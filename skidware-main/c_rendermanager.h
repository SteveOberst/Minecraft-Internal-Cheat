#pragma once

#include "c_minecraft.h"

#include "Mapping.h"

class c_rendermanager {
public:
	c_rendermanager() { }
	c_rendermanager(jobject javaclass) {
		java_class = javaclass;
	}

	vec3_t render_position() {
		return vec3_t(get_render_x(), get_render_y(), get_render_z());
	}

private:
	jobject java_class;

	float get_render_x() {
		using namespace mappings;
		jfieldID get_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("RenderManager", "renderPosX"), getFieldSignature("RenderManager", "renderPosX"));
		return minecraft->m_jenv->GetDoubleField(java_class, get_x);
	}

	float get_render_y() {
		using namespace mappings;
		jfieldID get_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("RenderManager", "renderPosY"), getFieldSignature("RenderManager", "renderPosY"));
		return minecraft->m_jenv->GetDoubleField(java_class, get_y);
	}

	float get_render_z() {
		using namespace mappings;
		jfieldID get_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("RenderManager", "renderPosZ"), getFieldSignature("RenderManager", "renderPosZ"));
		return minecraft->m_jenv->GetDoubleField(java_class, get_z);
	}
};