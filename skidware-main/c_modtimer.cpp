#include "c_modtimer.h"
#include "c_timer.h"
#include "c_gameinstance.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

enum TimerMode
{
	NORMAL = 0,
	SWITCH = 1
};

struct TimerConfig
{
	bool enabled;
	TimerMode mode = NORMAL;
	int keybind;
	float speed = 1.2f;
};

static TimerConfig config = TimerConfig();

void update_timer_speed()
{
	c_timer timer = minecraft->game->get_timer();
	timer.set_timer(config.speed);
}

c_timer_module::c_timer_module() : Module("Timer")
{
}

void c_timer_module::update()
{
}

void c_timer_module::enable()
{
	update_timer_speed();
}

void c_timer_module::disable()
{
	c_timer timer = minecraft->game->get_timer();
	timer.reset_timer();
}

bool c_timer_module::is_enabled()
{
	return config.enabled;
}

void c_timer_module::draw_options()
{
	if (ImGui::Checkbox("Enabled", &config.enabled))
	{
		config.enabled ? enable() : disable();
	}

	ImGui::Combo("Mode", (int*)&config.mode, "Normal\0Switch");

	ImGui::NextColumn();
	ImGui::SliderFloat("Speed", &config.speed, .1f, 2.f);

	if (ImGui::IsItemActive())
	{
		update_timer_speed();
	}
}
