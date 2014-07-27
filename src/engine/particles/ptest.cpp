#include "cube.h"
#include "particles/particles.h"

struct ptest
{

	ptest()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 1010;
		int rate = 20;

		add_particle_renderer_type("default_billboard_renderer", "shader", "billboard_renderer");
		add_particle_type("simple_billboard", "default_billboard_renderer");
		add_particle_emitter_type("default_point_emitter", "simple_billboard", mass, density, lifetime, rate, "point_emitter");
		add_particle_modifier_type("default_velocity_transformation", "velocity_transformation");
		add_particle_modifier_type("default_mass_spring_transformation", "mass_spring_transformation");
		assign_modifier_to_emitter("default_point_emitter", "default_velocity_transformation");
		create_particle_emitter_instance("default_point_emitter", vec(0, 0, 0));
    }

};

ptest *ptest_inst = new ptest();
