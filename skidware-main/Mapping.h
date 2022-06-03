#pragma once
#include "jvmti.h"
#include "JvmUtil.h"
#include <map>
#include <string>

namespace mappings
{
	struct JClassMapping;
	struct JMethodMapping;
	class JMapping;

	struct JFieldMapping
	{
		JClassMapping* javaClass;
		const char* fieldName;
		const char* translatedFieldName;
		const char* signature;
		bool isStatic;
	};

	struct JMethodMapping
	{
		JClassMapping* javaClass;
		const char* methodName;
		const char* translatedMethodName;
		const char* signature;
		bool isStatic;
	};

	struct JClassMapping
	{
		const char* javaClass;
		const char* translatedJavaClass;

		std::map<std::string, JFieldMapping> fields;
		std::map<std::string, JMethodMapping> methods;

		JFieldMapping getFieldMapping(std::string fieldName);
		JMethodMapping getMethodMapping(std::string methodName);

		JFieldMapping registerFieldMapping(const char* fieldName, const  char* translatedName, const char* type, bool isStatic);
		JMethodMapping registerMethodMapping(const char* methodName, const char* translatedName, const char* type, bool isStatic);
	};
	
	class JMapping;

	enum class MappingType;

	class JClass
	{
	public:
		JClass(const char* javaClass);

	protected:
		const char* javaClass;
		jclass javaClassObj;
		JMapping* mapping;

		jfieldID getTranslatedField(const char* field_name);
		jmethodID getTranslatedMethod(const char* method_name);

	};

	class JMapping
	{
	public:
		JMapping();

		virtual JClassMapping getClassMapping(const char* className) = 0;

		virtual void registerMappings() = 0;

	protected:
		std::map<std::string, JClassMapping> classMappings;

		JClassMapping newMapping(const char* className, const char* translatedClassName);
	};

	class VanillaMapping : public JMapping
	{
	public:
		VanillaMapping();

		void registerMappings();

		JClassMapping getClassMapping(const char* className);
	};

	class BLCMapping : public JMapping
	{
	public:
		BLCMapping();

		void registerMappings();

		JClassMapping getClassMapping(const char* className);
	};

	void register_mappings(); 

	const char* getTranslatedClass(mappings::JClassMapping& class_mapping);

	const char* getTranslatedField(mappings::JFieldMapping& field_mapping);

	const char* getTranslatedMethod(mappings::JMethodMapping& method_mapping);

	const char* getSignature(mappings::JFieldMapping& field_mapping);

	const char* getSignature(mappings::JMethodMapping& method_mapping);

	const char* getMappedClassName(const char* original_name);

	const char* getFieldName(const char* class_name, const char* field_name);

	const char* getMethodName(const char* class_name, const char* method_name);

	const char* getFieldSignature(const char* class_name, const char* field_name);

	const char* getMethodSignature(const char* class_name, const char* method_name);

	JMapping* getMapping(mappings::MappingType type);

	JMapping* getMapping();
}