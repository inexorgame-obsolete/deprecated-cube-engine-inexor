#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a gravity point.
 */
struct gravity_point : public particle_modifier_implementation
{

public:

	static gravity_point& instance()
	{
		static gravity_point _instance;
		return _instance;
	}
	virtual ~gravity_point() { }

	/**
	 * Attracts particles.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		// TODO: time factor
		gravity = pm_inst->attributes["gravity"];
		mass = pm_inst->attributes["mass"];
		dx = p_inst->o.x - pm_inst->positions[0]->o.x;
		dy = p_inst->o.y - pm_inst->positions[0]->o.y;
		dz = p_inst->o.z - pm_inst->positions[0]->o.z;
		distance = sqrtf(dx * dx + dy * dy + dz * dz);
		if (distance == 0.0f) distance = 0.00000000001f;
		force = -(p_inst->mass) * mass * gravity / (distance * distance);
		p_inst->vel.x += (force * dx) / (distance * p_inst->mass);
		p_inst->vel.y += (force * dy) / (distance * p_inst->mass);
		p_inst->vel.z += (force * dz) / (distance * p_inst->mass);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

//	inline void init(particle_instance *p_inst) { }

private:

	float gravity;
	float mass;
	float distance;
	float force;
	float dx, dy, dz;

	gravity_point() : particle_modifier_implementation("gravity_point") {
		ps.add_modifier_implementation(this);
		gravity = 0.0f;
		mass = 0.0f;
		distance = 0.0f;
		force = 0.0f;
		dx = 0.0f;
		dy = 0.0f;
		dz = 0.0f;
	}
	gravity_point( const gravity_point& );
	gravity_point & operator = (const gravity_point &);

};

gravity_point& ps_modifier_gravity_point = gravity_point::instance();
