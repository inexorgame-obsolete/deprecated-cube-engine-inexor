#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of an initializer that applies a
 * random start velocity.
 */
struct random_particle_type : public particle_initializer_implementation
{

public:

	static random_particle_type& instance()
	{
		static random_particle_type _instance;
		return _instance;
	}
	virtual ~random_particle_type() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {
		int i = pi_inst->particle_types.size();
		std::list<particle_type*>::iterator pt_it;
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			pt_it = pi_inst->particle_types.begin();
			std::advance(pt_it, rnd(i));
			(*p_it)->type = (*pt_it);
		}
	}

private:

	random_particle_type() : particle_initializer_implementation("random_particle_type") {
		ps.add_initializer_implementation(this);
	}
	random_particle_type( const random_particle_type& );
	random_particle_type & operator = (const random_particle_type &);

};

random_particle_type& ps_initializer_random_particle_type = random_particle_type::instance();
