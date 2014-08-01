#include "cube.h"
#include "engine/particles/particles.h"

struct velocity_transformation : public particle_modifier_implementation
{

	velocity_transformation() : particle_modifier_implementation("velocity_transformation") {
		particle_modifier_implementations.add(this);
	}
	virtual ~velocity_transformation() { }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / particle_frame;
		p_inst->o.x += p_inst->vel.x * f;
		p_inst->o.y += p_inst->vel.y * f;
		p_inst->o.z += p_inst->vel.z * f;
		// conoutf("velocity_transformation:modify(x: %2.1f y: %2.1f z: %2.1f --- %2.3f --- type: %2d, emitter: %3d, elapsedtime: %4d)", p_inst->o.x, p_inst->o.y, p_inst->o.z, f, p_inst->type, p_inst->emitter, elapsedtime);
	}

};

velocity_transformation *ps_modifier_velocity_transformation = new velocity_transformation();
