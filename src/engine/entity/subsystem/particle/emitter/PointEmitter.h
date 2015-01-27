/*
 * PointEmitter.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINTEMITTER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINTEMITTER_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"

class PointEmitter : public EntityFunction
{
    public:
        PointEmitter();
        virtual ~PointEmitter();

        void Execute(EntityType* type, EntityInstance* inst);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(PointEmitter);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINTEMITTER_H_ */
