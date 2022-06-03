#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

#include "c_minecraft.h"

class ConfigHandler
{
public:
	virtual void save() = 0;
	virtual void read() = 0; // TODO: pass cfg file (json?)
	virtual void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, cheat::Module* selected) = 0;

	virtual cheat::ModuleHandler& get_module_handler() = 0;
};

class VisualConfigHandler : public ConfigHandler
{
public:
	void save();
	void read(); 
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, cheat::Module* selected);

	cheat::ModuleHandler& get_module_handler();
};

class CombatConfigHandler : public ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, cheat::Module* selected);

	cheat::ModuleHandler& get_module_handler();
};

class MovementConfigHandler : public ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, cheat::Module* selected);

	cheat::ModuleHandler& get_module_handler();
};

class PlayerConfigHandler : public ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, cheat::Module* selected);

	cheat::ModuleHandler& get_module_handler();
};

class MiscConfigHandler : public ConfigHandler
{
public:
	void save();
	void read();
	void draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, cheat::Module* selected);

	cheat::ModuleHandler& get_module_handler();
};
namespace confighandler 
{
	void draw_options(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font, ConfigHandler* config_handler);

	void draw_config_tab(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color);
}

static VisualConfigHandler* visual_config_handler = new VisualConfigHandler();
static CombatConfigHandler* combat_config_handler = new CombatConfigHandler();
static MovementConfigHandler* movement_config_handler = new MovementConfigHandler();
static PlayerConfigHandler* player_config_handler = new PlayerConfigHandler();
static MiscConfigHandler* misc_config_handler = new MiscConfigHandler();