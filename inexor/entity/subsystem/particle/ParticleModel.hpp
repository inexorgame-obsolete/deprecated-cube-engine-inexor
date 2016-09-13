/*
 * ParticleModel.h
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLEMODEL_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLEMODEL_H_

#include <string>

namespace inexor {
namespace entity {
namespace particle {

    // The subsystem

    const std::string PARTICLE_SUBSYSTEM("particle");

    // Standard particle attributes

    const std::string POS("pos");
    const std::string LAST_POS("last_pos");
    const std::string VELOCITY("vel");
    const std::string ROLL("roll");
    const std::string MASS("mass");
    const std::string DENSITY("density");
    const std::string GRAVITY("gravity");

    // Particle lifetime

    const std::string REMAINING("remaining");
    const std::string ELAPSED("elapsed");
    const std::string LAST_ELAPSED("last_elapsed");

    // Emitter time step

    const std::string RATE("rate");
    const std::string LIFETIME("lifetime");
    const std::string BATCH_SIZE("batch_size");
    const std::string ENABLED("enabled");
    const std::string MILLIS_TO_PROCESS("millistoprocess");

    // Modifier attributes

    const std::string DAMPER("damper");
    const std::string DELTA("delta");

    // Renderer attributes

    const std::string SIZE("size");
    const std::string TEXTURE("texture");
    const std::string MODEL("model");
    const std::string SHADER("shader");
    const std::string OFFSET("offset");
    const std::string EXPRESSION("expression");

    // Emitter type attributes

    const std::string PARTICLE_TYPE("particle_type");

    // Entity type definitions

    const std::string ENTTYPE_PARENT_PARTICLE_TYPE("particle_type");
    const std::string ENTTYPE_PARENT_EMITTER_TYPE("particle_emitter");
    const std::string ENTTYPE_PARENT_INITIALIZER_TYPE("particle_initializer");
    const std::string ENTTYPE_PARENT_MODIFIER_TYPE("particle_modifier");
    const std::string ENTTYPE_PARENT_RENDERER_TYPE("particle_renderer");

    // Relationship definitions

    const std::string REL_EMITTED_BY("emitted_by");
    const std::string REL_MODIFIES("modifies");
    const std::string REL_RENDERS("renders");
    const std::string REL_APPLY_INITIALIZER("apply_initializer");
    const std::string REL_APPLY_MODIFIER("apply_modifier");
    const std::string REL_APPLY_RENDERER("apply_renderer");

    // Type factories

    const std::string PARTICLE_EMITTER_TYPE_FACTORY("particle_emitter_type_factory");
    const std::string PARTICLE_INITIALIZER_TYPE_FACTORY("particle_initializer_type_factory");
    const std::string PARTICLE_MODIFIER_TYPE_FACTORY("particle_modifier_type_factory");
    const std::string PARTICLE_RENDERER_TYPE_FACTORY("particle_renderer_type_factory");
    const std::string PARTICLE_TYPE_FACTORY("particle_type_factory");

    // Type prefixes

    const std::string ENTTYPE_PREFIX_PARTICLE_EMITTER_TYPE("particle_emitter_type_");
    const std::string ENTTYPE_PREFIX_PARTICLE_INITIALIZER_TYPE("particle_initializer_type_");
    const std::string ENTTYPE_PREFIX_PARTICLE_MODIFIER_TYPE("particle_modifier_type_");
    const std::string ENTTYPE_PREFIX_PARTICLE_RENDERER_TYPE("particle_renderer_type_");
    const std::string ENTTYPE_PREFIX_PARTICLE_TYPE("particle_type_");

    // Function attribute names

    const std::string PARTICLE_EMITTER_FUNCTION_ATTRIBUTE_NAME("emit");
    const std::string PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME("initialize");
    const std::string PARTICLE_MODIFIER_FUNCTION_ATTRIBUTE_NAME("modify");
    const std::string PARTICLE_RENDERER_FUNCTION_ATTRIBUTE_NAME("render");
    const std::string PARTICLE_TYPE_FUNCTION_ATTRIBUTE_NAME("");
    const std::string PARTICLE_TYPE_RENDERER_INSTANCE_ATTRIBUTE_NAME("renderer_instance");

    // Function names

    const std::string EMITTER_POINT_FUNCTION("point_emitter");
    const std::string INITIALIZER_RANDOM_VELOCITY_FUNCTION("random_velocity");
    const std::string MODIFIER_BROWNIAN_MOTION_FUNCTION("brownian_motion");
    const std::string MODIFIER_CULLING_FUNCTION("culling");
    const std::string MODIFIER_DENSITY_FADEOUT_FUNCTION("density_fadeout");
    const std::string MODIFIER_GRAVITY_POINT_FUNCTION("gravity_point");
    const std::string MODIFIER_IMMORTAL_FUNCTION("immortal");
    const std::string MODIFIER_SIMPLE_GRAVITY_FUNCTION("simple_gravity");
    const std::string MODIFIER_ROLLING_FUNCTION("rolling");
    const std::string MODIFIER_VECTOR_FIELD_FUNCTION("vector_field");
    const std::string MODIFIER_VELOCITY_DAMPER_FUNCTION("velocity_damper");
    const std::string MODIFIER_VELOCITY_TRANSFORMATION_FUNCTION("velocity_transformation");
    const std::string RENDERER_BILLBOARD_FUNCTION("billboard_renderer");
    const std::string RENDERER_CUBE_FUNCTION("cube_renderer");
    const std::string RENDERER_MODEL_FUNCTION("model_renderer");
    const std::string RENDERER_ORIGIN_FUNCTION("origin_renderer");

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLEMODEL_H_ */
