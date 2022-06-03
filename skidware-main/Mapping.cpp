#include "Mapping.h"

enum class mappings::MappingType
{
	BADLION_V1_8_9,
	VANILLA_V1_8_8
};

inline std::map<mappings::MappingType, mappings::JMapping*> minecraft_mappings;

const char* mappings::getTranslatedClass(mappings::JClassMapping& class_mapping)
{
	return class_mapping.translatedJavaClass;
}

const char* mappings::getTranslatedField(mappings::JFieldMapping& field_mapping)
{
	return field_mapping.translatedFieldName;
}

const char* mappings::getTranslatedMethod(mappings::JMethodMapping& method_mapping)
{
	return method_mapping.translatedMethodName;
}

const char* mappings::getSignature(mappings::JFieldMapping& field_mapping)
{
	return field_mapping.signature;
}

const char* mappings::getSignature(mappings::JMethodMapping& method_mapping)
{
	return method_mapping.signature;
}

const char* mappings::getMappedClassName(const char* original_name)
{
	mappings::JMapping* mapping = getMapping();
	mappings::JClassMapping class_mapping = mapping->getClassMapping(original_name);
	return getTranslatedClass(class_mapping);
}

const char* mappings::getFieldName(const char* class_name, const char* field_name)
{
	mappings::JMapping* mapping = getMapping();
	mappings::JClassMapping class_mapping = mapping->getClassMapping(class_name);
	mappings::JFieldMapping field_mapping = class_mapping.getFieldMapping(field_name);
	return getTranslatedField(field_mapping);
}

const char* mappings::getMethodName(const char* class_name, const char* method_name)
{
	mappings::JMapping* mapping = getMapping();
	mappings::JClassMapping class_mapping = mapping->getClassMapping(class_name);
	mappings::JMethodMapping method_mapping = class_mapping.getMethodMapping(method_name);
	return getTranslatedMethod(method_mapping);
}

const char* mappings::getFieldSignature(const char* class_name, const char* field_name)
{
	mappings::JMapping* mapping = getMapping();
	mappings::JClassMapping class_mapping = mapping->getClassMapping(class_name);
	mappings::JFieldMapping field_mapping = class_mapping.getFieldMapping(field_name);
	return field_mapping.signature;
}

const char* mappings::getMethodSignature(const char* class_name, const char* method_name)
{
	mappings::JMapping* mapping = getMapping();
	mappings::JClassMapping class_mapping = mapping->getClassMapping(class_name);
	mappings::JMethodMapping method_mapping = class_mapping.getMethodMapping(method_name);
	return method_mapping.signature;
}

mappings::JMapping* mappings::getMapping(mappings::MappingType type)
{
	return minecraft_mappings.at(type);
}

mappings::JMapping* mappings::getMapping()
{
	//TODO: implement auto fetching of mappings
	return mappings::getMapping(mappings::MappingType::VANILLA_V1_8_8);
}

mappings::JMapping::JMapping()
{
}

mappings::JClassMapping mappings::JMapping::newMapping(const char* className, const char* translatedClassName)
{
	return JClassMapping{ className, translatedClassName };
}

// =============== Vanilla (1.8.8) Mappings ===============
void mappings::VanillaMapping::registerMappings()
{
	using namespace mappings;

	// =============== Minecraft ===============
	JClassMapping minecraft_mapping = newMapping("Minecraft", "ave");
	minecraft_mapping.registerFieldMapping("thePlayer", "h", "Lbew;", false);
	minecraft_mapping.registerFieldMapping("theWorld", "f", "Lbdb;", false);
	minecraft_mapping.registerFieldMapping("renderManager", "aa", "Lbiu;", false);
	minecraft_mapping.registerFieldMapping("objectMouseOver", "s", "Lauh;", false);
	minecraft_mapping.registerFieldMapping("timer", "Y", "Lavl;", false);
	minecraft_mapping.registerFieldMapping("inGameHasFocus", "w", "Z", false);
	minecraft_mapping.registerFieldMapping("currentScreen", "m", "Laxu;", false);

	minecraft_mapping.registerMethodMapping("getMinecraft", "A", "()Lave;", true);
	minecraft_mapping.registerMethodMapping("rightClickMouse", "ax", "()V", false);
	minecraft_mapping.registerMethodMapping("leftClickMouse", "aw", "()V", false);

	// =============== Entity ===============
	JClassMapping entity_mapping = newMapping("Entity", "pk");
	entity_mapping.registerFieldMapping("width", "J", "D", false);
	entity_mapping.registerFieldMapping("height", "K", "D", false);
	entity_mapping.registerFieldMapping("motionX", "v", "D", false);
	entity_mapping.registerFieldMapping("motionY", "w", "D", false);
	entity_mapping.registerFieldMapping("motionZ", "x", "D", false);
	entity_mapping.registerFieldMapping("onGround", "C", "Z", false);
	entity_mapping.registerFieldMapping("yaw", "y", "F", false);
	entity_mapping.registerFieldMapping("pitch", "z", "F", false);
	entity_mapping.registerFieldMapping("stepHeight", "S", "F", false);
	entity_mapping.registerFieldMapping("capabilities", "bA", "Lwl;", false);

	entity_mapping.registerMethodMapping("setPosition", "b", "(DDD)V", false);
	entity_mapping.registerMethodMapping("setVelocity", "i", "(DDD)V", false);
	entity_mapping.registerMethodMapping("addVelocity", "g", "(DDD)V", false);
	entity_mapping.registerMethodMapping("getName", "e_", "()Ljava/lang/String;", false);
	entity_mapping.registerMethodMapping("isAlive", "ai", "()Z", false);
	entity_mapping.registerMethodMapping("setSprinting", "d", "(Z)V", false);
	entity_mapping.registerMethodMapping("getEntityBoundingBox", "aR", "Laug;", false);
	entity_mapping.registerMethodMapping("getEntityId", "F", "()I", false);

	// =============== AxisAlignedBB ===============
	JClassMapping axis_aligned_bb_mapping = newMapping("AxisAlignedBB", "aug");
	axis_aligned_bb_mapping.registerFieldMapping("minX", "a", "D", false);
	axis_aligned_bb_mapping.registerFieldMapping("minY", "b", "D", false);
	axis_aligned_bb_mapping.registerFieldMapping("minZ", "c", "D", false);
	axis_aligned_bb_mapping.registerFieldMapping("maxX", "d", "D", false);
	axis_aligned_bb_mapping.registerFieldMapping("maxY", "e", "D", false);
	axis_aligned_bb_mapping.registerFieldMapping("maxZ", "f", "D", false);

	// =============== World ===============
	JClassMapping world_mapping = newMapping("World", "adm");
	world_mapping.registerFieldMapping("loadedPlayerEntities", "j", "Ljava/util/List;", false);
	world_mapping.registerFieldMapping("loadedEntities", "f", "Ljava/util/List;", false);

	// =============== Render Manager ===============
	JClassMapping render_manager_mapping = newMapping("RenderManager", "adm");
	render_manager_mapping.registerFieldMapping("renderPosX", "o", "D", false);
	render_manager_mapping.registerFieldMapping("renderPosY", "p", "D", false);
	render_manager_mapping.registerFieldMapping("renderPosZ", "q", "D", false);

	// =============== Capabilities ===============
	JClassMapping capabilities_mapping = newMapping("PlayerCapabilities", "wl");
	capabilities_mapping.registerFieldMapping("flight", "b", "Z", false);

	// =============== MovingObjectPosition ===============
	JClassMapping moving_object_position_mapping = newMapping("MovingObjectPosition", "auh");
	moving_object_position_mapping.registerFieldMapping("typeOfHit", "a", "Lauh/a;"/*MovingObjectPosition.MovingObjectType*/, false);

	// =============== GuiScreen ===============
	JClassMapping gui_screen_mapping = newMapping("GuiMainMenu", "aya");
	gui_screen_mapping.registerFieldMapping("splashText", "r", "Ljava/lang/String;", false);

	// =============== Timer ===============
	JClassMapping timer_mapping = newMapping("Timer", "avl");
	timer_mapping.registerFieldMapping("timerSpeed", "d", "F", false);

	classMappings.insert({ minecraft_mapping.javaClass, minecraft_mapping });
	classMappings.insert({ entity_mapping.javaClass, entity_mapping });
	classMappings.insert({ capabilities_mapping.javaClass, capabilities_mapping });
	classMappings.insert({ timer_mapping.javaClass, timer_mapping });
	classMappings.insert({ moving_object_position_mapping.javaClass, moving_object_position_mapping });
	classMappings.insert({ render_manager_mapping.javaClass, render_manager_mapping });
	classMappings.insert({ world_mapping.javaClass, world_mapping });
	classMappings.insert({ axis_aligned_bb_mapping.javaClass, axis_aligned_bb_mapping });
	classMappings.insert({ render_manager_mapping.javaClass, render_manager_mapping });
	classMappings.insert({ gui_screen_mapping.javaClass, gui_screen_mapping });
}

mappings::VanillaMapping::VanillaMapping()
{
}

mappings::JClassMapping mappings::VanillaMapping::getClassMapping(const char* className)
{
	return classMappings.at(className);
}

// =============== BLC (1.8.9) ===============
void mappings::BLCMapping::registerMappings()
{
}

mappings::BLCMapping::BLCMapping()
{
}

mappings::JClassMapping mappings::BLCMapping::getClassMapping(const char* className)
{
	return classMappings.at(className);
}

// =============== Class Mapping defs ===============

mappings::JFieldMapping mappings::JClassMapping::getFieldMapping(std::string fieldName)
{
	return this->fields.at(fieldName.c_str());
}

mappings::JMethodMapping mappings::JClassMapping::getMethodMapping(std::string methodName)
{
	return this->methods.at(methodName.c_str());
}

mappings::JFieldMapping mappings::JClassMapping::registerFieldMapping(const char* fieldName, const char* translatedName, const char* type, bool isStatic)
{
	JFieldMapping mapping = JFieldMapping{ this, fieldName, translatedName, type, isStatic };
	this->fields.insert({ fieldName, mapping });
	return mapping;
}

mappings::JMethodMapping mappings::JClassMapping::registerMethodMapping(const char* methodName, const char* translatedName, const char* type, bool isStatic)
{
	JMethodMapping mapping = JMethodMapping{ this, methodName, translatedName, type, isStatic };
	this->methods.insert({ methodName, mapping });
	return mapping;
}

mappings::JClass::JClass(const char* javaClass) : javaClass{ javaClass }
{
	this->mapping = getMapping();
	this->javaClassObj = minecraft->m_jenv->FindClass(javaClass);
}

jfieldID mappings::JClass::getTranslatedField(const char* field_name)
{
	JClassMapping classMapping = mapping->getClassMapping(javaClass);
	JFieldMapping fieldMapping = classMapping.getFieldMapping(field_name);
	return jvmutil::getFieldID(javaClassObj, fieldMapping.translatedFieldName, fieldMapping.signature, false);
}

jmethodID mappings::JClass::getTranslatedMethod(const char* method_name)
{
	JClassMapping classMapping = mapping->getClassMapping(javaClass);
	JMethodMapping methodMapping = classMapping.getMethodMapping(method_name);
	return jvmutil::getMethodID(javaClassObj, methodMapping.translatedMethodName, methodMapping.signature, false);
}

void mappings::register_mappings()
{
	minecraft_mappings.insert({ MappingType::VANILLA_V1_8_8, new VanillaMapping() });

	mappings::getMapping()->registerMappings();
}