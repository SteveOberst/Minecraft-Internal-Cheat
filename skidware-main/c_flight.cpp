#include "c_flight.h"
#include "c_entity.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

enum FlightMode
{
	SMOOTH_VANILLA = 0,
	VANILLA = 1,
	GLIDE = 2
};

struct FlightConfig
{
	bool enabled;
	bool anti_kick; // anti kick for vanilla modes
	FlightMode mode;
	float fly_speed = 1.f;
};

static FlightConfig config = FlightConfig();

c_flight::c_flight() : Module("Fly")
{
}

void handle_smooth_vanilla()
{
	if (config.anti_kick)
	{
		// TODO: only add velocity if player is not on ground
		ctx.m_player->add_velocity(vec3_t(0, -0.025, 0));
	}
	ctx.m_player->set_flight(true);
}

void handle_glide()
{
	ctx.m_player->set_velocity(vec3_t(ctx.m_player->mot_x(), -0.02, ctx.m_player->mot_z()));
}

void disable_smooth_vanilla()
{
	ctx.m_player->set_flight(false);
}

void c_flight::update()
{
	std::cout << ctx.m_player->mot_y() << std::endl;
	switch (config.mode)
	{
	case SMOOTH_VANILLA:
		handle_smooth_vanilla();
	case GLIDE:
		handle_glide();
	}
}

void c_flight::enable()
{
	switch (config.mode)
	{
	case SMOOTH_VANILLA:
		handle_smooth_vanilla();
	}
}

void c_flight::disable()
{
	switch (config.mode)
	{
	case SMOOTH_VANILLA:
		disable_smooth_vanilla();
	}
}

bool c_flight::is_enabled()
{
	return config.enabled;
}

void c_flight::draw_options()
{
	if (ImGui::Checkbox("Enabled", &config.enabled))
	{
		config.enabled ? enable() : disable();
	}

	int mode = ImGui::Combo("Mode", (int*) &config.mode, "Smooth Vanilla\0Vanilla\0Glide");

	if (mode == VANILLA || mode == SMOOTH_VANILLA)
	{
		ImGui::Checkbox("Anti-kick", &config.anti_kick);
	}

	ImGui::NextColumn();
	ImGui::SliderFloat("Fly Speed", &config.fly_speed, .1f, 2.f);
}
