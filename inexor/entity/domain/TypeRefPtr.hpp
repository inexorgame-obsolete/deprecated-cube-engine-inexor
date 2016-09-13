/*
 * RefPtr.h
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_TYPEREFPTR_H_
#define SRC_ENGINE_ENTITY_DOMAIN_TYPEREFPTR_H_

#include "../EntitySystemBase.h"
#include "AttributeRefPtr.h"

namespace inexor {
namespace entity {

template <class T>
class TypeRefPtr : public CefRefPtr<T> {
    public:
        typedef CefRefPtr<T> parent;

        TypeRefPtr() : parent() {}
        TypeRefPtr(T* p) : parent(p) {}
        TypeRefPtr(const CefRefPtr<T>& r) : parent(r) {}

        template <typename U>
        TypeRefPtr(const CefRefPtr<U>& r) : parent(r) {}

        AttributeRefPtr operator[](std::string key) const
        {
            AttributeRefPtr attribute = this->get()->GetAttribute(key);
            if (!attribute->initialized) {
                attribute->name = key;
                attribute->initialized = true;
            }
            return attribute;
        };

};

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_TYPEREFPTR_H_ */
