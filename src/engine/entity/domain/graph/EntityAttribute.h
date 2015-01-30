/*
 * EntityAttribute.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_
#define SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_

#include "../../EntitySystemBase.h"
#include "../TimeStep.h"
#include "../FunctionRefPtr.h"
// #include "../TypeRefPtr.h"

enum {
    ENTATTR_FALSE = 0,
    ENTATTR_TRUE,
    ENTATTR_NULL,
    ENTATTR_INT,
    ENTATTR_FLOAT,
    ENTATTR_DOUBLE,
    ENTATTR_STRING,
    ENTATTR_FUNCTION
    // TODO: vec3, vec4
    // TODO: muparser types
}; // JSON types

class TypeBase;
class EntityType;
class RelationshipType;
class EntityInstance;
class RelationshipInstance;
// class FunctionRefPtr;

class EntityAttribute
{
    public:
        EntityAttribute();
        EntityAttribute(bool value);
        EntityAttribute(int value);
        EntityAttribute(float value);
        EntityAttribute(double value);
        EntityAttribute(std::string value);
        EntityAttribute(FunctionRefPtr value);
        EntityAttribute(FunctionRefPtr *value);
        ~EntityAttribute();

        void SetType(int type);
        int GetType();
        void SetValue(bool value);
        void SetValue(int value);
        void SetValue(float value);
        void SetValue(double value);
        void SetValue(std::string value);
        void SetValue(FunctionRefPtr value);
        bool GetBool();
        int GetInteger();
        double GetFloat();
        double GetDouble();
        std::string GetString();
        FunctionRefPtr GetFunction();

        EntityAttribute& operator=(const EntityAttribute &attribute);
        EntityAttribute& operator=(bool* value);
        EntityAttribute& operator=(int* value);
        EntityAttribute& operator=(float* value);
        EntityAttribute& operator=(double* value);
        EntityAttribute& operator=(std::string* value);
        EntityAttribute& operator=(FunctionRefPtr* value);
        EntityAttribute& operator=(FunctionRefPtr value);

        void operator()(TimeStep time_step);
        void operator()(TimeStep time_step, EntityType* type);
        void operator()(TimeStep time_step, EntityType* type, EntityInstance* inst);
        void operator()(TimeStep time_step, EntityInstance* inst);
        void operator()(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type);
        void operator()(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst);
        void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2);
        void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type);
        void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst);
        void operator()(TimeStep time_step, RelationshipType* type);
        void operator()(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst);
        void operator()(TimeStep time_step, RelationshipInstance* inst);

    // protected:
        int type;
        std::string name;
        int intVal;
        float floatVal;
        double doubleVal;
        std::string stringVal;
        FunctionRefPtr functionVal;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityAttribute);
};

#endif /* SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_ */
