#include "c_autoclicker.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

#include "c_gameinstance.h"
#include "c_glrender.h"

#include <math.h>
#include <random>
#include <chrono>

struct AutoClickerConfig
{
	bool enabled_l = false;
	bool enabled_r = false;
	int keybind = 0;
	bool left_button = true;
	bool right_button = true;
	int left_bind = 0;
	int right_bind = 0;
	int min_cps_l = 10;
	int max_cps_l = 13;
	int min_cps_r = 10;
	int max_cps_r = 13;
	bool jitter_left = true;
	bool jitter_right = false;
	bool entity_target_only = false; // auto clicks (left) only if target is an entity
	bool block_target_only = true; // auto click (right) only if target is a block
};

static AutoClickerConfig config = AutoClickerConfig();
static long last_input = 0;

c_autoclicker::c_autoclicker() : Module("Clicker")
{
}

bool is_target_valid_l(c_movingobjectposition& object)
{
	return config.entity_target_only ? object.is_entity() : !object.is_block();
}

bool is_target_valid_r(c_movingobjectposition& object)
{
	return !config.block_target_only || object.is_block();
}

int rand_int_in_range(int& inbound, int outbound)
{
	if (inbound > outbound)
	{
		outbound = inbound;
	}

	std::random_device rd;
	std::mt19937 gen(rand());
	std::uniform_int_distribution<> dis(inbound, outbound);
	return dis(gen);
}

void jitter()
{

}

static long last_left_click;
static long last_right_click;

static long next_min_delay_l;
static long next_min_delay_r;

//TODO: rework delays for more consistency
void c_autoclicker::update()
{
	if (!minecraft->game->in_game_has_focus())
	{
		return;
	}

	namespace sc = std::chrono;
	auto time = sc::system_clock::now(); 
	auto since_epoch = time.time_since_epoch();
	auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
	long now = millis.count();

	c_movingobjectposition object = minecraft->game->object_mouse_over();
	// TODO: change to appropriate keybinds
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (config.enabled_l)
		{
			if (now - last_left_click >= next_min_delay_l)
			{
				if (is_target_valid_l(object))
				{
					minecraft->game->left_click_mouse();
					last_left_click = now;
					next_min_delay_l = ((1000) / rand_int_in_range(config.min_cps_l, config.max_cps_l)); // spare some resources by not calculating a random delay value every interval
				}
			}
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (config.enabled_r)
		{
			if (now - last_right_click >= next_min_delay_r)
			{
				if (is_target_valid_r(object))
				{
					
					minecraft->game->right_click_mouse();
					last_right_click = now;
					next_min_delay_r = ((1000) / rand_int_in_range(config.min_cps_r, config.max_cps_r)); // spare some resources by not calculating a random delay value every interval
				}
			}
		}
	}
}

void c_autoclicker::enable()
{
}

void c_autoclicker::disable()
{
}

bool c_autoclicker::is_enabled()
{
	return config.enabled_l || config.enabled_r;
}

void c_autoclicker::draw_options()
{
	ImGui::Text("Left-Click");
	ImGui::Checkbox("Enabled", &config.enabled_l);
	ImGui::Checkbox("Jitter", &config.jitter_left);
	ImGui::Checkbox("Entity Target only", &config.entity_target_only);
	ImGui::SliderInt("Min CPS", &config.min_cps_l, 1, 20);
	ImGui::SliderInt("Max CPS", &config.max_cps_l, 1, 20);
	ImGui::NextColumn();
	ImGui::Text("Right-Click");
	// you may be asking, why are there spaces after every id?
	// well, apparently ImGui get's confused if we re-use ids
	ImGui::Checkbox("Enabled ", &config.enabled_r);
	ImGui::Checkbox("Jitter ", &config.jitter_right);
	ImGui::Checkbox("Block Target only ", &config.block_target_only);
	ImGui::SliderInt("Min CPS ", &config.min_cps_r, 1, 20);
	ImGui::SliderInt("Max CPS ", &config.max_cps_r, 1, 20);
}
