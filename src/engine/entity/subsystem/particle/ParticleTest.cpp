/*
 * ParticleTest.cpp
 *
 *  Created on: 14.02.2015
 *      Author: aschaeffer
 */

#include "ParticleTest.h"

namespace inexor {
namespace entity {
namespace particle {

ParticleTest::ParticleTest()
{
    logoutf("Create emitter functions");
    point_emitter_function = new Point();

    logoutf("Create initializer functions");
    color_expression_function = new ColorExpression("0.5, 0.5, 0.5, 0.5");
    position_expression_function = new PositionExpression("ex+30*sin(time),ey+30*cos(time),ez");
    random_position_function = new RandomPosition();
    random_velocity_function = new RandomVelocity();
    velocity_expression_function = new VelocityExpression("32 * sn * sin(time / 1000), 32 * sn * cos(time / 1000), -32 * sn * sin(time / 1000)");

    logoutf("Create modifier functions");
    brownian_motion_function = new BrownianMotion();
    density_fadeout_function = new DensityFadeout();
    geometry_collide_function = new GeometryCollide();
    gravity_point_function = new GravityPoint();
    rolling_function = new Rolling();
    simple_gravity_function = new SimpleGravity();
    vector_field_function = new VectorField("(z * -0.3) * x, (z * -0.2) * y, 20");
    velocity_damper_function = new VelocityDamper();
    velocity_transformation_function = new VelocityTransformation();

    logoutf("Create renderer functions");
    billboard_renderer_function = new Billboard();
    color_billboard_renderer_function = new ColorBillboard();
    cube_renderer_function = new Cube();
    model_renderer_function = new Model();
    origin_renderer_function = new Origin();

    logoutf("Create particle types");
    default_particle_type = particle_subsystem->CreateParticleType("default_particle", "default_renderer");

    logoutf("Create emitter types");
    point_emitter = particle_subsystem->CreateEmitterType("point_emitter", point_emitter_function, default_particle_type, 75, 10, 5000, 1.0, 1.0);

    logoutf("Create initializer types");
    color_expression_initializer_type = particle_subsystem->CreateInitializerType("color_expression_initializer", color_expression_function);
    // color_expression_initializer_type[EXPRESSION] = std::string("0.5, 0.5, 0.5, 0.5");
    // color_expression_initializer_type[EXPRESSION] = std::string("abs(cos(time / ((sn+1) * 90))), abs(sin(time / ((sn+1) * 90))), sin(time / 180) * 0.5 + 0.5, 0.8");
    color_expression_initializer_type[EXPRESSION] = std::string("0.5 + sin(time / 360) / 2.0, 0.5 + abs(cos(time / 360)) / 2.0, 0.0, 0.8");
    position_expression_initializer_type = particle_subsystem->CreateInitializerType("position_expression_initializer", position_expression_function);
    // position_expression_initializer_type[EXPRESSION] = std::string("ex + 90 * cos(time / 2500) * (1 + ((sn div 4) div 4)), ey + 90 * sin(time / 1250) * (1 + ((sn div 4) % 4)), ez + 90 * tanh(time / 500) * (1 + ((sn % 4) % 4))");
    position_expression_initializer_type[EXPRESSION] = std::string("ex + ((sn+10) * 10 * tanh(time / 3600)) * cos(time / 360), ey + ((sn+10) * 10 * tanh(time / 3600)) * sin(time / 360), ez + ((sn+10) * 10 * tanh(time / 3600)) * sin(time / 360)");
    // expression_initializer_type[EXPRESSION] = std::string("ex + 128 * sin(time / 360), ey + 128 * sin(time / 360), ez + 256 * sin(sn / 360)");
    random_position_initializer_type = particle_subsystem->CreateInitializerType("random_position_initializer", random_position_function);
    random_velocity_initializer_type = particle_subsystem->CreateInitializerType("random_velocity_initializer", random_velocity_function);
    velocity_expression_initializer_type = particle_subsystem->CreateInitializerType("velocity_expression_initializer", velocity_expression_function);
    // velocity_expression_initializer_type[EXPRESSION] = std::string("32 * sn * sin(time / 1000), 32 * sn * cos(time / 1000), -32 * sn * sin(time / 1000)");
    velocity_expression_initializer_type[EXPRESSION] = std::string("4 * sn * sin(time / 3600), -4 * sn * cos(time / 3600), -8 * sn");

    logoutf("Create modifier types");
    brownian_motion_modifier_type = particle_subsystem->CreateModifierType("brownian_motion_modifier", brownian_motion_function);
    density_fadeout_modifier_type = particle_subsystem->CreateModifierType("density_fadeout_modifier", density_fadeout_function);
    geometry_collide_modifier_type = particle_subsystem->CreateModifierType("geometry_collide_modifier", geometry_collide_function);
    gravity_point_modifier_type = particle_subsystem->CreateModifierType("gravity_point_modifier", gravity_point_function);
    rolling_modifier_type = particle_subsystem->CreateModifierType("rolling_modifier", rolling_function);
    simple_gravity_modifier_type = particle_subsystem->CreateModifierType("simple_gravity_modifier", simple_gravity_function);
    vector_field_modifier_type = particle_subsystem->CreateModifierType("vector_field_modifier", vector_field_function);
    // vector_field_modifier_type[EXPRESSION] = std::string("y * tanh(time / (1250 * z * sin(time / 1250))), z * tanh(time / (1250 * x * cos(time / 1250))), x * tanh(time / (1250 * y * tanh(time / 1250)))");
    vector_field_modifier_type[EXPRESSION] = std::string("128 * sin(sn / 360), 128 * cos(sn / 360), 256 * cos(sn / 360) * sin(sn / 360)");
    // vector_field_modifier_type[EXPRESSION] = std::string("30 * sin(time / 1250), 30 * sin(time / 1250), 30 * ((x + y) / 2) * cos(time / 512)");
    velocity_damper_modifier_type = particle_subsystem->CreateModifierType("velocity_damper_modifier", velocity_damper_function);
    velocity_damper_modifier_type[DAMPER] = 0.2f;
    velocity_transformation_modifier_type = particle_subsystem->CreateModifierType("velocity_transformation_modifier", velocity_transformation_function);

    logoutf("Create renderer types");
    billboard_renderer_type = particle_subsystem->CreateRendererType("billboard_renderer", billboard_renderer_function);
    color_billboard_renderer_type = particle_subsystem->CreateRendererType("color_billboard_renderer", color_billboard_renderer_function);
    cube_renderer_type = particle_subsystem->CreateRendererType("cube_renderer", cube_renderer_function);
    model_renderer_type = particle_subsystem->CreateRendererType("model_renderer", model_renderer_function);
    origin_renderer_type = particle_subsystem->CreateRendererType("origin_renderer", origin_renderer_function);

}

ParticleTest::~ParticleTest()
{
}

void ParticleTest::RunTests()
{
    ShowCase();
    // PerformanceTest();
}

void ParticleTest::ShowCase()
{
    logoutf("Create emitter instances");
    point_emitter_1 = particle_subsystem->CreateEmitterInstance(point_emitter, 512.0, 512.0, 768.0, 0.0, 0.0, 0.0);
    point_emitter_1[RATE] = 30;
    point_emitter_1[BATCH_SIZE] = 54; // = 3 x 3 x 3
    point_emitter_1[LIFETIME] = 3000;

//    point_emitter_2 = particle_subsystem->CreateEmitterInstance(point_emitter, 512.0, 256.0, 512.0, 0.0, 0.0, 0.0);
//    point_emitter_2[LIFETIME] = 7500;
//    point_emitter_3 = particle_subsystem->CreateEmitterInstance(point_emitter, 768.0, 512.0, 542.0, 0.0, 0.0, 0.0);
//    point_emitter_3[RATE] = 250;
//    point_emitter_3[LIFETIME] = 15000;
//    point_emitter_3[BATCH_SIZE] = 1;
//    point_emitter_4 = particle_subsystem->CreateEmitterInstance(point_emitter, 256.0, 512.0, 512.0, 0.0, 0.0, 0.0);

    logoutf("Create initializer instances");
    color_expression_initializer_1 = particle_subsystem->CreateInitializerInstance(color_expression_initializer_type);
    position_expression_initializer_1 = particle_subsystem->CreateInitializerInstance(position_expression_initializer_type);
    velocity_expression_initializer_1 = particle_subsystem->CreateInitializerInstance(velocity_expression_initializer_type);
    random_velocity_initializer_1 = particle_subsystem->CreateInitializerInstance(random_velocity_initializer_type);
    random_velocity_initializer_1[DELTA] = vec(15.0f, 15.0f, 10.0f);
    random_velocity_initializer_2 = particle_subsystem->CreateInitializerInstance(random_velocity_initializer_type);
    random_velocity_initializer_2[DELTA] = vec(15.0f, 15.0f, 40.0f);
    random_position_initializer_1 = particle_subsystem->CreateInitializerInstance(random_position_initializer_type);
    random_position_initializer_1[DELTA] = vec(25.0f, 25.0f, 0.0f);
    random_position_initializer_2 = particle_subsystem->CreateInitializerInstance(random_position_initializer_type);
    random_position_initializer_2[DELTA] = vec(5.0f, 5.0f, 5.0f);

    logoutf("Create modifier instances");
    geometry_collide_modifier_1 = particle_subsystem->CreateModifierInstance(geometry_collide_modifier_type);
    gravity_point_modifier_1 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_1[MASS] = 5000.0f;
    gravity_point_modifier_1[GRAVITY] = 15.0f;
    gravity_point_modifier_1[POS] = vec(512.0f - 64.0f, 256.0f, 512.0f + 64.0f);
    gravity_point_modifier_2 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_2[MASS] = 5000.0f;
    gravity_point_modifier_2[GRAVITY] = 15.0f;
    gravity_point_modifier_2[POS] = vec(512.0f + 64.0f, 256.0f, 512.0f + 64.0f);
    /*
    gravity_point_modifier_3 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_3[MASS] = 5000.0f;
    gravity_point_modifier_3[GRAVITY] = 15.0f;
    gravity_point_modifier_3[POS] = vec(512.0f, 256.0f + 96.0f, 562.0f);
    gravity_point_modifier_4 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_4[MASS] = 5000.0f;
    gravity_point_modifier_4[GRAVITY] = 15.0f;
    gravity_point_modifier_4[POS] = vec(512.0f, 256.0f - 96.0f, 562.0f);
    */
    rolling_modifier_1 = particle_subsystem->CreateModifierInstance(rolling_modifier_type);
    simple_gravity_modifier_1 = particle_subsystem->CreateModifierInstance(simple_gravity_modifier_type);
    vector_field_modifier_1 = particle_subsystem->CreateModifierInstance(vector_field_modifier_type);
    vector_field_modifier_1[POS] = vec(512.0f, 768.0f, 480.0f);
    velocity_damper_modifier_1 = particle_subsystem->CreateModifierInstance(velocity_damper_modifier_type);
    velocity_transformation_modifier_1 = particle_subsystem->CreateModifierInstance(velocity_transformation_modifier_type);

    logoutf("Create renderer instances");
    billboard_renderer_1 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/ball3.png", 8.0f);
    billboard_renderer_2 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/ball2.png", 5.0f);
    billboard_renderer_3 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/ball3.png", 8.0f);
    billboard_renderer_4 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/base.png", 8.0f);
    billboard_renderer_5 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/flash01.png", 8.0f);
    color_billboard_renderer_1 = particle_subsystem->CreateRendererInstance(color_billboard_renderer_type, "particlepoints", "media/particle/ball2.png", 8.0f);
    model_renderer_1 = particle_subsystem->CreateRendererInstance(model_renderer_type, "projectile/grenade", vec(0.0f, 0.0f, 2.0f));
    cube_renderer_1 = particle_subsystem->CreateRendererInstance(cube_renderer_type, "particlepoints", "media/particle/ball3.png", 3.0f);
    origin_renderer_1 = particle_subsystem->CreateRendererInstance(origin_renderer_type, "particlepoints", "media/particle/ball3.png", 3.0f);

    logoutf("Create relations from emitters to initializers");
    // rel_point_emitter_random_velocity_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, random_velocity_initializer_1);
    // rel_point_emitter_random_position_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, random_position_initializer_1);
    rel_point_emitter_color_expression_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, color_expression_initializer_1);
    rel_point_emitter_position_expression_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, position_expression_initializer_1);
    rel_point_emitter_velocity_expression_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, velocity_expression_initializer_1);
//    rel_point_emitter_random_velocity_2 = particle_subsystem->AddInitializerToEmitter(point_emitter_2, random_velocity_initializer_1);
//    rel_point_emitter_random_velocity_3 = particle_subsystem->AddInitializerToEmitter(point_emitter_3, random_velocity_initializer_2);
//    rel_point_emitter_random_velocity_4 = particle_subsystem->AddInitializerToEmitter(point_emitter_4, random_velocity_initializer_1);
//    rel_point_emitter_random_position_4 = particle_subsystem->AddInitializerToEmitter(point_emitter_4, random_position_initializer_2);

    logoutf("Create relations from emitters to modifiers");
    rel_point_emitter_velocity_transformation_1 = particle_subsystem->AddModifierToEmitter(point_emitter_1, velocity_transformation_modifier_1);
//    rel_point_emitter_vector_field_1 = particle_subsystem->AddModifierToEmitter(point_emitter_1, vector_field_modifier_1);
//    rel_point_emitter_velocity_transformation_2 = particle_subsystem->AddModifierToEmitter(point_emitter_2, velocity_transformation_modifier_1);
//    rel_point_emitter_gravity_point_modifier_1 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_1);
//    rel_point_emitter_gravity_point_modifier_2 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_2);
//    // rel_point_emitter_gravity_point_modifier_3 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_3);
//    // rel_point_emitter_gravity_point_modifier_4 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_4);
//    rel_point_emitter_velocity_transformation_3 = particle_subsystem->AddModifierToEmitter(point_emitter_3, velocity_transformation_modifier_1);
//    rel_point_emitter_rolling_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, rolling_modifier_1);
//    rel_point_emitter_velocity_damper_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, velocity_damper_modifier_1);
//    rel_point_emitter_simple_gravity_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, simple_gravity_modifier_1);
//    rel_point_emitter_geometry_collide_modifier_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, geometry_collide_modifier_1);
//    rel_point_emitter_velocity_transformation_4 = particle_subsystem->AddModifierToEmitter(point_emitter_4, velocity_transformation_modifier_1);

    logoutf("Create relations from emitters to renderers");
//     rel_point_emitter_billboard_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_1, color_billboard_renderer_1);
    rel_point_emitter_color_billboard_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_1, color_billboard_renderer_1);
//    rel_point_emitter_billboard_renderer_2 = particle_subsystem->AddRendererToEmitter(point_emitter_2, billboard_renderer_2);
//    // rel_point_emitter_origin_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_2, origin_renderer_1);
//    rel_point_emitter_model_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_3, model_renderer_1);
//    // rel_point_emitter_cube_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_4, cube_renderer_1);
//    rel_point_emitter_billboard_renderer_3 = particle_subsystem->AddRendererToEmitter(point_emitter_4, billboard_renderer_3);
}

/**
 * 50 emitations per second, 10 particles per emitation, lifetime is 50
 * seconds = 25.000 particles in total.
 */
void ParticleTest::PerformanceTest()
{
    point_emitter_1 = particle_subsystem->CreateEmitterInstance(point_emitter, 512.0, 512.0, 512.0 + 128.0, 0.0, 0.0, 0.0);
    point_emitter_1[RATE] = 20;
    point_emitter_1[LIFETIME] = 2500;
    point_emitter_1[BATCH_SIZE] = 50;

    random_velocity_initializer_1 = particle_subsystem->CreateInitializerInstance(random_velocity_initializer_type);
    random_velocity_initializer_1[DELTA] = vec(100.0f, 100.0f, 25.0f);
    random_position_initializer_1 = particle_subsystem->CreateInitializerInstance(random_position_initializer_type);
    random_position_initializer_1[DELTA] = vec(256.0f, 256.0f, 128.0f);
    brownian_motion_modifier_1 = particle_subsystem->CreateModifierInstance(brownian_motion_modifier_type);
    velocity_transformation_modifier_1 = particle_subsystem->CreateModifierInstance(velocity_transformation_modifier_type);
    billboard_renderer_1 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/flash01.png", 40.0f);

    // particle_subsystem->AddInitializerToEmitter(point_emitter_1, random_velocity_initializer_1);
    particle_subsystem->AddInitializerToEmitter(point_emitter_1, random_position_initializer_1);
    particle_subsystem->AddModifierToEmitter(point_emitter_1, brownian_motion_modifier_1);
    particle_subsystem->AddModifierToEmitter(point_emitter_1, velocity_transformation_modifier_1);
    particle_subsystem->AddRendererToEmitter(point_emitter_1, billboard_renderer_1);
}

}
}
}