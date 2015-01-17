/*
 * EntityAttribute.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_
#define SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_

#include <string>

#include "EntitySystemBase.h"

enum {
    ENTATTR_FALSE = 0,
    ENTATTR_TRUE,
    ENTATTR_NULL,
    ENTATTR_NUMBER,
    ENTATTR_STRING
}; // JSON types

class EntityAttribute
{
    public:
        EntityAttribute(int type, std::string name, void* value);
        virtual ~EntityAttribute();

        void SetType(int type);
        int GetType();
        void SetValue(void* value);
        void* GetValue();

        int type;
        std::string name;
        void* value;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityAttribute);
};

#endif /* SRC_ENGINE_ENTITY_ENTITYATTRIBUTE_H_ */
