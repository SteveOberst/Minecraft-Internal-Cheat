#pragma once
#include "c_minecraft.h"

class c_movingobjectposition
{
private:
	jobject java_class;

public:
	c_movingobjectposition();
	c_movingobjectposition(jobject java_class) {
		this->java_class = java_class;
	}
	
	const char* to_string()
	{
		jmethodID method = minecraft->m_jenv->GetMethodID(minecraft->m_jenv->GetObjectClass(java_class), "toString", "()Ljava/lang/String;");
		jstring str = (jstring)minecraft->m_jenv->CallObjectMethod(java_class, method);
		jboolean is_copy = jboolean{ true };
		return (minecraft->m_jenv->GetStringUTFChars(str, &is_copy));
	}

	jobject type() {
		jfieldID type = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), "a"/*typeOfHit*/, "Lauh/a;"/*MovingObjectPosition.MovingObjectType*/);
		return minecraft->m_jenv->GetObjectField(java_class, type);
	}

	bool is_miss() {
		return std::string(to_string()).find("type=MISS") != std::string::npos;
	}

	bool is_block() {
		return std::string(to_string()).find("type=BLOCK"/*BLOCK*/) != std::string::npos;
	}

	bool is_entity() {
		return std::string(to_string()).find("type=ENTITY"/*ENTITY*/) != std::string::npos;
	}
};