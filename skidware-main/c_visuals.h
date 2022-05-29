#pragma once

#include "c_minecraft.h"
#include <map>

class c_visuals : public singleton<c_visuals> {
public:
	std::map<cheat::ModuleType, cheat::Module*> registered_modules;

	cheat::Module* get_module(cheat::ModuleType type);

	void register_modules();
};