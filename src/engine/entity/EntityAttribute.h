/*
 * EntityAttribute.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_
#define SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_

#include <string>

#include "EntitySystemBase.h"

enum {
    ENTATTR_FALSE = 0,
    ENTATTR_TRUE,
    ENTATTR_NULL,
    ENTATTR_INT,
    ENTATTR_DOUBLE,
    ENTATTR_STRING
}; // JSON types

class EntityAttribute
{
    public:
        EntityAttribute() : type(ENTATTR_NULL), name(""), intVal(0), doubleVal(0.0), stringVal("") { }
        EntityAttribute(bool value) : type(value), name(""), intVal(0), doubleVal(0.0), stringVal("") { }
        EntityAttribute(int value) : type(ENTATTR_INT), name(""), intVal(value), doubleVal(0.0), stringVal("") { }
        EntityAttribute(double value) : type(ENTATTR_DOUBLE), name(""), intVal(0), doubleVal(value), stringVal("") { }
        EntityAttribute(std::string value) : type(ENTATTR_STRING), name(""), intVal(0), doubleVal(0.0), stringVal(value) { }
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

        int type;
        std::string name;
        int intVal;
        double doubleVal;
        std::string stringVal;

        EntityAttribute& operator=(const EntityAttribute &attribute) {
            logoutf("aa=3");
            type = attribute.type;
            name = attribute.name;
            intVal = attribute.intVal;
            doubleVal = attribute.doubleVal;
            stringVal = attribute.stringVal;
            logoutf("aa=4");
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

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityAttribute);
};

class AttributeCefRefPtr : public CefRefPtr<EntityAttribute> {
    public:
        typedef CefRefPtr<EntityAttribute> parent;

        AttributeCefRefPtr() : parent(new EntityAttribute()) {
        }

        AttributeCefRefPtr(EntityAttribute* p) : parent(p) {
            EntityAttribute* attr = this->get();
            attr->type = p->type;
            attr->name = p->name;
            attr->intVal = p->intVal;
            attr->doubleVal = p->doubleVal;
            attr->stringVal = p->stringVal;
        }

        AttributeCefRefPtr(const CefRefPtr<EntityAttribute>& r) : parent(r) {
            EntityAttribute* attr = this->get();
            attr->type = r->type;
            attr->name = r->name;
            attr->intVal = r->intVal;
            attr->doubleVal = r->doubleVal;
            attr->stringVal = r->stringVal;
        }

        template <typename U>
        AttributeCefRefPtr(const CefRefPtr<U>& r) : parent(r) {
            EntityAttribute* attr = this->get();
            attr->type = r->type;
            attr->name = r->name;
            attr->intVal = r->intVal;
            attr->doubleVal = r->doubleVal;
            attr->stringVal = r->stringVal;
        }

        AttributeCefRefPtr(bool value) : parent(new EntityAttribute(value)) {
        }

        AttributeCefRefPtr(int value) : parent(new EntityAttribute(value)) {
        }

        AttributeCefRefPtr(double value) : parent(new EntityAttribute(value)) {
        }

        AttributeCefRefPtr(std::string value) : parent(new EntityAttribute(value)) {
        }

        EntityAttribute& operator=(const EntityAttribute &attribute) {
            EntityAttribute* attr = this->get();
            attr->type = attribute.type;
            attr->intVal = attribute.intVal;
            attr->doubleVal = attribute.doubleVal;
            attr->stringVal = attribute.stringVal;
            return *attr;
        }

        EntityAttribute& operator=(const AttributeCefRefPtr &r) {
            EntityAttribute* attr = this->get();
            attr->type = r->type;
            attr->intVal = r->intVal;
            attr->doubleVal = r->doubleVal;
            attr->stringVal = r->stringVal;
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

};

#endif /* SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_ */
