#pragma once

#include "c_minecraft.h"

#include "Mapping.h"

class c_timer
{
private:
	jobject java_class;

public:
	c_timer();
	c_timer(jobject java_class) {
		this->java_class = java_class;
	}

	void set_timer(float speed) {
		using namespace mappings;
		jfieldID timer_speed = minecraft->m_jenv->GetFieldID(minecraft->m_jenv->GetObjectClass(java_class), getFieldName("Timer", "timerSpeed"), getFieldSignature("Timer", "timerSpeed"));
		minecraft->m_jenv->SetFloatField(java_class, timer_speed, speed);
	}

	void reset_timer() {
		set_timer(1.f);
	}
};