#include "c_minecraft.h"
#include "c_gameinstance.h"
#include "c_entity.h"
#include "c_world.h"
#include "c_gui.h"

#include "c_legit.h"
#include "c_movement.h"
#include "c_visuals.h"
#include "c_combat.h"

void init_modules();

/* ~~ our hooking function. ~~ */
void c_main::hook(void) {
	// wait for java virtual machine
	while (!(minecraft->m_jvm_dll = GetModuleHandleA(xor("jvm.dll")))) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	while (!(minecraft->m_opengl_dll = GetModuleHandleA(xor("opengl32.dll")))) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	while (!(minecraft->m_kernel32_dll = GetModuleHandleA(xor("Kernel32.dll")))) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	// lambda function to recognise window titles.
	auto get_window_title = [&] (void) {
		// buffer
		char title [256];

		// get current window handle
		m_hwnd = GetForegroundWindow();
		GetWindowTextA(m_hwnd, title, sizeof(title));

		std::string m_title = title;
		return m_title;
	};

	// find game through previously explained lambda function
	while (!(get_window_title().find(xor ("Minecraft")) != std::string::npos)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	// get the jvm and jni enviroment
	jsize count;
	if (JNI_GetCreatedJavaVMs(&minecraft->m_jvm, 1, &count) != JNI_OK || count == 0) {
		return;
	}

	jint res = minecraft->m_jvm->GetEnv((void **) &minecraft->m_jenv, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED) {
		res = minecraft->m_jvm->AttachCurrentThread((void **) &minecraft->m_jenv, nullptr);
	}

	if (res != JNI_OK) {
		return;
	}

	// get base addresses for hooking
	minecraft->m_wgl_swap_buffers = GetProcAddress(minecraft->m_opengl_dll, xor ("wglSwapBuffers"));
	minecraft->m_open_process = GetProcAddress(minecraft->m_kernel32_dll, xor ("OpenProcess"));
	minecraft->m_create_remote_thread = GetProcAddress(minecraft->m_kernel32_dll, xor ("CreateRemoteThread"));
	minecraft->m_enum_process_modules = GetProcAddress(minecraft->m_kernel32_dll, xor ("EnumProcessModules"));

	// start hooking
	m_wndproc = (WNDPROC) SetWindowLongPtrA(m_hwnd, GWLP_WNDPROC, (LONG_PTR) hooks::wndproc);

	MH_Initialize();
	MH_CreateHook(minecraft->m_wgl_swap_buffers, hooks::wgl_swap_buffers, reinterpret_cast< void** >(&original_wgl_swap_buffers));
	MH_EnableHook(minecraft->m_wgl_swap_buffers);

	MH_CreateHook(minecraft->m_open_process, hooks::open_process, reinterpret_cast< void** >(&original_open_process));
	MH_EnableHook(minecraft->m_open_process);

	MH_CreateHook(minecraft->m_create_remote_thread, hooks::create_remote_thread, reinterpret_cast< void** >(&original_create_remote_thread));
	MH_EnableHook(minecraft->m_create_remote_thread);

	MH_CreateHook(minecraft->m_enum_process_modules, hooks::enum_process_modules, reinterpret_cast< void** >(&original_enum_process_modules));
	MH_EnableHook(minecraft->m_enum_process_modules);

	init_modules();

	static long cycles = 0;
	ctx.m_world = minecraft->game->get_world(); // TEST
	while (!ctx.m_unload) {
		if (GetAsyncKeyState(VK_DELETE)) {
			ctx.m_unload = true;
		}
		cycles++;

		// ayo, nobody ever bothered deleting those before re-assigning them new values? Skidware - clean up memory
		delete ctx.m_player;
		//delete ctx.m_world;
		delete ctx.m_render;

		ctx.m_player = minecraft->game->get_local();
		// ctx.m_world = minecraft->game->get_world();
		ctx.m_render = minecraft->game->get_render_manager();

		if (!ctx.sane()) {
			continue;
		}

		c_combat::get().handle(); // running every 10 ms as some of the combat modules require a higher frequency

		if (cycles % 5 == 0) // 50ms have passed, equal to the length of a tick in minecraft
		{
			c_movement::get().handle();
		}

		Sleep(10);
	}
}

void init_modules()
{
	c_visuals::get().register_modules();
	c_combat::get().register_modules();
	c_movement::get().register_modules();
}

/* ~~ our unhooking function ~~ */
void c_main::unhook(void) {
	// replace with original wndproc
	SetWindowLongPtrA(m_hwnd, GWLP_WNDPROC, (LONG_PTR) m_wndproc);

	MH_RemoveHook(minecraft->m_wgl_swap_buffers);
	MH_RemoveHook(minecraft->m_open_process);
	MH_RemoveHook(minecraft->m_create_remote_thread);
	MH_RemoveHook(minecraft->m_enum_process_modules);
	MH_Uninitialize();

	minecraft->m_jvm->DetachCurrentThread();
}

/* ~~ global sanity check ~~ */
bool c_context::sane(void) {
	return (ctx.m_player->is_valid() && ctx.m_world->is_valid());
}

/* ~~ define our external variables ~~ */
c_minecraft* minecraft = new c_minecraft();
c_context    ctx;

cheat::Module::Module(const char* name) : name { name }
{
}

const char* cheat::Module::module_name()
{
	return name;
}
