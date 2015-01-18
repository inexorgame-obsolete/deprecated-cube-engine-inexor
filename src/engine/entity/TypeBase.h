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
#include "EntityAction.h"

class TypeBase
{
    public:
        TypeBase(std::string name, bool persist, bool synchronize);
        virtual ~TypeBase();

        std::string GetUuid();
        std::string GetName();
        bool IsPersisting();
        bool IsSynchronizing();

        AttributeCefRefPtr operator[](std::string key) const;
        AttributeCefRefPtr & operator[](std::string key);

        void AddAttribute(std::string key, AttributeCefRefPtr attribute) {
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

        AttributeCefRefPtr GetAttribute(std::string key) {
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
        std::map<std::string, AttributeCefRefPtr> attributes;

        /**
         * The actions which are available on instances of this type.
         */
        std::map<std::string, CefRefPtr<EntityAction> > actions;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TypeBase);
};

template <class T>
class TypeCefRefPtr : public CefRefPtr<T> {
    public:
        typedef CefRefPtr<T> parent;

        TypeCefRefPtr() : parent() {
        }

        TypeCefRefPtr(T* p) : parent(p) {
        }

        TypeCefRefPtr(const CefRefPtr<T>& r) : parent(r) {
        }

        template <typename U>
        TypeCefRefPtr(const CefRefPtr<U>& r) : parent(r) {
        }

        AttributeCefRefPtr operator[](std::string key) const
        {
            AttributeCefRefPtr attribute = this->get()->GetAttribute(key);
            attribute->name = key;
            return attribute;
        };

};

#endif /* SRC_ENGINE_ENTITY_TYPEBASE_H_ */
