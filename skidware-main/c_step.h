#pragma once
#include "c_minecraft.h"

class c_step : public cheat::Module
{
public:
	c_step();

	void update();
	void enable();
	void disable();

	bool is_enabled();

	void draw_options();
};