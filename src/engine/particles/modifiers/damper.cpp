#include "cube.h"
#include "engine/particles/particles.h"

struct velocity_damper : particle_modifier_implementation
{
	/**
	 * The damper.
	 */
	float damper = 0.99f;

	/**
	 * The time unit (1 second).
	 */
	float unit = 1000.0f;

	velocity_damper()
    {
		strcpy(name, newstring("velocity_damper"));
		particle_modifier_implementations.add(this);
    }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		p_inst->vel.mul(damper * (elapsedtime / unit));
	}

};

velocity_damper *ps_modifier_velocity_damper = new velocity_damper();
