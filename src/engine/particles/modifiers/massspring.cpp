#include "cube.h"
#include "engine/particles/particles.h"

struct mass_spring_transformation : public particle_modifier_implementation
{

	mass_spring_transformation() : particle_modifier_implementation("mass_spring_transformation") {
		particle_modifier_implementations.add(this);
	}
	virtual ~mass_spring_transformation() { }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		// conoutf("mass_spring_transformation:modify(type: %d, emitter: %d, elapsedtime: %d)", pi.type, pi.emitter, elapsedtime);
	}

};

mass_spring_transformation *ps_modifier_mass_spring_transformation = new mass_spring_transformation();
