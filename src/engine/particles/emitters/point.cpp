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
		std::list<particle_instance*> emitted;
		for (int i = 0; i < pe_inst->batch_size; i++)
		{
			// get new particle, may increase the pool
			particle_instance *p_inst = ps.emit_particle();
			// set the origin emitter
			p_inst->pe_inst = pe_inst;
			// get the particle type, mass and density from the emitter type
			p_inst->type = pe_inst->p_type;
			// particle_emitter_instance* pe_inst2 = pe_inst;
			// position* pos = pe_inst->pos;
			// vec o = vec(pos->o);
			// float x = o.x;
			// conoutf("pe_inst->pos->o.x=%2.2f", pe_inst->pos->o.x);
			// conoutf("x=%2.2f", x);
			// p_inst->pos->o = vec(pe_inst->pos->o);
			p_inst->pos->o = pe_inst->pos->o;
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
			// p_inst->p_type->pr_inst->particles.push_back(p_inst);
			emitted.push_back(p_inst);
		}
		return emitted;
	}

	void render_edit_overlay(particle_emitter_instance *entity_instance) { }

private:

	point_emitter() : particle_emitter_implementation("point_emitter")
	{
		ps.add_emitter_implementation(this);
	}
	point_emitter( const point_emitter& );
	point_emitter & operator = (const point_emitter &);

};

point_emitter& ps_emitter_point = point_emitter::instance();
