#include "cube.h"
#include "particles/particles.h"

struct ptest
{

	ptest()
    {
		float mass = 1.0f;
		float density = 1.0f;
		// int lifetime1 = 3500;
		// int rate1 = 1;
		int lifetime2 = 30000;
		int rate2 = 1;
		int lifetime3 = 200;
		int rate3 = 5;

		add_particle_renderer_type("default_billboard_renderer", "shader", "billboard_renderer");

		add_particle_type("simple_billboard", "default_billboard_renderer");

		// add_particle_emitter_type("default_point_emitter", "simple_billboard", mass, density, lifetime1, rate1, "point_emitter");
		add_particle_emitter_type("special_point_emitter", "simple_billboard", mass, density, lifetime2, rate2, "point_emitter");
		add_particle_emitter_type("special_field_emitter", "simple_billboard", mass, density, lifetime3, rate3, "field_emitter");

		add_particle_modifier_type("default_velocity_transformation", vec(0.0f, 0.0f, 0.0f), vec(0.0f, 0.0f, 0.0f), "velocity_transformation");
		add_particle_modifier_type("default_mass_spring_transformation", vec(0.0f, 0.0f, 0.0f), vec(0.0f, 0.0f, 0.0f), "mass_spring_transformation");
		add_particle_modifier_type("default_randomv", vec(0.0f, 0.0f, 0.0f), vec(0.0f, 0.0f, 0.0f), "randomv");
		add_particle_modifier_type("default_randomw", vec(0.0f, 0.0f, 0.0f), vec(0.0f, 0.0f, 0.0f), "randomw");
		add_particle_modifier_type("gravity_point_1", vec(356.0f, 256.0f, 512.0f), vec(0.0f, 0.0f, 0.0f), "gravity_point");
		add_particle_modifier_type("gravity_point_2", vec(256.0f, 768.0f, 512.0f), vec(0.0f, 0.0f, 0.0f), "gravity_point");
		add_particle_modifier_type("gravity_point_3", vec(768.0f, 768.0f, 514.0f), vec(0.0f, 0.0f, 0.0f), "gravity_point");

		// assign_modifier_to_emitter("default_point_emitter", "default_velocity_transformation");
		// assign_modifier_to_emitter("default_point_emitter", "default_randomw");
		assign_modifier_to_emitter("special_point_emitter", "default_velocity_transformation");
		assign_modifier_to_emitter("special_point_emitter", "default_mass_spring_transformation");
		assign_modifier_to_emitter("special_point_emitter", "default_randomv");
		assign_modifier_to_emitter("special_point_emitter", "gravity_point_1");
		assign_modifier_to_emitter("special_point_emitter", "gravity_point_2");

		assign_modifier_to_emitter("special_field_emitter", "default_velocity_transformation");
		assign_modifier_to_emitter("special_field_emitter", "default_randomv");
		assign_modifier_to_emitter("special_field_emitter", "default_randomw");
		assign_modifier_to_emitter("special_field_emitter", "gravity_point_3");

		// create_particle_emitter_instance("default_point_emitter", vec(512.0f, 512.0f, 532.0f), vec(0.0f, 0.0f, 150.0f));
		// create_particle_emitter_instance("special_point_emitter", vec(512.0f, 512.0f, 514.0f), vec(80.0f, 0.0f, 0.0f));
		create_particle_emitter_instance("special_point_emitter", vec(512.0f, 512.0f, 514.0f), vec(-40.0f, 0.0f, 0.0f));
		create_particle_emitter_instance("special_field_emitter", vec(768.0f, 768.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
    }

};

ptest *ptest_inst = new ptest();
