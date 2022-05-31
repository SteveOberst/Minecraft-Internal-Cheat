#pragma once

#include "c_minecraft.h"
#include <map>

class c_combat : public singleton<c_combat> {
public:
	std::map<cheat::ModuleType, cheat::Module*> registered_modules;

	cheat::Module* get_module(cheat::ModuleType type);

	void handle();

	void register_modules();
};