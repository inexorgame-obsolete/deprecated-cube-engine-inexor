#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of an initializer that applies a
 * random start velocity.
 */
struct random_velocity : public particle_initializer_implementation
{

public:

	static random_velocity& instance()
	{
		static random_velocity _instance;
		return _instance;
	}
	virtual ~random_velocity() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {
		/*
		outer_scale.x = pi_inst->attributes["osx"];
		outer_scale.y = pi_inst->attributes["osy"];
		outer_scale.z = pi_inst->attributes["osz"];
		inner_scale.x = pi_inst->attributes["isx"];
		inner_scale.y = pi_inst->attributes["isy"];
		inner_scale.z = pi_inst->attributes["isz"];
		*/
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			(*p_it)->vel.add(vec(rndscale(outer_scale.x), rndscale(outer_scale.y), rndscale(outer_scale.z))).sub(inner_scale);
		}
	}

private:

	vec outer_scale;
	vec inner_scale;
	float time_factor;

	random_velocity() : particle_initializer_implementation("random_velocity") {
		ps.add_initializer_implementation(this);
		outer_scale = vec(32.0f, 32.0f, 32.0f);
		inner_scale = vec(16.0f, 16.0f, 16.0f);
		time_factor = 0.0f;
	}
	random_velocity( const random_velocity& );
	random_velocity & operator = (const random_velocity &);

};

random_velocity& ps_initializer_random_velocity = random_velocity::instance();
