#include "cube.h"
#include "engine/particles/particles.h"

struct gravity_point : particle_modifier_implementation
{
	/**
	 * The gravity.
	 */
	float gravity = 0.8f;

	/**
	 * The mass.
	 */
	float mass = 10000.0f;

	gravity_point()
    {
		strcpy(name, newstring("gravity_point"));
		particle_modifier_implementations.add(this);
    }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
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
		// p_inst->vel.mul(damper * (elapsedtime / unit));
		// float dx = p_inst->o.x - pm_inst->o.x;
		// float dy = p_inst->o.y - pm_inst->o.y;
		// float dz = p_inst->o.z - pm_inst->o.z;
		// float distance = p_inst->o.squaredist(pm_inst->o);
		// Float distance = (float) Math.sqrt(dx * dx + dy * dy + dz * dz);
		// if (distance == 0.0f) distance = 0.00000000001f;
		// Float force = -(particle.getMass()) * mass * gravity / (distance * distance);
		// if (Math.abs(force) > maxForce) force = maxForce;
		// Vector3f accelleration = new Vector3f(
		// 	(force * dx) / (distance * particle.getMass()),
		// 	(force * dy) / (distance * particle.getMass()),
		// 	(force * dz) / (distance * particle.getMass())
		// );
		// Vector3f newVelocity = new Vector3f();
		// Vector3f.add(particle.getVelocity(), accelleration, newVelocity);
		// particle.setVelocity(newVelocity);
	}

};

gravity_point *ps_modifier_gravity_point = new gravity_point();
