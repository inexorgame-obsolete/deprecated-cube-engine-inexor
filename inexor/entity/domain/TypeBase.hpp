/*
 * TypeBase.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_TYPEBASE_H_
#define SRC_ENGINE_ENTITY_DOMAIN_TYPEBASE_H_

#include "inexor/util/uuid.hpp"
#include "../EntitySystemBase.hpp"
#include "AttributeBase.hpp"

namespace inexor {
namespace entity {

    class TypeBase : public AttributeBase
    {
        public:

            TypeBase(std::string name, bool persist, bool synchronize);
            TypeBase(std::string name, bool persist, bool synchronize, std::string uuid);
            virtual ~TypeBase();

            std::string GetUuid();
            void SetUuid(std::string uuid);

            std::string GetName();
            std::string GetParentType();
            bool IsPersisting();
            bool IsSynchronizing();

            /**
             * The unique identifier of this type.
             */
            std::string uuid;

            /**
             * The name of the type.
             */
            std::string name;

        protected:

            /**
             * The parent type.
             */
            std::string parent_type;

            /**
             * Instances of this type should be persisted.
             */
            bool persist;

            /**
             * Instances of this type should be synchronized.
             */
            bool synchronize;

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(TypeBase);
    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_TYPEBASE_H_ */
