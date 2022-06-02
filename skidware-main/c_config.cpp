#include "c_config.h"
#include "c_minecraft.h"

#include "c_visuals.h"
#include "c_combat.h"
#include "c_movement.h"

ImColor clear_color = ImVec4(0, 0, 0, 0);

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
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) background_color);
    ImGui::PushFont(module_tab_font);
    int iterations = 0;
    static cheat::Module* selected = nullptr;
    while (it != visuals.registered_modules.end())
    {
        cheat::Module* mod = it->second;
        if (selected == nullptr)
        {
            selected = mod;
        }

        it++; // increase iterator right here in case of early return
        iterations++; // increase integer to keep track of iterations
        if (mod == nullptr) // safety measurement - should not actually return a nullptr at any given point but better safe than sorry.
        {
            continue; 
        }

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4) clear_color);
        ImVec2 button_dimensions = ImVec2(90, 50);
        if (ImGui::Button(mod->module_name(), button_dimensions))
        {
            selected = mod;
        }
        ImGui::PopStyleColor();

        // draw a line under the text if hovered
        if (ImGui::IsItemHovered())
        {
            ImVec2 text_size = ImGui::CalcTextSize(mod->module_name());
            int button_space = 8;
            int text_center = (button_dimensions.x * iterations) - (button_dimensions.x / 2) + (button_space * iterations);
            int line_height = 1;
            draw->AddRectFilled(
                ImVec2(pos.x + offset_x + text_center - (text_size.x / 2) - 1 /*account for precision loss*/, pos.y + space + button_space + (button_dimensions.y / 2) + (text_size.y / 2) + 3 /*adjust height a bit*/),
                ImVec2(pos.x + offset_x + text_center + (text_size.x / 2), pos.y + space + button_space + (button_dimensions.y / 2) + (text_size.y / 2) + 3 + line_height),
                ImColor(255, 255, 255, 255)
            );
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(2);
    ImGui::EndChild();

    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset));
    ImGui::SetCursorPos(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset));
    // manually draw the rectangle around the settings
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset), ImVec2(pos.x + win_size.x - space, pos.y + win_size.y - space), background_color, 6.f);
    ImGui::BeginChild("options", ImVec2(win_size.x - offset_x, win_size.y - upper_vertical_rect_offset/*testing?*/ + (space * 2)), true, sub_tab_flags);
    {
        float column_width = ((pos.x + win_size.x - space) - (pos.x + offset_x)) / 2;
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, column_width);
        //bool begin = ImGui::BeginTable("##RightSide", 2);
        if (selected == nullptr) // shouldn't ever be a nullptr, just making sure as safety measurement.
        {
            ImGui::EndChild();
            return;
        }
        // Sliders, Checkboxes etc.
        selected->draw_options();
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
    float space = 10;
    float offset_x = 165 /* = child_width in the main rendering function*/ + 10;
    float upper_vertical_rect_offset = 90;

    // draw modules tab
    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space));
    c_combat& combat = c_combat::get();
    std::map<cheat::ModuleType, cheat::Module*>::iterator it = combat.registered_modules.begin();
    // iterate over registered modules
    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space + 3 /*adjust the position by a bit*/));
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + space), ImVec2(pos.x + win_size.x - space, pos.y + (upper_vertical_rect_offset - space)), background_color, 6.f);
    ImGui::BeginChild("##RightSide", ImVec2(win_size.x - offset_x + space, upper_vertical_rect_offset - space), true, sub_tab_flags);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)background_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)background_color);
    ImGui::PushFont(module_tab_font);
    int iterations = 0;
    static cheat::Module* selected = nullptr;
    while (it != combat.registered_modules.end())
    {
        cheat::Module* mod = it->second;
        if (selected == nullptr)
        {
            selected = mod;
        }

        it++; // increase iterator right here in case of early return
        iterations++; // increase integer to keep track of iterations
        if (mod == nullptr) // safety measurement - should not actually return a nullptr at any given point but better safe than sorry.
        {
            continue;
        }

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)clear_color);
        ImVec2 button_dimensions = ImVec2(90, 50);
        if (ImGui::Button(mod->module_name(), button_dimensions))
        {
            selected = mod;
        }
        ImGui::PopStyleColor();

        // draw a line under the text if hovered
        if (ImGui::IsItemHovered())
        {
            ImVec2 text_size = ImGui::CalcTextSize(mod->module_name());
            int button_space = 8;
            int text_center = (button_dimensions.x * iterations) - (button_dimensions.x / 2) + (button_space * iterations);
            int line_height = 1;
            draw->AddRectFilled(
                ImVec2(pos.x + offset_x + text_center - (text_size.x / 2) - 1 /*account for precision loss*/, pos.y + space + button_space + (button_dimensions.y / 2) + (text_size.y / 2) + 3 /*adjust height a bit*/),
                ImVec2(pos.x + offset_x + text_center + (text_size.x / 2), pos.y + space + button_space + (button_dimensions.y / 2) + (text_size.y / 2) + 3 + line_height),
                ImColor(255, 255, 255, 255)
            );
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(2);
    ImGui::EndChild();

    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset));
    ImGui::SetCursorPos(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset));
    // manually draw the rectangle around the settings
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset), ImVec2(pos.x + win_size.x - space, pos.y + win_size.y - space), background_color, 6.f);
    ImGui::BeginChild("options", ImVec2(win_size.x - offset_x, win_size.y - upper_vertical_rect_offset/*testing?*/ + (space * 2)), true, sub_tab_flags);
    {
        float column_width = ((pos.x + win_size.x - space) - (pos.x + offset_x)) / 2;
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, column_width);
        if (selected == nullptr) // shouldn't ever be a nullptr, just making sure as safety measurement.
        {
            ImGui::EndChild();
            return;
        }
        // Sliders, Checkboxes etc.
        selected->draw_options();
    }
    ImGui::EndChild();
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
    float space = 10;
    float offset_x = 165 /* = child_width in the main rendering function*/ + 10;
    float upper_vertical_rect_offset = 90;

    // draw modules tab
    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space));
    c_movement& movement = c_movement::get();
    std::map<cheat::ModuleType, cheat::Module*>::iterator it = movement.registered_modules.begin();
    // iterate over registered modules
    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + space + 3 /*adjust the position by a bit*/));
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + space), ImVec2(pos.x + win_size.x - space, pos.y + (upper_vertical_rect_offset - space)), background_color, 6.f);
    ImGui::BeginChild("##RightSide", ImVec2(win_size.x - offset_x + space, upper_vertical_rect_offset - space), true, sub_tab_flags);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)background_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)background_color);
    ImGui::PushFont(module_tab_font);
    int iterations = 0;
    static cheat::Module* selected = nullptr;
    while (it != movement.registered_modules.end())
    {
        cheat::Module* mod = it->second;
        if (selected == nullptr)
        {
            selected = mod;
        }

        it++; // increase iterator right here in case of early return
        iterations++; // increase integer to keep track of iterations
        if (mod == nullptr) // safety measurement - should not actually return a nullptr at any given point but better safe than sorry.
        {
            continue;
        }

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)clear_color);
        ImVec2 button_dimensions = ImVec2(90, 50);
        int button_space = 8;

        // keep buttons on the same y pos and manually calculate x offset
        ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + ((button_dimensions.x) * (iterations - 1)) + (button_space * (iterations - 1)), 8/*button offset to the upper window edge*/));
        if (ImGui::Button(mod->module_name(), button_dimensions))
        {
            selected = mod;
        }
        ImGui::PopStyleColor();

        // draw a line under the text if hovered
        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
        {
            ImVec2 text_size = ImGui::CalcTextSize(mod->module_name());
            int text_center = (button_dimensions.x * iterations) - (button_dimensions.x / 2) + (button_space * iterations);
            int line_height = 1;
            draw->AddRectFilled(
                ImVec2(pos.x + offset_x + text_center - (text_size.x / 2) - 1 /*account for precision loss*/, pos.y + space + button_space + (button_dimensions.y / 2) + (text_size.y / 2) + 3 /*adjust height a bit*/),
                ImVec2(pos.x + offset_x + text_center + (text_size.x / 2), pos.y + space + button_space + (button_dimensions.y / 2) + (text_size.y / 2) + 3 + line_height),
                ImColor(255, 255, 255, 255)
            );
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(2);
    ImGui::EndChild();

    ImGui::SetNextWindowPos(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset));
    ImGui::SetCursorPos(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset));
    // manually draw the rectangle around the settings
    draw->AddRectFilled(ImVec2(pos.x + offset_x, pos.y + upper_vertical_rect_offset), ImVec2(pos.x + win_size.x - space, pos.y + win_size.y - space), background_color, 6.f);
    ImGui::BeginChild("options", ImVec2(win_size.x - offset_x, win_size.y - upper_vertical_rect_offset/*testing?*/ + (space * 2)), true, sub_tab_flags);
    {
        float column_width = ((pos.x + win_size.x - space) - (pos.x + offset_x)) / 2;
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, column_width);
        if (selected == nullptr) // shouldn't ever be a nullptr, just making sure as safety measurement.
        {
            ImGui::EndChild();
            return;
        }
        // Sliders, Checkboxes etc.
        selected->draw_options();
    }
    ImGui::EndChild();
}

// =============== Player Config Handler  ===============
void PlayerConfigHandler::save()
{
}

void PlayerConfigHandler::read()
{
}

void PlayerConfigHandler::draw(ImDrawList* draw, ImVec2& pos, ImVec2& win_size, unsigned int sub_tab_flags, ImColor background_color, ImFont* module_tab_font)
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
