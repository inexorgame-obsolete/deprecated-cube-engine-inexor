#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a sphere emitter.
 */
struct sphere_emitter : public particle_emitter_implementation
{

public:

	static sphere_emitter& instance()
	{
		static sphere_emitter _instance;
		return _instance;
	}
	virtual ~sphere_emitter() { }

	/**
	 * Emits particles from a single sphere (x,y,z).
	 */
	inline void emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
		particle_emitter_type* pe_type = pe_inst->pe_type;
		pe_inst->millistoprocess += elapsedtime;
		int particlestoemit = pe_inst->millistoprocess / pe_type->rate;
		pe_inst->millistoprocess = pe_inst->millistoprocess % pe_type->rate;

		if (particlestoemit > 0)
		{
			loopi(particlestoemit)
			{
				// get new particle, may increase the pool
				particle_instance *p_inst = emit_particle();
				// set the origin emitter
				p_inst->pe_inst = pe_inst;
				// get the particle type, mass and density from the emitter type
				p_inst->p_type = pe_inst->p_type;
				p_inst->o = pe_inst->o;

				float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				p_inst->vel.x += (rx * 2 * pe_inst->vel.x) - pe_inst->vel.x;
				p_inst->vel.y += (ry * 2 * pe_inst->vel.y) - pe_inst->vel.y;
				p_inst->vel.z += (rz * 2 * pe_inst->vel.z) - pe_inst->vel.z;

				p_inst->mass = pe_inst->mass;
				p_inst->density = pe_inst->density;
				// set the elapsed and remaining iterations from the emitter type's lifetime
				p_inst->elapsed = 0;
				p_inst->remaining = pe_inst->lifetime;
				// add particle instance to the alive pool
				alive_pool.push_back(p_inst);
				// add particle instance to it's renderer
				p_inst->p_type->pr_inst->particles.push_back(p_inst);
			}
		}

	}

private:

	sphere_emitter() : particle_emitter_implementation("sphere_emitter")
	{
		particle_emitter_implementations.push_back(this);
	}
	sphere_emitter( const sphere_emitter& );
	sphere_emitter & operator = (const sphere_emitter &);

};

sphere_emitter& ps_emitter_sphere = sphere_emitter::instance();
