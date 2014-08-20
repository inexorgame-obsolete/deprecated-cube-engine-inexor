#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a point emitter.
 */
struct point_emitter : public particle_emitter_implementation
{

public:

	static point_emitter& instance()
	{
		static point_emitter _instance;
		return _instance;
	}
	virtual ~point_emitter() { }

	/**
	 * Emits particles from a single point (x,y,z).
	 */
	inline std::list<particle_instance*> emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
		particle_emitter_type* pe_type = pe_inst->pe_type;
		pe_inst->millistoprocess += elapsedtime;
		int particlestoemit = pe_inst->millistoprocess / pe_type->rate;
		pe_inst->millistoprocess = pe_inst->millistoprocess % pe_type->rate;

		std::list<particle_instance*> emitted;
		if (particlestoemit > 0)
		{
			loopi(particlestoemit)
			{
				// get new particle, may increase the pool
				particle_instance *p_inst = ps.emit_particle();
				// set the origin emitter
				p_inst->pe_inst = pe_inst;
				// get the particle type, mass and density from the emitter type
				p_inst->p_type = pe_inst->p_type;
				// conoutf("x:%3.1f y:%3.1f z:%3.1f", pe_inst->o.x, pe_inst->o.y, pe_inst->o.z);
				p_inst->o = vec(pe_inst->o);
				p_inst->vel = pe_inst->vel;
				p_inst->roll = 0;
				p_inst->mass = pe_inst->mass;
				p_inst->density = pe_inst->density;
				// set the remaining iterations from the emitter type's lifetime
				p_inst->remaining = pe_inst->lifetime;
				// add particle instance to the alive pool
				ps.alive_pool.push_back(p_inst);
				ps.count_alive_pool++;
				// add particle instance to it's renderer
				p_inst->p_type->pr_inst->particles.push_back(p_inst);
				emitted.push_back(p_inst);
			}
		}
		return emitted;
	}

private:

	point_emitter() : particle_emitter_implementation("point_emitter")
	{
		ps.add_emitter_implementation(this);
	}
	point_emitter( const point_emitter& );
	point_emitter & operator = (const point_emitter &);

};

point_emitter& ps_emitter_point = point_emitter::instance();
