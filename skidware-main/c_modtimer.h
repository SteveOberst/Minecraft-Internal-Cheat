#pragma once

#include "c_minecraft.h"

class c_timer_module : public cheat::Module
{
public:
	c_timer_module();

	void update();
	void enable();
	void disable();

	bool is_enabled();

	void draw_options();
};