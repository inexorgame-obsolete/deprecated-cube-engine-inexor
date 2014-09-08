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
	inline std::list<particle_instance*> emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
		std::list<particle_instance*> emitted;
		for (int i = 0; i < pe_inst->batch_size; i++)
		{
			// get new particle, may increase the pool
			particle_instance *p_inst = ps.emit_particle();
			// set the origin emitter
			p_inst->pe_inst = pe_inst;
			// get the particle type, mass and density from the emitter type
			p_inst->type = pe_inst->p_type;
			// conoutf("x:%3.1f y:%3.1f z:%3.1f", pe_inst->o.x, pe_inst->o.y, pe_inst->o.z);
			p_inst->pos->o = vec(pe_inst->pos->o);

			// TODO: make sure the length of the vector from emitter to the spawn position is constant

			float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			p_inst->vel.x += (rx * 2 * pe_inst->vel.x) - pe_inst->vel.x;
			p_inst->vel.y += (ry * 2 * pe_inst->vel.y) - pe_inst->vel.y;
			p_inst->vel.z += (rz * 2 * pe_inst->vel.z) - pe_inst->vel.z;
			p_inst->roll = 0;

			p_inst->mass = pe_inst->mass;
			p_inst->density = pe_inst->density;
			// set the remaining iterations from the emitter type's lifetime
			p_inst->remaining = pe_inst->lifetime;
			// add particle instance to the alive pool
			ps.alive_pool.push_back(p_inst);
			ps.count_alive_pool++;
			emitted.push_back(p_inst);
		}
		return emitted;
	}

	void render_edit_overlay(particle_emitter_instance *entity_instance) { }

private:

	particle_instance* last;

	sphere_emitter() : particle_emitter_implementation("sphere_emitter")
	{
		ps.add_emitter_implementation(this);
		last = NULL;
	}
	sphere_emitter( const sphere_emitter& );
	sphere_emitter & operator = (const sphere_emitter &);

};

sphere_emitter& ps_emitter_sphere = sphere_emitter::instance();
