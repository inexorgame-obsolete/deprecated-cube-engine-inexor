/*
 * AttributeRefPtr.hpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_ATTRIBUTEREFPTR_H_
#define SRC_ENGINE_ENTITY_DOMAIN_ATTRIBUTEREFPTR_H_

#include "../EntitySystemBase.hpp"
#include "TimeStep.hpp"
#include "graph/EntityAttribute.hpp"

struct vec;
struct vec4;

namespace inexor {
namespace entity {

    class FunctionRefPtr;
    class EntityType;
    class RelationshipType;
    class EntityInstance;
    class RelationshipInstance;

    /**
     *
     */
    class AttributeRefPtr : public std::shared_ptr<EntityAttribute>
    {
        public:

            typedef std::shared_ptr<EntityAttribute> parent;

            AttributeRefPtr();
            AttributeRefPtr(EntityAttribute* p);
            AttributeRefPtr(const std::shared_ptr<EntityAttribute>& r);

            template <typename U>
            AttributeRefPtr(const std::shared_ptr<U>& r) : parent(r) {
                EntityAttribute* attr = this->get();
                attr->type = r->type;
                attr->name = r->name;
                attr->intVal = r->intVal;
                attr->floatVal = r->floatVal;
                attr->doubleVal = r->doubleVal;
                attr->vec3Val = r->vec3Val;
                attr->vec4Val = r->vec4Val;
                attr->stringVal = r->stringVal;
                attr->functionVal = r->functionVal;
                attr->initialized = true;
            }

            AttributeRefPtr(bool value);
            AttributeRefPtr(int value);
            AttributeRefPtr(float value);
            AttributeRefPtr(double value);
            AttributeRefPtr(vec value);
            AttributeRefPtr(double x, double y, double z);
            AttributeRefPtr(vec4 value);
            AttributeRefPtr(double x, double y, double z, double w);
            AttributeRefPtr(std::string value);
            AttributeRefPtr(FunctionRefPtr value);
            AttributeRefPtr(FunctionRefPtr *value);

            EntityAttribute& operator=(const EntityAttribute &attribute);
            EntityAttribute& operator=(const AttributeRefPtr &r);
            EntityAttribute& operator=(const bool &b);
            EntityAttribute& operator=(const int &i);
            EntityAttribute& operator=(const float &f);
            EntityAttribute& operator=(const double &d);
            EntityAttribute& operator=(const vec &v3);
            EntityAttribute& operator=(const vec4 &v4);
            EntityAttribute& operator=(const std::string &s);
            EntityAttribute& operator=(const FunctionRefPtr &f);
            EntityAttribute& operator=(FunctionRefPtr &f);

            AttributeRefPtr& operator+(const AttributeRefPtr &r);
            int operator+(int i);
            float operator+(float f);
            double operator+(double d);
            std::string operator+(std::string s);

            AttributeRefPtr& operator-(const AttributeRefPtr &r);
            int operator-(int i);
            float operator-(float f);
            double operator-(double d);

            AttributeRefPtr& operator*(const AttributeRefPtr &r);
            int operator*(int i);
            float operator*(float f);
            double operator*(double d);

            AttributeRefPtr& operator/(const AttributeRefPtr &r);
            int operator/(int i);
            float operator/(float f);
            double operator/(double d);

            // AttributeRefPtr& operator+=(const AttributeRefPtr &r);
            AttributeRefPtr& operator+=(int i);
            AttributeRefPtr& operator+=(float f);
            AttributeRefPtr& operator+=(double d);
            AttributeRefPtr& operator+=(std::string s);

            AttributeRefPtr& operator-=(int i);
            AttributeRefPtr& operator-=(float f);
            AttributeRefPtr& operator-=(double d);

            AttributeRefPtr& operator*=(int i);
            AttributeRefPtr& operator*=(float f);
            AttributeRefPtr& operator*=(double d);

            AttributeRefPtr& operator/=(int i);
            AttributeRefPtr& operator/=(float f);
            AttributeRefPtr& operator/=(double d);

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

    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_ATTRIBUTEREFPTR_H_ */
