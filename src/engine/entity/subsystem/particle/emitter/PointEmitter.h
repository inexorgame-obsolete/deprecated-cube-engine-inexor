/*
 * PointEmitter.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINTEMITTER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINTEMITTER_H_

#include "../../../EntitySystemBase.h"
#include "../ParticleSubsystem.h"
#include "../../../EntitySystem.h"
#include "../../../domain/graph/EntityFunction.h"

#define POINT_EMITTER_FUNCTION "point_emitter"

class PointEmitter : public EntityFunction
{
    public:
        PointEmitter();
        virtual ~PointEmitter();

        void Execute(TimeStep time_step, EntityType* particle_type, EntityInstance* emitter_inst);

    private:
        /**
         * The relationship type:
         *
         *     particle--[:emitted_by]-->emitter
         *
         */
        TypeRefPtr<RelationshipType> emitted_by_type;

        /**
         * The relationship type:
         *
         *     emitter--[:apply_modifier]-->modifier
         *
         */
        TypeRefPtr<RelationshipType> apply_modifier;

        /**
         * The relationship type:
         *
         *     modifier--[:modifies]-->particle
         */
        TypeRefPtr<RelationshipType> modifies;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(PointEmitter);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINTEMITTER_H_ */
