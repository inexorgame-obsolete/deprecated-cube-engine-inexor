#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of global gravity.
 */
struct simple_gravity : public particle_modifier_implementation
{

public:

	static simple_gravity& instance()
	{
		static simple_gravity _instance;
		return _instance;
	}
	virtual ~simple_gravity() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) { }

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime)
	{
		for(std::list<particle_instance*>::iterator p_it = ps.alive_pool.begin(); p_it != ps.alive_pool.end(); ++p_it)
		{
			(*p_it)->vel.z += ((-((*p_it)->mass) * _mass * _gravity / (dz * dz)) * dz) / (dz * (*p_it)->mass);
		}
	}

	inline void modify(int elapsedtime) { }

//	inline void init(particle_instance *p_inst) { }

private:

	float _gravity;
	float _mass;
	float dz;

	simple_gravity() : particle_modifier_implementation("simple_gravity") {
		ps.add_modifier_implementation(this);
		_gravity = 0.98f;
		_mass = 200.0f;
		dz = 60.0f;
	}
	simple_gravity( const simple_gravity& );
	simple_gravity & operator = (const simple_gravity &);

};

simple_gravity& ps_modifier_simple_gravity = simple_gravity::instance();
