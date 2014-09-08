#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of an initializer for creating springs between a
 * primary particle and a lot of satellite particles.
 */
struct satellite_springs : public particle_initializer_implementation
{

public:

	static satellite_springs& instance()
	{
		static satellite_springs _instance;
		return _instance;
	}
	virtual ~satellite_springs() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {
		// first particle is the primary
		particle_instance* first = particles.front();
		spring_constant = pi_inst->attributes["spring_constant"];
		spring_friction = pi_inst->attributes["spring_friction"];
		spring_length = pi_inst->attributes["spring_length"];
		satellite_mass_factor = pi_inst->attributes["satellite_mass_factor"];
		satellite_density_factor = pi_inst->attributes["satellite_density_factor"];
		for(std::list<particle_instance*>::iterator p_it = particles.begin()++; p_it != particles.end(); ++p_it)
		{
			spring_instance *spring_inst = new spring_instance;
			spring_inst->p_inst_1 = first;
			spring_inst->p_inst_2 = (*p_it);
			spring_inst->spring_constant = spring_constant;
			spring_inst->spring_friction = spring_friction;
			spring_inst->spring_length = spring_length;
			spring_inst->alive = true;
			ps.add_spring(spring_inst);

			(*p_it)->mass = first->mass * satellite_mass_factor;
			(*p_it)->density = first->density * satellite_density_factor;
		}
	}

	void render_edit_overlay(particle_initializer_instance *entity_instance) { }

private:

	float time_factor;
	float spring_constant;
	float spring_friction;
	float spring_length;
	float satellite_mass_factor;
	float satellite_density_factor;

	satellite_springs() : particle_initializer_implementation("random_position") {
		ps.add_initializer_implementation(this);
		time_factor = 0.0f;
		spring_constant = 0.1f;
		spring_friction = 0.95f;
		spring_length = 10.0f;
		satellite_mass_factor = 0.1f;
		satellite_density_factor = 0.1f;
	}
	satellite_springs( const satellite_springs& );
	satellite_springs & operator = (const satellite_springs &);

};

satellite_springs& ps_initializer_satellite_springs = satellite_springs::instance();
