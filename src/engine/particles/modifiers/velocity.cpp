#include "cube.h"
#include "engine/particles/particles.h"

struct velocity_transformation : particle_modifier_implementation
{
	velocity_transformation()
    {
		strcpy(name, newstring("velocity_transformation"));
		particle_modifier_implementations.add(this);
    }

	void modify(particle_modifier_instance pm_inst, particle_instance pi, int elapsedtime) {
		conoutf("velocity_transformation:modify(type: %d, emitter: %d, elapsedtime: %d)", pi.type, pi.emitter, elapsedtime);
		// pi.o.add()
	}

};

velocity_transformation *ps_modifier_velocity_transformation = new velocity_transformation();
