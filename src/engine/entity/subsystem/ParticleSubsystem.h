/*
 * ParticleSubsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_

#include "SubsystemBase.h"

#define PARTICLE_SUBSYSTEM "particle"

class ParticleSubsystem : public SubsystemBase
{
    public:
        ParticleSubsystem();
        ParticleSubsystem(
            CefRefPtr<EntityTypeManager> entity_type_manager,
            CefRefPtr<EntityInstanceManager> entity_instance_manager,
            CefRefPtr<RelationshipTypeManager> relationship_type_manager,
            CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
        );
        virtual ~ParticleSubsystem() {};

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleSubsystem);

};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLESUBSYSTEM_H_ */
