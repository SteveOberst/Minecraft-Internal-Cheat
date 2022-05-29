#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

class ConfigHandler
{
public:
	virtual void save() = 0;
	virtual void read() = 0; // TODO: pass cfg file (json?)
	virtual void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font) = 0;
};

class VisualConfigHandler : ConfigHandler
{
public:
	void save();
	void read(); 
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font);
};

class CombatConfigHandler : ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font);
};

class MovementConfigHandler : ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font);
};

class MiscConfigHandler : ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font);
};

void draw_config_tab(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color);

static VisualConfigHandler* visual_config_handler = new VisualConfigHandler();
static CombatConfigHandler* combat_config_handler = new CombatConfigHandler();
static MovementConfigHandler* movement_config_handler = new MovementConfigHandler();
static MiscConfigHandler* misc_config_handler = new MiscConfigHandler();