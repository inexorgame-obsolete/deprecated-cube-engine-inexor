/*
 * ParticleRendererTypeFactory.cpp
 *
 *  Created on: 07.02.2015
 *      Author: aschaeffer
 */

#include "ParticleRendererTypeFactory.hpp"

namespace inexor {
namespace entity {
namespace particle {

ParticleRendererTypeFactory::ParticleRendererTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager)
    : EntityTypeFactory(PARTICLE_RENDERER_TYPE_FACTORY, PARTICLE_RENDERER_FUNCTION_ATTRIBUTE_NAME, ENTTYPE_PREFIX_PARTICLE_RENDERER_TYPE, entity_type_manager)
{
}

ParticleRendererTypeFactory::~ParticleRendererTypeFactory()
{
}

TypeRefPtr<EntityType> ParticleRendererTypeFactory::Create(std::string name_suffix, FunctionRefPtr function)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    // Set the parent type, so that we know that the entity type is a particle renderer type.
    TypeRefPtr<EntityType> parent_renderer_type = entity_type_manager->Get(ENTTYPE_PARENT_RENDERER_TYPE);
    TypeRefPtr<EntityType> particle_renderer_type = entity_type_manager->Create(entity_type_name, true, true, parent_renderer_type);
    particle_renderer_type[function_attribute_name] = function;
    return particle_renderer_type;
}

}
}
}
