/*
 * RefPtr.h
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_TYPEREFPTR_H_
#define SRC_ENGINE_ENTITY_DOMAIN_TYPEREFPTR_H_

#include "../EntitySystemBase.hpp"
#include "AttributeRefPtr.hpp"

namespace inexor {
namespace entity {

    template <class T>
    class TypeRefPtr : public std::shared_ptr<T>
    {
        public:

            typedef std::shared_ptr<T> parent;

            TypeRefPtr() : parent() {}
            TypeRefPtr(T* p) : parent(p) {}
            TypeRefPtr(const std::shared_ptr<T>& r) : parent(r) {}

            template <typename U>
            TypeRefPtr(const std::shared_ptr<U>& r) : parent(r) {}

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
