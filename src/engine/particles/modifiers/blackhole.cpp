#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a black hole.
 */
struct black_hole : public particle_modifier_implementation
{

public:

	static black_hole& instance()
	{
		static black_hole _instance;
		return _instance;
	}
	virtual ~black_hole() { }

	/**
	 * Attracts particles.
	 */
	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float gravity = pm_inst->attributes["gravity"];
		float mass = pm_inst->attributes["mass"];
		float dx = p_inst->o.x - pm_inst->o.x;
		float dy = p_inst->o.y - pm_inst->o.y;
		float dz = p_inst->o.z - pm_inst->o.z;
		float distance = sqrtf(dx * dx + dy * dy + dz * dz);
		if (distance < 5.0f) {
			p_inst->remaining = 0;
		} else {
			float force = -(p_inst->mass) * mass * gravity / (distance * distance);
			float ax = (force * dx) / (distance * p_inst->mass);
			float ay = (force * dy) / (distance * p_inst->mass);
			float az = (force * dz) / (distance * p_inst->mass);
			p_inst->vel.x += ax;
			p_inst->vel.y += ay;
			p_inst->vel.z += az;
		}
	}

private:
	black_hole() : particle_modifier_implementation("black_hole") {
		particle_modifier_implementations.push_back(this);
	}
	black_hole( const black_hole& );
	black_hole & operator = (const black_hole &);

};

black_hole& ps_modifier_black_hole = black_hole::instance();
