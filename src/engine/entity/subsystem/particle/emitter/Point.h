/*
 * Point.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINT_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINT_H_

#include "../../../EntitySystemBase.h"
#include "../ParticleSubsystem.h"
#include "../../../EntitySystem.h"
#include "../../../domain/graph/EntityFunction.h"

namespace inexor {
namespace entity {
namespace particle {

/**
 * The point emitter emits particle at the position of the emitter. The point
 * emitter is an EntityFunction which accepts the particle type and the emitter
 * instance as parameters.
 */
class Point : public EntityFunction
{
    public:
        Point();
        virtual ~Point();

        void Execute(TimeStep time_step, EntityType* particle_type, EntityInstance* emitter_inst);

    private:
        /**
         * The relationship type:
         *
         *     particle--[:emitted_by]-->emitter
         *
         */
        TypeRefPtr<RelationshipType> emitted_by;

        /**
         * The relationship type:
         *
         *     emitter--[:apply_initializer]-->initializer
         *
         */
        TypeRefPtr<RelationshipType> apply_initializer;

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
         *     emitter--[:apply_renderer]-->renderer
         *
         */
        TypeRefPtr<RelationshipType> apply_renderer;

        /**
         * The relationship type:
         *
         *     modifier--[:modifies]-->particle
         */
        TypeRefPtr<RelationshipType> modifies;

        /**
         * The relationship type:
         *
         *     renderer--[:renders]-->particle
         */
        TypeRefPtr<RelationshipType> renders;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(Point);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EMITTER_POINT_H_ */
