#include "cube.h"
#include "engine/particles/particles.h"

struct mass_spring_transformation : particle_modifier_implementation
{

	mass_spring_transformation()
    {
		strcpy(name, newstring("mass_spring_transformation"));
		particle_modifier_implementations.add(this);
    }

	void modify(particle_modifier_instance pm_inst, particle_instance pi, int elapsedtime) {
		conoutf("mass_spring_transformation:modify(type: %d, emitter: %d, elapsedtime: %d)", pi.type, pi.emitter, elapsedtime);
	}

};

mass_spring_transformation *ps_modifier_mass_spring_transformation = new mass_spring_transformation();
