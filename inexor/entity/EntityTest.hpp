/*
 * EntityTest.hpp
 *
 *  Created on: 14.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYTEST_H_
#define SRC_ENGINE_ENTITY_ENTITYTEST_H_

#include "EntitySystemBase.hpp"
#include "EntitySystem.hpp"

namespace inexor {
namespace entity {

class EntityTest
{
    public:
        EntityTest();
        virtual ~EntityTest();
        void PrintStats();
        void RunTests();
        void CleanupTests();
        void AttributeTest();
        void InstanceCreationTest();
        void LowLevelTypeCreationTest();
        void LowLevelInstanceCreationTest();

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTest);

};

}
}

#endif /* SRC_ENGINE_ENTITY_ENTITYTEST_H_ */
