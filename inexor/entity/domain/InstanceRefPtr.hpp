/*
 * InstanceRefPtr.hpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_INSTANCEREFPTR_H_
#define SRC_ENGINE_ENTITY_DOMAIN_INSTANCEREFPTR_H_

#include "../EntitySystemBase.hpp"
#include "AttributeRefPtr.hpp"

namespace inexor {
namespace entity {

    /**
     * 
     */
    template <class T>
    class InstanceRefPtr : public std::shared_ptr<T>
    {
        public:

            /**
             * 
             */
            typedef std::shared_ptr<T> parent;

            /**
             * 
             */
            InstanceRefPtr() : parent() {}

            /**
             * 
             */
            InstanceRefPtr(T* p) : parent(p) {}

            /**
             * 
             */
            InstanceRefPtr(const std::shared_ptr<T>& r) : parent(r) {}

            /**
             * 
             */
            template <typename U>
            InstanceRefPtr(const std::shared_ptr<U>& r) : parent(r) {}

            /**
             * 
             */
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

#endif /* SRC_ENGINE_ENTITY_DOMAIN_INSTANCEREFPTR_H_ */
