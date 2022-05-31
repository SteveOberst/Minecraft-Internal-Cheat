#include "c_combat.h"
#include "c_autoclicker.h"

#include <iostream>

cheat::Module* c_combat::get_module(cheat::ModuleType type)
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

void c_combat::handle()
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

void c_combat::register_modules()
{
	registered_modules.insert({ cheat::ModuleType::C_AUTO_CLICKER, new c_autoclicker() });
}