#include "cube.h"
#include "engine/particles/particles.h"

struct randomv : particle_modifier_implementation
{
	/**
	 * The time unit (1 second).
	 */
	float unit = 1000.0f;

	randomv()
    {
		strcpy(name, newstring("randomv"));
		particle_modifier_implementations.add(this);
    }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / unit;
		float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float sx = (rx * 64.0f) - 32.0f;
		float sy = (ry * 64.0f) - 32.0f;
		float sz = (rz * 64.0f) - 32.0f;
		p_inst->vel.x += sx * f;
		p_inst->vel.y += sy * f;
		p_inst->vel.z += sz * f;
	}

};

randomv *ps_modifier_randomv = new randomv();
