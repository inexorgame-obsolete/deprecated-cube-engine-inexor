#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a position trace.
 */
struct position_trace : public particle_modifier_implementation
{

public:

	static position_trace& instance()
	{
		static position_trace _instance;
		return _instance;
	}
	virtual ~position_trace() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		p_inst->attributes["millistoprocess"] += elapsedtime;
		if (p_inst->attributes["millistoprocess"] > 2000.0f || p_inst->attributes["millistoprocess"] < 0.0f)
		{
			p_inst->attributes["millistoprocess"] = 0.0f;
			// get new particle, may increase the pool
			particle_instance *trace = ps.emit_particle();
			// don't set the origin emitter
			trace->pe_inst = ps.noop_emitter_inst;
			// get the particle type, mass and density from the emitter type
			trace->p_type = p_inst->p_type;
			trace->o = vec(p_inst->o);
			trace->vel = vec(0, 0, 0);
			trace->roll = p_inst->roll;
			trace->mass = p_inst->mass;
			trace->density = p_inst->density;
			// set the remaining iterations from the emitter type's lifetime
			trace->remaining = 100;
			// add particle instance to the alive pool
			ps.alive_pool.push_back(trace);
			ps.count_alive_pool++;
			// add particle instance to it's renderer (this time we have to do it by ourself, because we are in a modifier)
			trace->p_type->pr_inst->particles.push_back(trace);
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

private:

	float time_factor;

	position_trace() : particle_modifier_implementation("position_trace") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
	}
	position_trace( const position_trace& );
	position_trace & operator = (const position_trace &);

};

position_trace& ps_modifier_position_trace = position_trace::instance();
