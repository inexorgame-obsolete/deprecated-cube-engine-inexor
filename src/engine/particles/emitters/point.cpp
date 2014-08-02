#include "cube.h"
#include "engine/particles/particles.h"

struct point_emitter : public particle_emitter_implementation
{

	point_emitter() : particle_emitter_implementation("point_emitter") {
		particle_emitter_implementations.push_back(this);
	}
	virtual ~point_emitter() { }

	void emit(particle_emitter_instance *pe_inst, int elapsedtime) {
		particle_emitter_type* pe_type = pe_inst->pe_type;
		pe_inst->millistoprocess += elapsedtime;
		int particlestoemit = pe_inst->millistoprocess / pe_type->rate;
		pe_inst->millistoprocess = pe_inst->millistoprocess % pe_type->rate;
		// conoutf("pe_inst: %d millistoprocess: %d particlestoemit: %d", pe_inst_id, pe_inst->millistoprocess, particlestoemit);

		if (particlestoemit > 0) {
			loopi(particlestoemit)
			{
				// get new particle, may increase the pool
				particle_instance *p_inst = emit_particle();
				// set the origin emitter
				p_inst->pe_inst = pe_inst;
				// get the particle type, mass and density from the emitter type
				p_inst->p_type = pe_inst->p_type;
				p_inst->o = pe_inst->o;
				p_inst->vel = pe_inst->vel;
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

};

point_emitter *ps_emitter_point = new point_emitter();
