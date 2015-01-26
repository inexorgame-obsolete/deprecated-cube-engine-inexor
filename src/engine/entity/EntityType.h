/*
 * EntityType.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYTYPE_H_
#define SRC_ENGINE_ENTITY_ENTITYTYPE_H_

#include "TypeBase.h"

class EntityType : public TypeBase
{
    public:
        EntityType(std::string name, bool persist, bool synchronize);
        virtual ~EntityType() {};

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityType);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYTYPE_H_ */
