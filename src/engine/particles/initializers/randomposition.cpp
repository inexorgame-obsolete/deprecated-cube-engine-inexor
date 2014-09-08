#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of an initializer that applies a
 * random start position.
 */
struct random_position : public particle_initializer_implementation
{

public:

	static random_position& instance()
	{
		static random_position _instance;
		return _instance;
	}
	virtual ~random_position() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {
		outer_scale = vec(pi_inst->attributes["osx"], pi_inst->attributes["osy"], pi_inst->attributes["osz"]);
		inner_scale = vec(pi_inst->attributes["isx"], pi_inst->attributes["isy"], pi_inst->attributes["isz"]);
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			(*p_it)->pos->o.add(vec(rndscale(outer_scale.x), rndscale(outer_scale.y), rndscale(outer_scale.z))).sub(inner_scale);
		}
	}

	void render_edit_overlay(particle_initializer_instance *entity_instance) { }

private:

	vec outer_scale;
	vec inner_scale;
	float time_factor;

	random_position() : particle_initializer_implementation("random_position") {
		ps.add_initializer_implementation(this);
		outer_scale = vec(64.0f, 64.0f, 64.0f);
		inner_scale = vec(32.0f, 32.0f, 32.0f);
		time_factor = 0.0f;
	}
	random_position( const random_position& );
	random_position & operator = (const random_position &);

};

random_position& ps_initializer_random_position = random_position::instance();
