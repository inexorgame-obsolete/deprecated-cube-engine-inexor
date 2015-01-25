/*
 * ParticleSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleSubsystem.h"

ParticleSubsystem::ParticleSubsystem() : SubsystemBase(PARTICLE_SUBSYSTEM)
{
}

ParticleSubsystem::ParticleSubsystem(
    CefRefPtr<EntityTypeManager> entity_type_manager,
    CefRefPtr<EntityInstanceManager> entity_instance_manager,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
) : SubsystemBase(PARTICLE_SUBSYSTEM, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager)
{
}
