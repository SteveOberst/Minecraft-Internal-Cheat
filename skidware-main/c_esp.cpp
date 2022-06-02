#include "c_esp.h"
#include "c_imguiextension.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

#include "c_gameinstance.h"
#include "c_glrender.h"

#include <iostream>

struct ESPConfig
{
	bool enabled;
	int keybind;
	bool draw_players;
	bool draw_entities;
	bool fill;
	float line_tickness;
	int r;
	int g;
	int b;
	int alpha;
	bool rainbow;
};

static ESPConfig config = ESPConfig();

c_esp::c_esp() : Module("ESP")
{
}

void c_esp::update()
{
	if (ctx.m_world == nullptr || !ctx.m_world->is_constructed())
	{
		return;
	}
	std::list<c_entity> list = ctx.m_world->get_entity_list();
	for (c_entity& entity : list)
	{
		//if (!entity.is_valid() || entity.is_item() || entity.index() == ctx.m_player->index() || !entity.is_alive())
		//	continue;

		AxisAlignedBB aabb = entity.get_bounding_box();
		//c_rendermanager* render_manager = ctx.m_render;
		//vec3_t render_pos = render_manager->render_position();
		//glTranslated(render_pos.x, render_pos.y, render_pos.z);
		//c_glrender::get().box_outline(aabb.min_x(), aabb.min_y(), aabb.min_z(), aabb.max_x(), aabb.max_y(), aabb.max_z(), config.r, config.g, config.b, config.alpha, config.line_tickness);
	}
}

void c_esp::enable()
{
	config.enabled = true;
}

void c_esp::disable()
{
	config.enabled = false;
}

bool c_esp::is_enabled()
{
	return config.enabled;
}

void c_esp::draw_options()
{
	ImGui::Checkbox("Enabled", &config.enabled);
	ImGui::Checkbox("Players", &config.draw_players);
	ImGui::Checkbox("Entities", &config.draw_entities);
	ImGui::Checkbox("Fill Box", &config.fill);
	ImGui::SliderFloat("Line Thickness", &config.line_tickness, 1.f, 10.f);
	ImGui::NextColumn();
	bool rainbow = ImGui::Checkbox("Rainbow", &config.rainbow);
	if (rainbow)
	{
		ImGui::BeginDisabled(rainbow);
		ImGui::PushStyleVar(ImGuiStyleVar_DisabledAlpha, 0.f);
	}

	ImGui::SliderInt("R", &config.r, 0, 255);
	ImGui::SliderInt("G", &config.g, 0, 255);
	ImGui::SliderInt("B", &config.b, 0, 255);
	ImGui::SliderInt("Alpha", &config.alpha, 0, 255);
	if (rainbow)
	{
		ImGui::PopStyleVar();
		ImGui::EndDisabled();
	}
}
