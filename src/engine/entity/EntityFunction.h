/*
 * EntityAction.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_
#define SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_

#include "EntitySystemBase.h"

class EntityFunction
{
    public:
        EntityFunction() : name("test") {};
        virtual ~EntityFunction() {};

        void Execute() {};
        std::string GetName() { return name; };

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

};

#endif /* SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_ */
