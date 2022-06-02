#pragma once
#include "c_minecraft.h"
#include <map>

class c_movement : public singleton<c_movement> {
public:
	std::map<cheat::ModuleType, cheat::Module*> registered_modules;

	cheat::Module* get_module(cheat::ModuleType type);

	void handle();

	void register_modules();
};