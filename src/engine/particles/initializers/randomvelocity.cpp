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

	inline void init(std::list<particle_instance *> particles, int elapsedtime) {
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			(*p_it)->vel.add(vec(
				rndscale(scale) - scale2,
				rndscale(scale) - scale2,
				rndscale(scale) - scale2
			));
		}
	}

private:

	float scale;
	float scale2;
	float time_factor;

	random_velocity() : particle_initializer_implementation("random_velocity") {
		ps.add_initializer_implementation(this);
		scale = 32.0f;
		scale2 = 16.0f;
		time_factor = 0.0f;
	}
	random_velocity( const random_velocity& );
	random_velocity & operator = (const random_velocity &);

};

random_velocity& ps_initializer_random_velocity = random_velocity::instance();
