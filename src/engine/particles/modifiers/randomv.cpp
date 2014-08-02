#include "cube.h"
#include "engine/particles/particles.h"

struct randomv : public particle_modifier_implementation
{

	randomv() : particle_modifier_implementation("randomv") {
		particle_modifier_implementations.push_back(this);
	}
	virtual ~randomv() { }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / particle_frame;
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
