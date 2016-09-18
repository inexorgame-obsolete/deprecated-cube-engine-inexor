/*
 * InstanceBase.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_INSTANCEBASE_H_
#define SRC_ENGINE_ENTITY_DOMAIN_INSTANCEBASE_H_

#include "inexor/util/uuid.hpp"

#include "../EntitySystemBase.hpp"
#include "AttributeBase.hpp"

namespace inexor {
namespace entity {

    class InstanceBase : public AttributeBase
    {
        public:
        
            InstanceBase();
            InstanceBase(std::string uuid);
            virtual ~InstanceBase();

            std::string GetUuid();
            void SetUuid(std::string uuid);

        // protected:

            std::string uuid;

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(InstanceBase);

    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_INSTANCEBASE_H_ */
