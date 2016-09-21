/*
 * EntityAttribute.hpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_
#define SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_

#include "inexor/engine/engine.hpp"
// #include "geom.h"
#include "../../EntitySystemBase.hpp"
#include "../TimeStep.hpp"
#include "../FunctionRefPtr.hpp"

namespace inexor {
namespace entity {

    // TODO: implement a named enumeration
    /**
     *
     */
    enum 
    {
        ENTATTR_FALSE = 0,
        ENTATTR_TRUE,
        ENTATTR_NULL,
        ENTATTR_INT,
        ENTATTR_FLOAT,
        ENTATTR_DOUBLE,
        ENTATTR_VEC3,
        ENTATTR_VEC4,
        ENTATTR_STRING,
        ENTATTR_FUNCTION
    }; // JSON types

    class TypeBase;
    class EntityType;
    class RelationshipType;
    class EntityInstance;
    class RelationshipInstance;

    /**
     *
     */
    class EntityAttribute
    {
        public:

            EntityAttribute();
            EntityAttribute(bool value);
            EntityAttribute(int value);
            EntityAttribute(float value);
            EntityAttribute(double value);
            EntityAttribute(vec value);
            EntityAttribute(double x, double y, double z);
            EntityAttribute(vec4 value);
            EntityAttribute(double x, double y, double z, double w);
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
            void SetValue(vec value);
            void SetValue(double x, double y, double z);
            void SetValue(vec4 value);
            void SetValue(double x, double y, double z, double w);
            void SetValue(std::string value);
            void SetValue(FunctionRefPtr value);
            bool GetBool();
            int GetInteger();
            double GetFloat();
            double GetDouble();
            vec GetVec3();
            vec4 GetVec4();
            std::string GetString();
            FunctionRefPtr GetFunction();

            EntityAttribute& operator=(const EntityAttribute &attribute);
            EntityAttribute& operator=(bool* value);
            EntityAttribute& operator=(int* value);
            EntityAttribute& operator=(float* value);
            EntityAttribute& operator=(double* value);
            EntityAttribute& operator=(vec value);
            EntityAttribute& operator=(vec4 value);
            EntityAttribute& operator=(std::string* value);
            EntityAttribute& operator=(FunctionRefPtr* value);
            EntityAttribute& operator=(FunctionRefPtr value);

            void operator()(TimeStep time_step);
            void operator()(TimeStep time_step, std::shared_ptr<EntityType> type);
            void operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type);
            void operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst);
            void operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type);
            void operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst);
            void operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst);

        // protected:

            int type;
            bool initialized;
            std::string name;
            int intVal;
            float floatVal;
            double doubleVal;
            vec vec3Val;
            vec4 vec4Val;
            std::string stringVal;
            FunctionRefPtr functionVal;

    };

}
}

#endif /* SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_ */
