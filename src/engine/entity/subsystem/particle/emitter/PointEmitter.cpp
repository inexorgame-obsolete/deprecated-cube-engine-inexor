/*
 * PointEmitter.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "PointEmitter.h"

PointEmitter::PointEmitter() : EntityFunction(POINT_EMITTER_FUNCTION)
{
    emitted_by_type = entity_system->GetRelationshipTypeManager()->Get(REL_EMITTED_BY);
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

    // Position
    particle_inst["x"] = emitter_inst->GetAttribute("x")->doubleVal;
    particle_inst["y"] = emitter_inst->GetAttribute("y")->doubleVal;
    particle_inst["z"] = emitter_inst->GetAttribute("z")->doubleVal;

    /**
     * The last current position of the particle instance.
     */
    particle_inst["lx"] = emitter_inst->GetAttribute("x")->doubleVal;
    particle_inst["ly"] = emitter_inst->GetAttribute("y")->doubleVal;
    particle_inst["lz"] = emitter_inst->GetAttribute("z")->doubleVal;

    /**
     * The current velocity of the particle instance. The last velocity can be
     * calculated by the current and last position of the particle instance.
     */
    particle_inst["vx"] = emitter_inst->GetAttribute("vx")->doubleVal;
    particle_inst["vy"] = emitter_inst->GetAttribute("vy")->doubleVal;
    particle_inst["vz"] = emitter_inst->GetAttribute("vz")->doubleVal;

    /**
     * The remaining iterations of the particle instance. There might be
     * particle modifiers that change the remaining lifetime, for example
     * particle culling would set the remaining iterations to zero.
     */
    particle_inst["remaining"] = 0;

    /**
     * The elapsed iterations since birth. This attribute gets constantly
     * increased and should not be modified. It also might differ to
     * calculating (lifetime - remaining iterations) if the remaining
     * iterations attribute was modified. If you need a constant change
     * over time, you should use this!
     */
    particle_inst["elapsed"] = 0;

    /**
     * The time elapsed in the previous iteration.
     */
    particle_inst["last_elapsed"] = 0;

    /**
     * Rolling particles
     */
    particle_inst["roll"] = 0.0;

    /**
     * Every particle instance has a mass. Needed for modifiers which are
     * applying physical transformations like gravity.
     */
    particle_inst["mass"] = 0.0;

    /**
     * The density (or volume) of the particle. Needed for volumetric
     * rendering (for example metaballs or cloth).
     */
    particle_inst["density"] = 0.0;

    // Create relationship from particle to emitter
    entity_system->GetRelationshipInstanceManager()->CreateInstance(
        // The relationship type
        emitted_by_type,
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
            // Start node: The modifier instance
            (*it)->GetEndNode(),
            // End node: The particle instance
            particle_inst
        );
    }

    // TODO: Create relationship from the renderer instance to the newly created particle instance

    // TODO: remove debug
    // logoutf("particle instance emitted");
}
