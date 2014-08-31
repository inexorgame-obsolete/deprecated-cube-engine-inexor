#include "cube.h"
#include "engine/particles/particles.h"

// TODO: remove this modifier in favor of simplegravity
struct global_gravity : public particle_modifier_implementation
{

public:

	static global_gravity& instance()
	{
		static global_gravity _instance;
		return _instance;
	}
	virtual ~global_gravity() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) { }

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime)
	{
		gravity = pm_inst->attributes["gravity"];
		mass = pm_inst->attributes["mass"];
		for(std::list<particle_instance*>::iterator p_it = ps.alive_pool.begin(); p_it != ps.alive_pool.end(); ++p_it)
		{
			dz = (*p_it)->o.z - pm_inst->positions[0]->o.z;
			if (dz <= dzmin || dz >= dzmax) continue;
			force = -((*p_it)->mass) * mass * gravity / (dz * dz);
			(*p_it)->vel.z += (force * dz) / (dz * (*p_it)->mass);
		}
	}

	inline void modify(int elapsedtime) { }

private:

	float gravity;
	float mass;
	float distance;
	float force;
	float dz;
	float dzmin;
	float dzmax;

	global_gravity() : particle_modifier_implementation("global_gravity") {
		ps.add_modifier_implementation(this);
		gravity = 0.0f;
		mass = 0.0f;
		distance = 0.0f;
		force = 0.0f;
		dz = 0.0f;
		dzmin = 10.0f;
		dzmax = 80.0f;
	}
	global_gravity( const global_gravity& );
	global_gravity & operator = (const global_gravity &);

};

global_gravity& ps_modifier_global_gravity = global_gravity::instance();
