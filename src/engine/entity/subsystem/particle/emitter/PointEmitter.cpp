/*
 * PointEmitter.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "PointEmitter.h"

namespace inexor {
namespace entity {
namespace particle {

PointEmitter::PointEmitter() : EntityFunction(POINT_EMITTER_FUNCTION)
{
    emitted_by = entity_system->GetRelationshipTypeManager()->Get(REL_EMITTED_BY);
    apply_modifier = entity_system->GetRelationshipTypeManager()->Get(REL_APPLY_MODIFIER);
    modifies = entity_system->GetRelationshipTypeManager()->Get(REL_MODIFIES);
}

PointEmitter::~PointEmitter()
{
}

void PointEmitter::Execute(TimeStep time_step, EntityType* particle_type, EntityInstance* emitter_inst)
{

    // TODO: fetch dead particle from pool instead of creating new
    // TODO: migrate rate / batch from the old...
    // TODO:

    InstanceRefPtr<EntityInstance> particle_inst = entity_system->GetEntityInstanceManager()->Create(particle_type);

    /**
     * The current position of the particle instance. May be overwritten by an
     * initializer.
     */
    particle_inst[POS] = vec(emitter_inst->GetAttribute("pos")->vec3Val);
    /*
    particle_inst["x"]->doubleVal = emitter_inst->GetAttribute("x")->doubleVal;
    particle_inst["y"]->doubleVal = emitter_inst->GetAttribute("y")->doubleVal;
    particle_inst["z"]->doubleVal = emitter_inst->GetAttribute("z")->doubleVal;
    */

    /**
     * The last current position of the particle instance.
     */
    particle_inst[LAST_POS] = vec(emitter_inst->GetAttribute(LAST_POS)->vec3Val);
    /*
    particle_inst["lx"]->doubleVal = emitter_inst->GetAttribute("x")->doubleVal;
    particle_inst["ly"]->doubleVal = emitter_inst->GetAttribute("y")->doubleVal;
    particle_inst["lz"]->doubleVal = emitter_inst->GetAttribute("z")->doubleVal;
    */

    /**
     * The current velocity of the particle instance. The last velocity can be
     * calculated by the current and last position of the particle instance.
     */
    particle_inst[VELOCITY] = vec(emitter_inst->GetAttribute(VELOCITY)->vec3Val);
    /*
    particle_inst["vx"]->doubleVal = emitter_inst->GetAttribute("vx")->doubleVal;
    particle_inst["vy"]->doubleVal = emitter_inst->GetAttribute("vy")->doubleVal;
    particle_inst["vz"]->doubleVal = emitter_inst->GetAttribute("vz")->doubleVal;
    */

    /**
     * The remaining iterations of the particle instance. There might be
     * particle modifiers that change the remaining lifetime, for example
     * particle culling would set the remaining iterations to zero.
     */
    particle_inst[REMAINING] = emitter_inst->GetAttribute(LIFETIME)->intVal;

    /**
     * The elapsed iterations since birth. This attribute gets constantly
     * increased and should not be modified. It also might differ to
     * calculating (lifetime - remaining iterations) if the remaining
     * iterations attribute was modified. If you need a constant change
     * over time, you should use this!
     */
    particle_inst[ELAPSED] = 0;

    /**
     * The time elapsed in the previous iteration.
     */
    particle_inst[LAST_ELAPSED] = 0;

    /**
     * Rolling particles
     */
    particle_inst[ROLL] = 0.0;

    /**
     * Every particle instance has a mass. Needed for modifiers which are
     * applying physical transformations like gravity.
     */
    particle_inst[MASS] = 0.0;

    /**
     * The density (or volume) of the particle. Needed for volumetric
     * rendering (for example metaballs or cloth).
     */
    particle_inst[DENSITY] = 0.0;

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
    std::list<InstanceRefPtr<RelationshipInstance> > apply_modifiers = emitter_inst->GetAllOutgoingRelationshipsOfType(apply_modifier);
    for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = apply_modifiers.begin(); it != apply_modifiers.end(); ++it)
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

    // TODO: Create relationship from the renderer instance to the newly created particle instance

    // TODO: remove debug
    // logoutf("particle instance emitted");
}

}
}
}
