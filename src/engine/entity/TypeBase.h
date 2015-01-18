/*
 * TypeBase.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_TYPEBASE_H_
#define SRC_ENGINE_ENTITY_TYPEBASE_H_

#include "EntitySystemBase.h"

#include "EntityAttribute.h"
#include "EntityFunction.h"

class TypeBase
{
    public:
        TypeBase(std::string name, bool persist, bool synchronize);
        virtual ~TypeBase();

        std::string GetUuid();
        std::string GetName();
        bool IsPersisting();
        bool IsSynchronizing();

        AttributeRefPtr operator[](std::string key) const;
        AttributeRefPtr & operator[](std::string key);

        void AddAttribute(std::string key, AttributeRefPtr attribute) {
            attribute.get()->name = key;
            attributes[key] = attribute;
        }

        void AddAttribute(std::string key, bool value) {
            attributes[key] = value;
            attributes[key]->type = value;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, int value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_INT;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, double value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_DOUBLE;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, std::string value) {
            attributes[key] = value;
            attributes[key]->type = ENTATTR_STRING;
            attributes[key]->name = key;
        }

        void AddAttribute(std::string key, FunctionRefPtr action) {
            attributes[key] = action;
            attributes[key]->type = ENTATTR_FUNCTION;
            attributes[key]->name = key;
        }

        AttributeRefPtr GetAttribute(std::string key) {
            return attributes[key];
        }

    protected:

        /**
         * The unique identifier of this type.
         */
        std::string uuid;

        /**
         * The name of the type.
         */
        std::string name;

        /**
         * Instances of this type should be persisted.
         */
        bool persist;

        /**
         * Instances of this type should be synchronized.
         */
        bool synchronize;

        /**
         * The attributes of this type.
         */
        std::map<std::string, AttributeRefPtr> attributes;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TypeBase);
};

template <class T>
class TypeRefPtr : public CefRefPtr<T> {
    public:
        typedef CefRefPtr<T> parent;

        TypeRefPtr() : parent() {
        }

        TypeRefPtr(T* p) : parent(p) {
        }

        TypeRefPtr(const CefRefPtr<T>& r) : parent(r) {
        }

        template <typename U>
        TypeRefPtr(const CefRefPtr<U>& r) : parent(r) {
        }

        AttributeRefPtr operator[](std::string key) const
        {
            AttributeRefPtr attribute = this->get()->GetAttribute(key);
            attribute->name = key;
            return attribute;
        };

};

#endif /* SRC_ENGINE_ENTITY_TYPEBASE_H_ */
