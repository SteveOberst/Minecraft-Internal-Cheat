#include "c_config.h"
#include "c_minecraft.h"

#include "c_visuals.h"

// =============== Visual Config Handler  ===============
void VisualConfigHandler::save()
{
}

void VisualConfigHandler::read()
{
}

void VisualConfigHandler::draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font)
{
    float space = 10;
    float offset_x = 165 /* = child_width in the main rendering function*/ + 10;
    float upper_vertical_rect_offset = 90;

    // draw modules tab
    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space));
    c_visuals& visuals = c_visuals::get();
    std::map<cheat::ModuleType, cheat::Module*>::iterator it = visuals.registered_modules.begin();
    // iterate over registered modules
    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space + 3 /*adjust the position by a bit*/));
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + space), ImVec2(pos.x + win_size.x - space, pos.y + (upper_vertical_rect_offset - space)), background_color, 6.f);
    ImGui::BeginChild("##RightSide", ImVec2(win_size.x - offset_x + space, upper_vertical_rect_offset - space), true, sub_tab_flags);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) background_color);
    ImGui::PushFont(module_tab_font);
    while (it != visuals.registered_modules.end())
    {
        cheat::Module* mod = it->second;
        it++; // increase iterator right here in case of early return
        if (mod == nullptr) // safety measurement - should not actually return a nullptr at any given point but better safe than sorry.
        {
            continue;
        }
        ImGui::Button(mod->module_name(), ImVec2(90/*120*/, 50));
    }
    ImGui::PopFont();
    ImGui::PopStyleColor();
    ImGui::EndChild();

    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space + upper_vertical_rect_offset));
    // manually draw the rectangle around the settings
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset), ImVec2(pos.x + win_size.x - space, pos.y + win_size.y - space), background_color, 6.f);
    ImGui::BeginChild("##RightSide", ImVec2(win_size.x + offset_x, win_size.y - upper_vertical_rect_offset /*testing?*/ - (space * 2)), true, sub_tab_flags);
    {
        float column_width = ((pos.x + win_size.x - space) - (pos.x + offset_x)) / 2;
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, column_width);

        // Sliders, Checkboxes etc.
    }
    ImGui::EndChild();
}

// =============== Combat Config Handler  ===============
void CombatConfigHandler::save()
{
}

void CombatConfigHandler::read()
{
}

void CombatConfigHandler::draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font)
{
}

// =============== Movement Config Handler  ===============
void MovementConfigHandler::save()
{
}

void MovementConfigHandler::read()
{
}

void MovementConfigHandler::draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font)
{
}

// =============== Misc Config Handler  ===============
void MiscConfigHandler::save()
{
}

void MiscConfigHandler::read()
{
}

void MiscConfigHandler::draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font)
{
}

// =============== Other ===============
void draw_config_tab(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color)
{
}
