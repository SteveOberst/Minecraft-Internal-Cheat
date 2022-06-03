#include "c_movement.h"
#include "c_entity.h"
#include "c_flight.h"
#include "c_step.h"

std::map<cheat::ModuleType, cheat::Module*>& c_movement::get_registered_modules()
{
	return this->registered_modules;
}

cheat::Module* c_movement::get_module(cheat::ModuleType type)
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

void c_movement::handle()
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

void c_movement::register_modules()
{
	registered_modules.insert({ cheat::ModuleType::M_FLIGHT, new c_flight() });
	registered_modules.insert({ cheat::ModuleType::M_STEP, new c_step() });
}