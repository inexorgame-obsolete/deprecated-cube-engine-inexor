/*
 * PulseInitializer.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_PULSEINITIALIZER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_PULSEINITIALIZER_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"

namespace inexor {
namespace entity {
namespace particle {

class PulseInitializer : public EntityFunction
{
    public:
        PulseInitializer();
        virtual ~PulseInitializer();

        void Execute(EntityType* type, EntityInstance* inst);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(PulseInitializer);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_PULSEINITIALIZER_H_ */
