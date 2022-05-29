#pragma once
#include "c_minecraft.h"

class c_esp : public cheat::Module
{
public:
	c_esp();

	void update();
	void enable();
	void disable();
};