#include "includes.h"
#include "c_minecraft.h"

/*
* ~~
*  a fully c++ coded [cheat base] engineered by jordan & dregulae.
* ~~
*/

/* ~~ forward declarations. ~~ */
HINSTANCE m_unhookinst;
void initialise(void);

/* ~~ dllmain... with as little winapi as possible. ~~ */
bool __stdcall DllMain(HINSTANCE instance, unsigned long reason, void* reserved) {

	// Skidware - allocate debug console window
	/*AllocConsole();
	FILE* fIn;
	FILE* fOut;
	freopen_s(&fIn, "conin$", "r", stdin);
	freopen_s(&fOut, "conout$", "w", stdout);
	freopen_s(&fOut, "conout$", "w", stderr);*/

	// reduce the size of the dll by removing DLL_THREAD* calls - ty lily <3
	DisableThreadLibraryCalls(instance);

	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			m_unhookinst = instance;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE) initialise, 0, 0, 0);
		} break;

		default: {

		} break;
	}

	return true;
}

/* ~~ main initialisation function. ~~ */
void initialise(void) {
	// hook our main cheat on inject
	c_main::get().hook();

	// handle unload state
	while (!ctx.m_unload) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	// unload triggered, unhook cheat
	c_main::get().unhook();

	// handle self destruction, removing evidence of cheat
	// c_destroy::get()->handle();

	// prevent unload crashing
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	// self explanatory function name, who would have thought?
	FreeLibraryAndExitThread(m_unhookinst, 0);
}