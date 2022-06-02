#pragma once
#include "c_minecraft.h"

class c_reach : public cheat::Module
{
public:
	c_reach();

	void update();
	void enable();
	void disable();

	bool is_enabled();

	void draw_options();
};