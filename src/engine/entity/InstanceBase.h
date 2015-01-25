/*
 * InstanceBase.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_INSTANCEBASE_H_
#define SRC_ENGINE_ENTITY_INSTANCEBASE_H_

#include "EntitySystemBase.h"
#include "AttributeBase.h"

#include "EntityAttribute.h"
#include "EntityFunction.h"

class InstanceBase : public AttributeBase
{

    public:
        InstanceBase();
        InstanceBase(std::string uuid) : uuid(uuid) {};
        virtual ~InstanceBase() {};

        std::string GetUuid() { return uuid; };
        void SetUuid(std::string uuid) { this->uuid = uuid; };

    private:
        std::string uuid;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InstanceBase);

};

template <class T>
class InstanceRefPtr : public CefRefPtr<T> {
    public:
        typedef CefRefPtr<T> parent;

        InstanceRefPtr() : parent() {
        }

        InstanceRefPtr(T* p) : parent(p) {
        }

        InstanceRefPtr(const CefRefPtr<T>& r) : parent(r) {
        }

        template <typename U>
        InstanceRefPtr(const CefRefPtr<U>& r) : parent(r) {
        }

        AttributeRefPtr operator[](std::string key) const
        {
            AttributeRefPtr attribute = this->get()->GetAttribute(key);
            attribute->name = key;
            return attribute;
        };

};

#endif /* SRC_ENGINE_ENTITY_INSTANCEBASE_H_ */
