#pragma once

#include "c_minecraft.h"

#include "Mapping.h"

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
		using namespace mappings;
		jfieldID min_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("AxisAlignedBB", "minX"), getFieldSignature("AxisAlignedBB", "minX"));
		return minecraft->m_jenv->GetDoubleField(java_class, min_x);
	}

	double min_y() {
		using namespace mappings;
		jfieldID min_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("AxisAlignedBB", "minY"), getFieldSignature("AxisAlignedBB", "minY"));
		return minecraft->m_jenv->GetDoubleField(java_class, min_y);
	}

	double min_z() {
		using namespace mappings;
		jfieldID min_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("AxisAlignedBB", "minZ"), getFieldSignature("AxisAlignedBB", "minZ"));
		return minecraft->m_jenv->GetDoubleField(java_class, min_z);
	}

	double max_x() {
		using namespace mappings;
		jfieldID max_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("AxisAlignedBB", "maxX"), getFieldSignature("AxisAlignedBB", "maxX"));
		return minecraft->m_jenv->GetDoubleField(java_class, max_x);
	}

	double max_y() {
		using namespace mappings;
		jfieldID max_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("AxisAlignedBB", "maxY"), getFieldSignature("AxisAlignedBB", "maxY"));
		return minecraft->m_jenv->GetDoubleField(java_class, max_y);
	}

	double max_z() {
		using namespace mappings;
		jfieldID max_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("AxisAlignedBB", "maxZ"), getFieldSignature("AxisAlignedBB", "maxZ"));
		return minecraft->m_jenv->GetDoubleField(java_class, max_z);
	}

	bool contains(vec3_t vec) {
		return vec.x > min_x() && vec.x < max_x() && vec.y > min_y() && vec.y < max_y() && vec.z > min_z() && vec.z < max_z();
	}
};