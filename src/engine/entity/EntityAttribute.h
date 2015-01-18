/*
 * EntityAttribute.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_
#define SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_

#include <string>

#include "EntityFunction.h"
#include "EntitySystemBase.h"

enum {
    ENTATTR_FALSE = 0,
    ENTATTR_TRUE,
    ENTATTR_NULL,
    ENTATTR_INT,
    ENTATTR_DOUBLE,
    ENTATTR_STRING,
    ENTATTR_FUNCTION
}; // JSON types

class TypeBase;
class EntityType;
class RelationshipType;
class EntityInstance;
class RelationshipInstance;

class EntityAttribute
{
    public:
        EntityAttribute() : type(ENTATTR_NULL), name(""), intVal(0), doubleVal(0.0), stringVal(""), functionVal(0) { }
        EntityAttribute(bool value) : type(value), name(""), intVal(0), doubleVal(0.0), stringVal(""), functionVal(0) { }
        EntityAttribute(int value) : type(ENTATTR_INT), name(""), intVal(value), doubleVal(0.0), stringVal(""), functionVal(0) { }
        EntityAttribute(double value) : type(ENTATTR_DOUBLE), name(""), intVal(0), doubleVal(value), stringVal(""), functionVal(0) { }
        EntityAttribute(std::string value) : type(ENTATTR_STRING), name(""), intVal(0), doubleVal(0.0), stringVal(value), functionVal(0) { }
        EntityAttribute(FunctionRefPtr value) : type(ENTATTR_FUNCTION), name(""), intVal(0), doubleVal(0.0), stringVal(""), functionVal(value) { }
        EntityAttribute(FunctionRefPtr *value) : type(ENTATTR_FUNCTION), name(""), intVal(0), doubleVal(0.0), stringVal(""), functionVal(*value) { }
        ~EntityAttribute() { }

        void SetType(int type)
        {
            this->type = type;
        };
        int GetType()
        {
            return type;
        };
        void SetValue(bool value)
        {
            this->type = value;
        };
        void SetValue(int value)
        {
            this->type = ENTATTR_INT;
            this->intVal = value;
        };
        void SetValue(double value)
        {
            this->type = ENTATTR_DOUBLE;
            this->doubleVal = value;
        };
        void SetValue(std::string value)
        {
            this->type = ENTATTR_STRING;
            this->stringVal = value;
        };
        void SetValue(FunctionRefPtr value)
        {
            this->type = ENTATTR_FUNCTION;
            this->functionVal = value;
        };
        bool GetBool()
        {
            if (this->type == ENTATTR_TRUE) {
                return ENTATTR_TRUE;
            } else {
                return ENTATTR_FALSE;
            }
        };
        int GetInteger()
        {
            if (this->type == ENTATTR_INT) {
                return intVal;
            } else {
                return 0;
            }
        };
        double GetDouble()
        {
            if (this->type == ENTATTR_DOUBLE) {
                return doubleVal;
            } else {
                return 0.0;
            }
        };
        std::string GetString()
        {
            if (this->type == ENTATTR_STRING) {
                return stringVal;
            } else {
                return "";
            }
        };
        FunctionRefPtr GetFunction()
        {
            if (this->type == ENTATTR_FUNCTION) {
                return functionVal;
            } else {
                return 0;
            }
        };

        int type;
        std::string name;
        int intVal;
        double doubleVal;
        std::string stringVal;
        FunctionRefPtr functionVal;

        EntityAttribute& operator=(const EntityAttribute &attribute) {
            type = attribute.type;
            name = attribute.name;
            intVal = attribute.intVal;
            doubleVal = attribute.doubleVal;
            stringVal = attribute.stringVal;
            functionVal = attribute.functionVal;
            return *this;
        };

        EntityAttribute& operator=(bool* value) {
            this->type = *value;
            return *this;
        };

        EntityAttribute& operator=(int* value) {
            this->type = ENTATTR_INT;
            this->intVal = *value;
            return *this;
        };

        EntityAttribute& operator=(double* value) {
            this->type = ENTATTR_DOUBLE;
            this->doubleVal = *value;
            return *this;
        };

        EntityAttribute& operator=(std::string* value) {
            this->type = ENTATTR_STRING;
            this->stringVal = *value;
            return *this;
        };

        EntityAttribute& operator=(FunctionRefPtr* value) {
            this->type = ENTATTR_FUNCTION;
            this->functionVal = *value;
            return *this;
        };

        EntityAttribute& operator=(FunctionRefPtr value) {
            this->type = ENTATTR_FUNCTION;
            this->functionVal = value;
            return *this;
        };

        void operator()();
        void operator()(TypeBase* type);
        void operator()(EntityType* type);
        void operator()(RelationshipType* type);
        void operator()(EntityInstance* inst);
        void operator()(RelationshipInstance* inst);

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityAttribute);
};

class AttributeRefPtr : public CefRefPtr<EntityAttribute> {
    public:
        typedef CefRefPtr<EntityAttribute> parent;

        AttributeRefPtr() : parent(new EntityAttribute()) { }

        AttributeRefPtr(EntityAttribute* p) : parent(p) {
            EntityAttribute* attr = this->get();
            attr->type = p->type;
            attr->name = p->name;
            attr->intVal = p->intVal;
            attr->doubleVal = p->doubleVal;
            attr->stringVal = p->stringVal;
            attr->functionVal = p->functionVal;
        }

        AttributeRefPtr(const CefRefPtr<EntityAttribute>& r) : parent(r) {
            EntityAttribute* attr = this->get();
            attr->type = r->type;
            attr->name = r->name;
            attr->intVal = r->intVal;
            attr->doubleVal = r->doubleVal;
            attr->stringVal = r->stringVal;
            attr->functionVal = r->functionVal;
        }

        template <typename U>
        AttributeRefPtr(const CefRefPtr<U>& r) : parent(r) {
            EntityAttribute* attr = this->get();
            attr->type = r->type;
            attr->name = r->name;
            attr->intVal = r->intVal;
            attr->doubleVal = r->doubleVal;
            attr->stringVal = r->stringVal;
            attr->functionVal = r->functionVal;
        }

        AttributeRefPtr(bool value) : parent(new EntityAttribute(value)) { }

        AttributeRefPtr(int value) : parent(new EntityAttribute(value)) { }

        AttributeRefPtr(double value) : parent(new EntityAttribute(value)) { }

        AttributeRefPtr(std::string value) : parent(new EntityAttribute(value)) { }

        AttributeRefPtr(FunctionRefPtr value) : parent(new EntityAttribute(value)) { }

        AttributeRefPtr(FunctionRefPtr *value) : parent(new EntityAttribute(*value)) { }

        EntityAttribute& operator=(const EntityAttribute &attribute) {
            EntityAttribute* attr = this->get();
            attr->type = attribute.type;
            attr->intVal = attribute.intVal;
            attr->doubleVal = attribute.doubleVal;
            attr->stringVal = attribute.stringVal;
            attr->functionVal = attribute.functionVal;
            return *attr;
        }

        EntityAttribute& operator=(const AttributeRefPtr &r) {
            EntityAttribute* attr = this->get();
            attr->type = r->type;
            attr->intVal = r->intVal;
            attr->doubleVal = r->doubleVal;
            attr->stringVal = r->stringVal;
            attr->functionVal = r->functionVal;
            return *attr;
        }

        EntityAttribute& operator=(const bool &b) {
            EntityAttribute* attr = this->get();
            bool b1 = b;
            attr->type = b1;
            return *attr;
        }

        EntityAttribute& operator=(const int &i) {
            EntityAttribute* attr = this->get();
            attr->type = ENTATTR_INT;
            int i1 = i;
            attr->intVal = i1;
            return *attr;
        }

        EntityAttribute& operator=(const double &d) {
            EntityAttribute* attr = this->get();
            attr->type = ENTATTR_DOUBLE;
            double d1 = d;
            attr->doubleVal = d1;
            return *attr;
        }

        EntityAttribute& operator=(const std::string &s) {
            EntityAttribute* attr = this->get();
            attr->type = ENTATTR_STRING;
            std::string s1 = s;
            attr->stringVal = s1;
            return *attr;
        }

        EntityAttribute& operator=(const FunctionRefPtr &f) {
            EntityAttribute* attr = this->get();
            attr->type = ENTATTR_FUNCTION;
            FunctionRefPtr f1 = f;
            attr->functionVal = f1;
            return *attr;
        }

        EntityAttribute& operator=(FunctionRefPtr &f) {
            EntityAttribute* attr = this->get();
            attr->type = ENTATTR_FUNCTION;
            attr->functionVal = f;
            return *attr;
        }

        void operator()();
        void operator()(TypeBase* type);
        void operator()(EntityType* type);
        void operator()(RelationshipType* type);
        void operator()(EntityInstance* inst);
        void operator()(RelationshipInstance* inst);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_ */
