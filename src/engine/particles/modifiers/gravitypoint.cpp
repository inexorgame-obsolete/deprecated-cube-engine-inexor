#include "cube.h"
#include "engine/particles/particles.h"

struct gravity_point : public particle_modifier_implementation
{
	/**
	 * The gravity.
	 */
	static const float gravity = 0.8f;

	/**
	 * The mass.
	 */
	static const float mass = 1000.0f;

	gravity_point() : particle_modifier_implementation("gravity_point") {
		particle_modifier_implementations.push_back(this);
	}
	virtual ~gravity_point() { }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float gravity = pm_inst->attributes["gravity"];
		float mass = pm_inst->attributes["mass"];
		float dx = p_inst->o.x - pm_inst->o.x;
		float dy = p_inst->o.y - pm_inst->o.y;
		float dz = p_inst->o.z - pm_inst->o.z;
		float distance = sqrtf(dx * dx + dy * dy + dz * dz);
		if (distance == 0.0f) distance = 0.00000000001f;
		float force = -(p_inst->mass) * mass * gravity / (distance * distance);
		float ax = (force * dx) / (distance * p_inst->mass);
		float ay = (force * dy) / (distance * p_inst->mass);
		float az = (force * dz) / (distance * p_inst->mass);
		p_inst->vel.x += ax;
		p_inst->vel.y += ay;
		p_inst->vel.z += az;
	}

};

gravity_point *ps_modifier_gravity_point = new gravity_point();
