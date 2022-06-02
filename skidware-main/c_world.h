#pragma once

#include "c_minecraft.h"
#include "c_javaset.h"
#include "c_javalist.h"
#include "c_entity.h"

#include <list>

class c_world {
public:
	c_world() { }
	c_world(jobject javaclass) {
		java_class = javaclass;
		update_entities();
		update_player_entities();
		constructed = true;
	}

	int get_entities() {
		return list_instance.size(minecraft->m_jenv->GetObjectField(java_class, loaded_entities));
	}

	int get_player_entities() {
		return list_instance.size(minecraft->m_jenv->GetObjectField(java_class, loaded_players));
	}

	bool is_constructed() {
		return constructed;
	}

	c_entity get_entity(int i) {
		return c_entity(list_instance.get(minecraft->m_jenv->GetObjectField(java_class, loaded_entities), i));
	}

	c_entity get_player_entity(int i) {
		return c_entity(list_instance.get(minecraft->m_jenv->GetObjectField(java_class, loaded_players), i));
	}

	int test() {
		return loaded_players_list.size();
	}

	std::list<c_entity>& get_entity_list() {
		return loaded_entities_list;
	}

	std::list<c_entity>& get_player_list() {
		return loaded_players_list;
	}

	void update_entities() {
		loaded_entities = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetSuperclass(minecraft->m_jenv->GetObjectClass(java_class)), "f", "Ljava/util/List;");
		loaded_entities_list.clear();
		for (int i = 0; i < get_entities(); i++) {
			loaded_entities_list.push_back(get_entity(i));
		}
	}

	void update_player_entities() {
		loaded_players = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetSuperclass(minecraft->m_jenv->GetObjectClass(java_class)), "j", "Ljava/util/List;");
		loaded_players_list.clear();
		for (int i = 0; i < get_player_entities(); i++) {
			loaded_players_list.push_back(get_player_entity(i));
		}
	}

	void set_time(jobject java_class, jlong time) {
		jmethodID set_time = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), "b", "(J)V");
		minecraft->m_jenv->CallLongMethod(java_class, set_time, time);
	}

	bool is_valid() {
		return java_class;
	}

private:
	jobject java_class;
	jfieldID loaded_entities;
	jfieldID loaded_players;
	std::list<c_entity> loaded_entities_list;
	std::list<c_entity> loaded_players_list;
	c_javalist list_instance = c_javalist();
	bool constructed = false;
};

extern c_world* world;