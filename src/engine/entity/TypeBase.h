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

    private:

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
        std::map<std::string, CefRefPtr<EntityAttribute> > attributes;

        /**
         * The actions which are available on instances of this type.
         */
        std::map<std::string, CefRefPtr<EntityAction> > actions;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(TypeBase);
};

#endif /* SRC_ENGINE_ENTITY_TYPEBASE_H_ */
