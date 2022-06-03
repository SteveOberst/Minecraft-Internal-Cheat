#pragma once

#pragma once

#include "jvmti.h"
#include "c_minecraft.h"

// Wow, we just interact with java and already have a ton of boilerplate...
namespace jvmutil
{
	static jclass getClass(const char* java_class);

	static jclass getClass(jobject& object);

	static jfieldID getFieldID(jclass java_class, const char* field_name, const char* type, bool is_static = false)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return is_static ? environment->GetStaticFieldID(java_class, field_name, type) : environment->GetFieldID(java_class, field_name, type);
	}

	static jmethodID getMethodID(jclass java_class, const char* method_name, const char* type, bool is_static = false)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return is_static ? environment->GetStaticMethodID(java_class, method_name, type) : environment->GetMethodID(java_class, method_name, type);
	}

	static jclass getClass(const char* java_class)
	{
		return minecraft->m_jenv->FindClass(java_class);
	}

	static jclass getClass(jobject& object)
	{
		return minecraft->m_jenv->GetObjectClass(object);
	}

	static jint getIntFieldVal(jobject instance, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetIntField(instance, field_id);
	}

	static jint getIntFieldVal(jclass java_class, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetStaticIntField(java_class, field_id);
	}

	static jint getIntMethodVal(jobject instance, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallIntMethod(instance, method_id);
	}

	static jint getIntMethodVal(jclass java_class, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallStaticIntMethod(java_class, method_id);
	}

	static jdouble getDoubleFieldVal(jobject instance, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetDoubleField(instance, field_id);
	}

	static jdouble getDoubleFieldVal(jclass java_class, jfieldID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetStaticDoubleField(java_class, method_id);
	}

	static jdouble getDoubleMethodVal(jobject instance, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallDoubleMethod(instance, method_id);
	}

	static jdouble getDoubleMethodVal(jclass java_class, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallStaticDoubleMethod(java_class, method_id);
	}

	static jfloat getFloatFieldVal(jobject instance, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetFloatField(instance, field_id);
	}

	static jfloat getFloatFieldVal(jclass java_class, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetStaticFloatField(java_class, field_id);
	}

	static jfloat getFloatMethodVal(jobject instance, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallFloatMethod(instance, method_id);
	}

	static jfloat getFloatMethodVal(jclass java_class, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallStaticFloatMethod(java_class, method_id);
	}

	static jlong getLongFieldVal(jobject instance, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetLongField(instance, field_id);
	}

	static jlong getLongFieldVal(jclass java_class, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetStaticLongField(java_class, field_id);
	}

	static jlong getLongMethodVal(jobject instance, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallLongMethod(instance, method_id);
	}

	static jlong getLongMethodVal(jclass java_class, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallStaticLongMethod(java_class, method_id);
	}

	static jobject getObjectFieldVal(jobject instance, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetObjectField(instance, field_id);
	}

	static jobject getObjectFieldVal(jclass java_class, jfieldID field_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->GetStaticObjectField(java_class, field_id);
	}

	static jobject getObjectMethodVal(jobject instance, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallObjectMethod(instance, method_id);
	}

	static jobject getObjectMethodVal(jclass java_class, jmethodID method_id)
	{
		JNIEnv* environment = minecraft->m_jenv;
		return environment->CallStaticObjectMethod(java_class, method_id);
	}



	/*static jint getIntFieldVal(jobject instance, jfieldID field_id);
	static jint getIntFieldVal(jclass java_class, jfieldID field_id);
	static jint getIntMethodVal(jobject instance, jmethodID method_id);
	static jint getIntMethodVal(jclass java_class, jmethodID method_id);

	static jdouble getDoubleFieldVal(jobject instance, jfieldID field_id);
	static jdouble getDoubleFieldVal(jclass java_class, jfieldID method_id);
	static jdouble getDoubleMethodVal(jobject instance, jmethodID method_id);
	static jdouble getDoubleMethodVal(jclass java_class,  jmethodID method_id);

	static jfloat getFloatFieldVal(jobject instance, jfieldID field_id);
	static jfloat getFloatFieldVal(jclass java_class, jfieldID field_id);
	static jfloat getFloatMethodVal(jobject instance, jmethodID method_id);
	static jfloat getFloatMethodVal(jclass java_class, jmethodID method_id);

	static jlong getLongFieldVal(jobject instance, jfieldID field_id);
	static jlong getLongFieldVal(jclass java_class, jfieldID field_id);
	static jlong getLongMethodVal(jobject instance, jmethodID method_id);
	static jlong getLongMethodVal(jclass java_class, jmethodID method_id);

	static jobject getObjectFieldVal(jobject instance, jfieldID field_id);
	static jobject getObjectFieldVal(jclass java_class, jfieldID field_id);
	static jobject getObjectMethodVal(jobject instance, jmethodID method_id);
	static jobject getObjectMethodVal(jclass java_class, jmethodID method_id);*/
}