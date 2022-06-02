#include "c_step.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

#include "c_entity.h"

enum StepMode
{
	VANILLA,
};

struct StepConfig
{
	bool enabled;
	enum StepMode mode;
	float step_height = 1.f;
};

static StepConfig config = StepConfig();

c_step::c_step() : Module("Step")
{
}

void c_step::update()
{
}

void c_step::enable()
{
	ctx.m_player->set_step_height(config.step_height);
}

void c_step::disable()
{
	ctx.m_player->set_step_height(0.5f);
}

bool c_step::is_enabled()
{
	return config.enabled;
}

void c_step::draw_options()
{
	if(ImGui::Checkbox("Enabled", &config.enabled))
	{
		config.enabled ? enable() : disable();
	}
	ImGui::Combo("Mode", (int*)&config.mode, "Vanilla");
	ImGui::NextColumn();
	ImGui::SliderFloat("Step Height", &config.step_height, .5f, 8.f);
}
