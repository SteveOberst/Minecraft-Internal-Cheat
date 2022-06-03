#include "c_player.h"
#include "c_modtimer.h"

std::map<cheat::ModuleType, cheat::Module*>& c_player::get_registered_modules()
{
	return this->registered_modules;
}

cheat::Module* c_player::get_module(cheat::ModuleType type)
{
	std::map<cheat::ModuleType, cheat::Module*>::iterator it = registered_modules.begin();
	while (it != registered_modules.end())
	{
		if (it->first == type)
		{
			return it->second;
		}
		it++;
	}
	return nullptr; // should never actually end up returning a nullptr
}

void c_player::handle()
{
	std::map<cheat::ModuleType, cheat::Module*>::iterator it = registered_modules.begin();
	while (it != registered_modules.end())
	{
		cheat::Module* mod = it->second;
		if (mod->is_enabled())
		{
			mod->update();
		}
		it++;
	}
}

void c_player::register_modules()
{
	registered_modules.insert({ cheat::ModuleType::P_TIMER, new c_timer_module() });
}