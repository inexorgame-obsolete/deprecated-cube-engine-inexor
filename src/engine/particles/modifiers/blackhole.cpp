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
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		// TODO: time factor
		gravity = pm_inst->attributes["gravity"];
		mass = pm_inst->attributes["mass"];
		dx = p_inst->pos->o.x - pm_inst->positions[0]->o.x;
		dy = p_inst->pos->o.y - pm_inst->positions[0]->o.y;
		dz = p_inst->pos->o.z - pm_inst->positions[0]->o.z;
		distance = sqrtf(dx * dx + dy * dy + dz * dz);
		if (distance < 5.0f) {
			p_inst->remaining = 0;
		} else {
			force = -(p_inst->mass) * mass * gravity / (distance * distance);
			p_inst->vel.x += (force * dx) / (distance * p_inst->mass);
			p_inst->vel.y += (force * dy) / (distance * p_inst->mass);
			p_inst->vel.z += (force * dz) / (distance * p_inst->mass);
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	float gravity;
	float mass;
	float distance;
	float force;
	float dx, dy, dz;

	black_hole() : particle_modifier_implementation("black_hole") {
		ps.add_modifier_implementation(this);
		gravity = 0.0f;
		mass = 0.0f;
		distance = 0.0f;
		force = 0.0f;
		dx = 0.0f;
		dy = 0.0f;
		dz = 0.0f;
	}
	black_hole( const black_hole& );
	black_hole & operator = (const black_hole &);

};

black_hole& ps_modifier_black_hole = black_hole::instance();
