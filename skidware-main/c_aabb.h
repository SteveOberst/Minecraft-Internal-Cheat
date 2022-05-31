#pragma once

#include "c_minecraft.h"

class AxisAlignedBB
{
private:
	jobject java_class;

public:
	AxisAlignedBB();
	AxisAlignedBB(jobject java_class) {
		this->java_class = java_class;
	}

	double min_x() {
		jfieldID min_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "a", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, min_x);
	}

	double min_y() {
		jfieldID min_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "b", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, min_y);
	}

	double min_z() {
		jfieldID min_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "c", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, min_z);
	}

	double max_x() {
		jfieldID max_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "d", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, max_x);
	}

	double max_y() {
		jfieldID max_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "e", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, max_y);
	}

	double max_z() {
		jfieldID max_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "f", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, max_z);
	}

	bool contains(vec3_t vec) {
		return vec.x > min_x() && vec.x < max_x() && vec.y > min_y() && vec.y < max_y() && vec.z > min_z() && vec.z < max_z();
	}
};