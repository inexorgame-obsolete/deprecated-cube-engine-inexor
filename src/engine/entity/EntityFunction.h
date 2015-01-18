/*
 * EntityAction.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_
#define SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_

#include "EntitySystemBase.h"

class TypeBase;
class EntityType;
class RelationshipType;
class EntityInstance;
class RelationshipInstance;

class EntityFunction
{
    public:
        EntityFunction() : name("test") {};
        virtual ~EntityFunction() {};

        void Execute();
        void Execute(TypeBase* type);
        void Execute(EntityType* type);
        void Execute(RelationshipType* type);
        void Execute(EntityInstance* inst);
        void Execute(RelationshipInstance* inst);

        std::string GetName() { return name; };

        void operator()();
        void operator()(TypeBase* type);
        void operator()(EntityType* type);
        void operator()(RelationshipType* type);
        void operator()(EntityInstance* inst);
        void operator()(RelationshipInstance* inst);

    private:
        std::string name;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityFunction);

};

class FunctionRefPtr : public CefRefPtr<EntityFunction> {
    public:
        typedef CefRefPtr<EntityFunction> parent;

        FunctionRefPtr() : parent() {
        }

        FunctionRefPtr(EntityFunction* p) : parent(p) {
        }

        FunctionRefPtr(const CefRefPtr<EntityFunction>& r) : parent(r) {
        }

        template <typename U>
        FunctionRefPtr(const CefRefPtr<U>& r) : parent(r) {
        }

        void operator()();
        void operator()(TypeBase* type);
        void operator()(EntityType* type);
        void operator()(RelationshipType* type);
        void operator()(EntityInstance* inst);
        void operator()(RelationshipInstance* inst);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_ */
