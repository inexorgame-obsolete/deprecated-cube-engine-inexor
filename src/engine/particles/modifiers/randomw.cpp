#include "cube.h"
#include "engine/particles/particles.h"

struct randomw : particle_modifier_implementation
{
	/**
	 * The time unit (1 second).
	 */
	float unit = 1000.0f;

	randomw()
    {
		strcpy(name, newstring("randomw"));
		particle_modifier_implementations.add(this);
    }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / unit;
		float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float sx = (rx * 2.0f) - 1.0f;
		float sy = (ry * 2.0f) - 1.0f;
		float sz = (rz * 2.0f) - 1.0f;
		p_inst->vel.x += sx;
		p_inst->vel.y += sy;
		p_inst->vel.z += sz;
	}

};

randomw *ps_modifier_randomw = new randomw();
