#include "cube.h"
#include "engine/particles/particles.h"

struct randomw : public particle_modifier_implementation
{

	randomw() : particle_modifier_implementation("randomw") {
		particle_modifier_implementations.add(this);
	}
	virtual ~randomw() { }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / particle_frame;
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
