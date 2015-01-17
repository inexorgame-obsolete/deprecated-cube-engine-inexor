/*
 * EntityAction.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYACTION_H_
#define SRC_ENGINE_ENTITY_ENTITYACTION_H_

#include "EntitySystemBase.h"

class EntityAction
{
    public:
        EntityAction();
        virtual ~EntityAction();
    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityAction);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYACTION_H_ */
