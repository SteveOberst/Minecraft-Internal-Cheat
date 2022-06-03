#pragma once

#include "c_minecraft.h"
#include "c_aabb.h"

class c_entity {
public:
	c_entity() { }
	c_entity(jobject javaclass) {
		java_class = javaclass;
	}

	vec3_t position() {
		return vec3_t(get_x(), get_y(), get_z());
	}

	vec3_t size() {
		using namespace mappings;
		jfieldID width = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "width"), getFieldSignature("Entity", "width"));
		jfieldID height = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "height"), getFieldSignature("Entity", "height"));
		return vec3_t(minecraft->m_jenv->GetFloatField(java_class, height), minecraft->m_jenv->GetFloatField(java_class, width), 0.0f);
	}

	double mot_x() {
		using namespace mappings;
		jfieldID motion_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "motionX"), getFieldSignature("Entity", "motionX"));
		return minecraft->m_jenv->GetDoubleField(java_class, motion_x);
	}

	double mot_y() {
		using namespace mappings;
		jfieldID motion_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "motionY"), getFieldSignature("Entity", "motionY"));
		return minecraft->m_jenv->GetDoubleField(java_class, motion_y);
	}

	double mot_z() {
		using namespace mappings;
		jfieldID motion_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "motionZ"), getFieldSignature("Entity", "motionZ"));
		return minecraft->m_jenv->GetDoubleField(java_class, motion_z);
	}

	bool is_on_ground() {
		using namespace mappings;
		jfieldID on_ground = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "onGround"), getFieldSignature("Entity", "onGround"));
		return minecraft->m_jenv->GetBooleanField(java_class, on_ground);
	}

	void set_position(vec3_t pos) {
		using namespace mappings;
		jmethodID set_position = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "setPosition"), getMethodSignature("Entity", "setPosition"));
		return minecraft->m_jenv->CallVoidMethod(java_class, set_position, pos.x, pos.y, pos.z);
	}

	void set_velocity(vec3_t velocity) {
		using namespace mappings;
		jmethodID set_velocity = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "setVelocity"), getMethodSignature("Entity", "setVelocity"));
		return minecraft->m_jenv->CallVoidMethod(java_class, set_velocity, velocity.x, velocity.y, velocity.z);
	}

	void add_velocity(vec3_t velocity) {
		using namespace mappings;
		jmethodID add_velocity = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "addVelocity"), getMethodSignature("Entity", "addVelocity"));
		return minecraft->m_jenv->CallVoidMethod(java_class, add_velocity, velocity.x, velocity.y, velocity.z);
	}

	vec3_t angles() {
		return vec3_t(get_pitch(), get_yaw(), 0.f);
	}

	int index() {
		using namespace mappings;
		jmethodID index = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "getEntityId"), getMethodSignature("Entity", "getEntityId"));
		return minecraft->m_jenv->CallIntMethod(java_class, index);
	}

	std::string name() {
		using namespace mappings;
		jmethodID get_name = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "getName"), getMethodSignature("Entity", "getName"));
		jstring name = (jstring) minecraft->m_jenv->CallObjectMethod(java_class, get_name);
		jboolean is_copy = jboolean{ false };
		return std::string(minecraft->m_jenv->GetStringUTFChars(name, &is_copy));
	}

	bool is_valid() {
		return java_class;
	}

	bool is_item() {
		return name().find("item.item") != std::string::npos;
	}

	bool is_alive() {
		using namespace mappings;
		jmethodID alive = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "isAlive"), getMethodSignature("Entity", "isAlive"));
		return minecraft->m_jenv->CallBooleanMethod(java_class, alive);
	}

	void set_yaw(jfloat yaw) {
		using namespace mappings;
		jfieldID set_yaw = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "yaw"), getFieldSignature("Entity", "yaw"));
		minecraft->m_jenv->SetFloatField(java_class, set_yaw, yaw);
	}

	void set_pitch(jfloat pitch) {
		using namespace mappings;
		jfieldID set_pitch = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "pitch"), getFieldSignature("Entity", "pitch"));
		minecraft->m_jenv->SetFloatField(java_class, set_pitch, pitch);
	}

	void set_sprint(jboolean sprinting) {
		using namespace mappings;
		jmethodID set_sprint = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), getMethodName("Entity", "setSprinting"), getMethodSignature("Entity", "setSprinting"));
		minecraft->m_jenv->CallBooleanMethod(java_class, set_sprint, sprinting);
	}

	void set_step_height(jfloat height) {
		using namespace mappings;
		jfieldID step_height = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "stepHeight"), getFieldSignature("Entity", "stepHeight"));
		minecraft->m_jenv->SetFloatField(java_class, step_height, height);
	}

	jobject get_capabilities() {
		using namespace mappings;
		jfieldID get_capabilities = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Entity", "capabilities"), getFieldSignature("Entity", "capabilities"));
		return minecraft->m_jenv->GetObjectField(java_class, get_capabilities);
	}

	void set_flight(jboolean state) {
		using namespace mappings;
		jfieldID set_flight = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(get_capabilities()), getFieldName("PlayerCapabilities", "flight"), getFieldSignature("PlayerCapabilities", "flight"));
		minecraft->m_jenv->SetBooleanField(get_capabilities(), set_flight, state);
	}

	AxisAlignedBB get_bounding_box() {
		using namespace mappings;
		jmethodID get_entity_bounding_box = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), "aR", "Laug;");
		return AxisAlignedBB(minecraft->m_jenv->CallObjectMethod(java_class, get_entity_bounding_box));
	}

private:
	jobject java_class;

	float get_x() {
		jfieldID get_x = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "s", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, get_x);
	}

	float get_y() {
		jfieldID get_y = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "t", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, get_y);
	}

	float get_z() {
		jfieldID get_z = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "u", "D");
		return minecraft->m_jenv->GetDoubleField(java_class, get_z);
	}

	float get_pitch() {
		jfieldID get_pitch = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "z", "F");
		return minecraft->m_jenv->GetFloatField(java_class, get_pitch);
	}

	float get_yaw() {
		jfieldID get_yaw = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "y", "F");
		return minecraft->m_jenv->GetFloatField(java_class, get_yaw);
	}
};

extern c_entity* entity;