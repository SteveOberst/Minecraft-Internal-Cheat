#include "c_minecraft.h"
#include "c_gameinstance.h"
#include "c_glrender.h"
#include "c_gltext.h"

#include "c_visuals.h"

#include "c_config.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

#include "icons.h"

#define GWL_WNDPROC         (-4)

fn_wgl_swap_buffers original_wgl_swap_buffers;

ImFont* global = nullptr;
ImFont* global2 = nullptr;
ImFont* second = nullptr;
ImFont* logo_font = nullptr;
ImFont* module_tab_font = nullptr;

ImGuiContext* context;

static const char* glsl_version = "#version 130";
static HWND hWindow;

void InitImGui(HWND window);

GLuint* icons[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

constexpr auto GLTEXTURE_COMBAT = 0;
constexpr auto GLTEXTURE_VISUAL = 1;
constexpr auto GLTEXTURE_RADAR = 2;
constexpr auto GLTEXTURE_MOVEMENT = 3;
constexpr auto GLTEXTURE_COLORS = 4;
constexpr auto GLTEXTURE_INVENTORY = 5;
constexpr auto GLTEXTURE_TRIGGER = 6;
constexpr auto GLTEXTURE_OTHER = 7;

WNDPROC oWndProc;

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE;

	hWindow = handle;
	return FALSE;
}

HWND GetProcessWindow()
{
	hWindow = NULL;
	EnumWindows(EWindowsCallback, NULL);
	return hWindow;
}

void sglLoadTexture(BYTE* texture, UINT width, UINT height, GLuint* image_texture)
{
	glGenTextures(GL_TEXTURE_2D, image_texture);
	glTexParameteri(*image_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(*image_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(*image_texture, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(*image_texture, GL_TEXTURE_WRAP_T, GL_CLAMP);
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, false, GL_RGBA, GL_FLOAT, texture);
}

void InitImGui(HWND window)
{
	// grab window handle
	while (!window)
	{
		window = GetProcessWindow();
	}
	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
	
	context = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.WantCaptureKeyboard = true; // TEST
	ImGui_ImplWin32_Init(window);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Alpha = 1.f;
	style->WindowRounding = 1.f;
	style->FramePadding = ImVec2(4, 3);
	style->WindowPadding = ImVec2(8, 8); // 8, 8
	style->ItemInnerSpacing = ImVec2(4, 4);
	style->ItemSpacing = ImVec2(8, 4);
	style->FrameRounding = 5.f;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 12.f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_ChildBg] = ImColor(24, 29, 59, 255);
	colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.11f, 0.50f);
	colors[ImGuiCol_FrameBg] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_Header] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_HeaderActive] = ImColor(28, 28, 36, 255);
	colors[ImGuiCol_HeaderHovered] = ImColor(30, 30, 38, 255);
	colors[ImGuiCol_PopupBg] = ImColor(35, 35, 45, 255);

	global = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/pivodef.ttf", 15.0f);
	global2 = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/pivodef.ttf", 14.0f);
	second = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/pivolight.ttf", 11.6f);
	logo_font = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/AccidentalPresidency.ttf", 55.0f);
	module_tab_font = io.Fonts->AddFontFromFileTTF("C:/windows/fonts/pivodef.ttf", 19.f);
}

void load_textures()
{
	if (icons[GLTEXTURE_COMBAT] == nullptr)
		sglLoadTexture(Combat ,20, 20, icons[GLTEXTURE_COMBAT]);
	if (icons[GLTEXTURE_VISUAL] == nullptr)
		sglLoadTexture(Visual, 21, 20, icons[GLTEXTURE_VISUAL]);
	if (icons[GLTEXTURE_RADAR] == nullptr)
		sglLoadTexture(Radar, 21, 20, icons[GLTEXTURE_RADAR]);
	if (icons[GLTEXTURE_MOVEMENT] == nullptr)
		sglLoadTexture(Movement, 21, 20, icons[GLTEXTURE_MOVEMENT]);
	if (icons[GLTEXTURE_COLORS] == nullptr)
		sglLoadTexture(Colors, 21, 20, icons[GLTEXTURE_COLORS]);
	if (icons[GLTEXTURE_INVENTORY] == nullptr)
		sglLoadTexture(Inventory, 21, 14, icons[GLTEXTURE_INVENTORY]);
	if (icons[GLTEXTURE_TRIGGER] == nullptr)
		sglLoadTexture(Triggerbot, 21, 20, icons[GLTEXTURE_TRIGGER]);
	if (icons[GLTEXTURE_OTHER] == nullptr)
		sglLoadTexture(Skinss, 21, 20, icons[GLTEXTURE_OTHER]);
}

const ImColor background_color = ImColor(24, 29, 59, 220);
const ImColor background_color_non_transp = ImColor(24, 29, 59, 255);
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);

const std::vector<std::string> tab_vec = { "Visuals", "Combat", "Movement", "Misc", "Config" };
const std::vector<std::string> tab_description_vec = { "ESP, Chams, Tracers", "Killaura, Reach", "Fly, Speed", "Other Settings", "Config Manager" };

bool init = false;
bool draw_gui = true;

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (draw_gui && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

const std::vector<int> icon_index_vec = { GLTEXTURE_VISUAL, GLTEXTURE_COMBAT, GLTEXTURE_TRIGGER, GLTEXTURE_INVENTORY, GLTEXTURE_OTHER };

//
// https://gist.github.com/godshawk/6a5cfcb7c447c977e2ce
// https://guidedhacking.com/threads/opengl-drawing-class.6264/
bool __stdcall hooks::wgl_swap_buffers(_In_ HDC hdc) {
	HDC m_curhdc = hdc;
	if (!c_gltext::get().m_fontbuilt || m_curhdc != c_gltext::get().m_fonthdc) {
		c_gltext::get().build_fonts();
		return original_wgl_swap_buffers(hdc);
	}

	c_glrender::get().setup_ortho();

	unsigned char color [3] { 0, 128, 255 };
	c_gltext::get().print(2, 15, color, xor ("Skidware"));

	// run our visuals here.
	//c_esp::get().handle();
	//c_visuals::get().handle();
	c_glrender::get().restore_gl();

	// Skidware - render gui
	//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	if (!init)
	{
		//wglMakeCurrent(hdc, newContext);
		InitImGui(hWindow);
		init = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		draw_gui = !draw_gui;
	}

	if (!draw_gui)
	{
		return original_wgl_swap_buffers(hdc);
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	ImGui::CaptureMouseFromApp(true); // Test
	ImGui::Begin("Skidware", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);
	ImVec2 pos;
	ImDrawList* draw;
	pos = ImGui::GetWindowPos();
	draw = ImGui::GetWindowDrawList();
	ImGui::SetWindowSize(ImVec2(900, 530));
	ImVec2 win_size = ImGui::GetWindowSize();

	static int tab_index = 0;

	// Draw window frame
	draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + win_size.x, pos.y + win_size.y), background_color, 12.f);

	float child_offset_y = 120;
	float child_offset_x = 15;
	float child_width = 165;
	ImGui::SetNextWindowPos(ImVec2(pos.x + child_offset_x, pos.y + child_offset_y));
	ImGui::BeginChild("##LeftSide", ImVec2(child_width, win_size.y - child_offset_y - 10), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.f, 0.f));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
	ImGui::PushFont(global);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(125, 125, 125, 255));

	// Draw tabs (Visuals, Legitbot...)
	for (unsigned int i = 0; i < tab_vec.size(); i++)
	{
		// we use buttons instead of tabs due to the customizations possibilities
		if (ImGui::Button(tab_vec.at(i).c_str(), ImVec2(150, 63)))
		{
			tab_index = i;
		}
	}

	ImGui::PopStyleColor(2);
	ImGui::PopFont();
	ImGui::PopStyleVar(2);

	ImGui::EndChild();

	// =============== Icons & Tab descriptions [begin] ===============
	int base_offset_icon_y = 149;
	int offset_icon_x = 20;
	int icon_space = 63;

	// Hecky way to draw my lovely icons 
	// TODO: icons for opengl
	for (unsigned int i = 0; i < icon_index_vec.size(); i++)
	{
		ImVec2 cursor = ImGui::GetCursorScreenPos();
		ImGui::SetCursorScreenPos(ImVec2(pos.x + offset_icon_x, pos.y + base_offset_icon_y + (icon_space * i)));
		ImGui::Image(icons[icon_index_vec.at(i)], ImVec2(16, 16));
		ImGui::SetCursorScreenPos(cursor);
	}

	// Descriptions use the icon positions as offset
	int base_offset_descriptor_x = 72;
	int offset_descriptor_y = 12;
	ImGui::PushFont(second);
	for (unsigned int i = 0; i < tab_description_vec.size(); i++)
	{
		const char* text = tab_description_vec.at(i).c_str();
		ImVec2 text_size = ImGui::CalcTextSize(text);
		float offset_exact = (pos.x + offset_icon_x) + base_offset_descriptor_x - (text_size.x / 2);

		ImVec2 cursor = ImGui::GetCursorScreenPos();
		ImGui::SetCursorScreenPos(ImVec2(offset_exact, (pos.y + base_offset_icon_y + (icon_space * i)) + offset_descriptor_y));
		ImGui::Text(text);
		ImGui::SetCursorScreenPos(cursor);
	}
	ImGui::PopFont();
	// =============== Icons & Tab descriptions [end] ===============

	ImGui::BeginGroup();
	ImGui::PushFont(global2);
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	ImGuiWindowFlags sub_tab_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground;

	switch (tab_index) // Begin - render sub tabs
	{
	case 0: // Visuals
	{
		visual_config_handler->draw(draw, pos, win_size, sub_tab_flags, background_color_non_transp, module_tab_font);
		break;
	}
	case 1: // Combat
	{
		combat_config_handler->draw(draw, pos, win_size, sub_tab_flags, background_color_non_transp, module_tab_font);
		break;
	}
	case 2: // Movement
	{
		
		break;
	}
	case 3: // Misc
	{

		break;
	}
	case 4: // Config
	{
		// TODO: implement configs
		break;
	}
	} // END - render sub tabs

	//ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::EndGroup();

	// Draw client name and rectangle (removed rectangle due to the ugly looks of it) in the upper left corner
	//draw->AddRectFilled(ImVec2(pos.x + 10, pos.y + 10), ImVec2(pos.x + offset_x - 5, pos.y + upper_vertical_rect_offset - 5), background_color_non_transp, 6.f);
	ImGui::BeginGroup();

	int logo_offset_x = 15;
	int logo_offset_y = 15;

	ImVec2 previous_cursor = ImGui::GetCursorScreenPos();
	ImGui::SetCursorScreenPos(ImVec2(pos.x + logo_offset_x, pos.y + logo_offset_y));
	ImGui::PushFont(logo_font);
	ImGui::Text("SKIDWARE");
	ImGui::PopFont();
	ImGui::SetCursorScreenPos(previous_cursor);

	ImGui::EndGroup(); // End the logo's group

	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return original_wgl_swap_buffers(hdc);
}

long __stdcall hooks::wndproc(const HWND window_handle, unsigned int user_msg, uintptr_t wparam, long lparam) {

	if (user_msg == WM_LBUTTONDOWN) {
		
	}

	return CallWindowProcA(c_main::get().m_wndproc, window_handle, user_msg, wparam, lparam);
}