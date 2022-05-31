#pragma once
#include "c_minecraft.h"

class c_autoclicker : public cheat::Module
{
public:
	c_autoclicker();

	void update();
	void enable();
	void disable();

	bool is_enabled();

	void draw_options();
};