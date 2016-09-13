/*
 * PointEmitter.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "Point.h"

namespace inexor {
namespace entity {
namespace particle {

Point::Point() : EntityFunction(EMITTER_POINT_FUNCTION)
{
    emitted_by = entity_system->GetRelationshipTypeManager()->Get(REL_EMITTED_BY);
}

Point::~Point()
{
}

void Point::Execute(TimeStep time_step, EntityInstance* emitter_inst, EntityInstance* particle_inst)
{

    // InstanceRefPtr<EntityInstance> particle_inst = entity_system->GetEntityInstanceManager()->Create(particle_type);
    // InstanceRefPtr<EntityInstance> particle_inst = particle;

    /**
     * The current position of the particle instance. May be overwritten by an
     * initializer.
     */
    (*particle_inst)[POS] = vec(emitter_inst->GetAttribute(POS)->vec3Val);

    /**
     * The last current position of the particle instance.
     */
    (*particle_inst)[LAST_POS] = vec(emitter_inst->GetAttribute(LAST_POS)->vec3Val);

    /**
     * The current velocity of the particle instance. The last velocity can be
     * calculated by the current and last position of the particle instance.
     */
    (*particle_inst)[VELOCITY] = vec(emitter_inst->GetAttribute(VELOCITY)->vec3Val);

    /**
     * The remaining iterations of the particle instance. There might be
     * particle modifiers that change the remaining lifetime, for example
     * particle culling would set the remaining iterations to zero.
     */
    (*particle_inst)[REMAINING] = emitter_inst->GetAttribute(LIFETIME)->intVal;

    /**
     * The elapsed iterations since birth. This attribute gets constantly
     * increased and should not be modified. It also might differ to
     * calculating (lifetime - remaining iterations) if the remaining
     * iterations attribute was modified. If you need a constant change
     * over time, you should use this!
     */
    // particle_inst[ELAPSED] = 0;

    /**
     * The time elapsed in the previous iteration.
     */
    // particle_inst[LAST_ELAPSED] = 0;

    /**
     * Rolling particles
     */
    (*particle_inst)[ROLL] = 0.0f;

    /**
     * Every particle instance has a mass. Needed for modifiers which are
     * applying physical transformations like gravity.
     */
    (*particle_inst)[MASS] = 1.0f;

    /**
     * The density (or volume) of the particle. Needed for volumetric
     * rendering (for example metaballs or cloth).
     */
    (*particle_inst)[DENSITY] = 1.0f;

/*
    // Create relationship from particle to emitter
    entity_system->GetRelationshipInstanceManager()->CreateInstance(
        // The relationship type
        emitted_by,
        // Start node: The particle instance
        particle_inst,
        // End node: The emitter instance
        emitter_inst
    );

    // TODO: Call all initializers
    for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = emitter_inst->outgoing[apply_initializer].begin(); it != emitter_inst->outgoing[apply_initializer].end(); ++it)
    {
        (*it)->endNode->GetType()[PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME]->functionVal(time_step, emitter_inst, (*it)->endNode.get(), particle_inst.get());
    }

    // The emitter instance has relationships to modifiers:
    //
    //     emitter--[:apply_modifier]-->modifier
    //
    // This means that each of these connected modifiers should be applied
    // on the newly created particle. Therefore we connect the newly created
    // particle with the modifier:
    //
    //     modifier--[:modifies]-->particle
    //
    for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = emitter_inst->outgoing[apply_modifier].begin(); it != emitter_inst->outgoing[apply_modifier].end(); ++it)
    {
        entity_system->GetRelationshipInstanceManager()->CreateInstance(
            // The relationship type
            modifies,
            // Start node: The modifier instance (which is the end node of the
            // apply_modifiers relationship)
            (*it)->endNode,
            // End node: The particle instance
            particle_inst
        );
    }

    // Create relationship from the renderer instance to the newly created particle instance
    for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = emitter_inst->outgoing[apply_renderer].begin(); it != emitter_inst->outgoing[apply_renderer].end(); ++it)
    {
        entity_system->GetRelationshipInstanceManager()->CreateInstance(
            // The relationship type
            renders,
            // Start node: The renderer instance (which is the end node of the
            // apply_renderers relationship)
            (*it)->endNode,
            // End node: The particle instance
            particle_inst
        );
    }
*/

}

}
}
}
