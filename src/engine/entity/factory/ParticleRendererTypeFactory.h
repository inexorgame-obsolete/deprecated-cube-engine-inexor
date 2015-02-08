/*
 * ParticleRendererTypeFactory.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLERENDERERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLERENDERERTYPEFACTORY_H_

#include "EntityTypeFactory.h"
#include "../subsystem/particle/ParticleModel.h"
#include "../domain/TypeRefPtr.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"

namespace inexor {
namespace entity {
namespace particle {

class ParticleRendererTypeFactory : public EntityTypeFactory
{
    public:
        ParticleRendererTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ParticleRendererTypeFactory();

        TypeRefPtr<EntityType> Create(std::string name_suffix);
        TypeRefPtr<EntityType> Create(std::string name_suffix, FunctionRefPtr function);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleRendererTypeFactory);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLERENDERERTYPEFACTORY_H_ */
