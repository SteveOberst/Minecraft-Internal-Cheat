#pragma once

#include "c_minecraft.h"

class c_flight : public cheat::Module
{
public:
	c_flight();

	void update();
	void enable();
	void disable();

	bool is_enabled();

	void draw_options();
};