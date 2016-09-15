/*
 * Origin.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef ENTITY_SUBSYSTEM_PARTICLE_RENDERER_ORIGIN_H_
#define ENTITY_SUBSYSTEM_PARTICLE_RENDERER_ORIGIN_H_

#include "../../../EntitySystemBase.hpp"
#include "../ParticleSubsystem.hpp"
#include "../../../EntitySystem.hpp"
#include "../../../domain/graph/EntityFunction.hpp"

extern void enablepolygonoffset(GLenum type);
extern void disablepolygonoffset(GLenum type);

namespace inexor {
namespace entity {
namespace particle {

    class Origin : public EntityFunction
    {
        public:

            Origin();
            virtual ~Origin();

            /**
             * Executed before particles are rendered.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             */
            void Before(TimeStep time_step, EntityInstance* renderer_inst);

            /**
             * Executed for each particle.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             * @param particle_inst The particle instance.
             */
            void Execute(TimeStep time_step, EntityInstance* renderer_inst, EntityInstance* particle_inst);

            /**
             * Executed after particles are rendered.
             * @param time_step The time step.
             * @param renderer_inst The renderer instance.
             */
            void After(TimeStep time_step, EntityInstance* renderer_inst);

        private:
            /**
             * The relationship type:
             *
             *     particle--[:emitted_by]-->emitter
             *
             */
            TypeRefPtr<RelationshipType> emitted_by;

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(Origin);

    };

}
}
}

#endif /* ENTITY_SUBSYSTEM_PARTICLE_RENDERER_ORIGIN_H_ */
