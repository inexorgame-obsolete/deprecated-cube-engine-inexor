/*
 * Subsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "SubsystemBase.h"

SubsystemBase::SubsystemBase(std::string name) : name(name)
{
}

SubsystemBase::SubsystemBase(
    std::string name,
    CefRefPtr<EntityTypeManager> entity_type_manager,
    CefRefPtr<EntityInstanceManager> entity_instance_manager,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
) : name(name),
    entity_type_manager(entity_type_manager),
    entity_instance_manager(entity_instance_manager),
    relationship_type_manager(relationship_type_manager),
    relationship_instance_manager(relationship_instance_manager) {}
