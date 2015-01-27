/*
 * EntityAction.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_
#define SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_

#include "../../EntitySystemBase.h"

class TypeBase;
class EntityType;
class RelationshipType;
class EntityInstance;
class RelationshipInstance;

class EntityFunction
{
    public:
        EntityFunction(std::string name) : name(name) {};
        virtual ~EntityFunction() {};

        // The Execute methods are not implemented. Sub classes can implement
        // whatever they want.
        void Execute() {};
        void Execute(TypeBase* type) {};
        void Execute(EntityType* type) {};
        void Execute(RelationshipType* type) {};
        void Execute(EntityInstance* inst) {};
        void Execute(RelationshipInstance* inst) {};
        void Execute(EntityInstance* entity_instance, RelationshipInstance* relationship_instance) {};
        void Execute(EntityInstance* entity_instance_1, EntityInstance* entity_instance_2) {};
        void Execute(EntityInstance* entity_instance_1, EntityInstance* entity_instance_2, EntityInstance* entity_instance_3) {};
        void Execute(EntityInstance* entity_instance_1, EntityInstance* entity_instance_2, RelationshipInstance* relationship_instance) {};

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
