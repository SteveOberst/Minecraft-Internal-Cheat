#include "c_visuals.h"
#include "c_world.h"

#include "c_gltext.h"
#include "c_glrender.h"
#include "c_esp.h"

cheat::Module* c_visuals::get_module(cheat::ModuleType type)
{
	std::map<cheat::ModuleType, cheat::Module*>::iterator it = registered_modules.begin();
	while (it != registered_modules.end())
	{
		if (it->first == type)
		{
			return it->second;
		}
	}
	return nullptr; // should never actually end up returning a nullptr
}

void c_visuals::register_modules()
{
	registered_modules.insert({ cheat::ModuleType::V_ESP, new c_esp()});
}