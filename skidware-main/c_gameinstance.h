#pragma once

#include "c_minecraft.h"
#include "c_entity.h"
#include "c_world.h"
#include "c_rendermanager.h"
#include "c_movingobjectposition.h"
#include "c_timer.h"

#include "Mapping.h"

class c_gameinstance {
private:
	mappings::JMapping* mapping;

public:

	c_gameinstance() {
		this->mapping = mappings::getMapping();
	}

	jobject get_minecraft() {
		using namespace mappings;
		jclass minecraft_class = minecraft->m_jenv->FindClass(getMappedClassName("Minecraft"));
		jmethodID find_minecraft = minecraft->m_jenv->GetStaticMethodID(minecraft_class, getMethodName("Minecraft", "getMinecraft"), getMethodSignature("Minecraft", "getMinecraft"));
		return minecraft->m_jenv->CallStaticObjectMethod(minecraft_class, find_minecraft);
	}

	void left_click_mouse() {
		using namespace mappings;
		jmethodID click_mouse = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getMethodName("Minecraft", "leftClickMouse"), getMethodSignature("Minecraft", "leftClickMouse"));
		return minecraft->m_jenv->CallVoidMethod(get_minecraft(), click_mouse);
	}

	void right_click_mouse() {
		using namespace mappings;
		jmethodID click_mouse = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getMethodName("Minecraft", "rightClickMouse"), getMethodSignature("Minecraft", "rightClickMouse"));
		return minecraft->m_jenv->CallVoidMethod(get_minecraft(), click_mouse);
	}

	jobject get_screen() {
		using namespace mappings;
		jfieldID get_screen = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "currentScreen"), getFieldSignature("Minecraft", "currentScreen"));
		return minecraft->m_jenv->GetObjectField(get_minecraft(), get_screen);
	}

	jobject get_player() {
		using namespace mappings;
		jfieldID get_player = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "thePlayer"), getFieldSignature("Minecraft", "thePlayer"));
		return minecraft->m_jenv->GetObjectField(get_minecraft(), get_player);
	}

	c_rendermanager* get_render_manager() {
		using namespace mappings;
		jfieldID render_manager = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "renderManager"), getFieldSignature("Minecraft", "renderManager"));
		return new c_rendermanager(minecraft->m_jenv->GetObjectField(get_minecraft(), render_manager));
	}

	c_movingobjectposition object_mouse_over() {
		using namespace mappings;
		jfieldID moving_object_pos = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "objectMouseOver"), getFieldSignature("Minecraft", "objectMouseOver"));
		return c_movingobjectposition(minecraft->m_jenv->GetObjectField(get_minecraft(), moving_object_pos));
	}

	c_timer get_timer() {
		using namespace mappings;
		jfieldID timer = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "timer"), getFieldSignature("Minecraft", "timer"));
		return c_timer(minecraft->m_jenv->GetObjectField(get_minecraft(), timer));
	}

	c_entity* get_local() {
		return new c_entity(minecraft->game->get_player());
	}

	c_world* get_world() {
		using namespace mappings;
		jfieldID get_world = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "theWorld"), getFieldSignature("Minecraft", "theWorld"));
		return new c_world(minecraft->m_jenv->GetObjectField(get_minecraft(), get_world));
	}

	bool in_game_has_focus() {
		using namespace mappings;
		jfieldID focus = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_minecraft()), getFieldName("Minecraft", "inGameHasFocus"), getFieldSignature("Minecraft", "inGameHasFocus"));
		return minecraft->m_jenv->GetBooleanField(get_minecraft(), focus);
	}
};