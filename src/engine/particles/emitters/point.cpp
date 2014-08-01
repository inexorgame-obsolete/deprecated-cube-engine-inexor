#include "cube.h"
#include "engine/particles/particles.h"

struct point_emitter : public particle_emitter_implementation
{

	point_emitter() : particle_emitter_implementation("point_emitter") {
		particle_emitter_implementations.add(this);
	}
	~point_emitter() { }

	void emit(particle_emitter_instance *pe_inst, int pe_inst_id, int elapsedtime) {
		particle_emitter_type pe_type = particle_emitter_types[pe_inst->type];

		pe_inst->millistoprocess += elapsedtime;
		int particlestoemit = pe_inst->millistoprocess / pe_type.rate;
		pe_inst->millistoprocess = pe_inst->millistoprocess % pe_type.rate;
		// conoutf("pe_inst: %d millistoprocess: %d particlestoemit: %d", pe_inst_id, pe_inst->millistoprocess, particlestoemit);

		if (particlestoemit > 0) {
			int p_type = pe_type.particle_type;
			float p_mass = pe_type.mass;
			float p_density = pe_type.density;
			int p_remaining = pe_type.lifetime;
			int renderer_type = particle_types[p_type].renderer_type;
			loopi(particlestoemit)
			{
				// get new particle, may increase the pool
				particle_instance *p_inst = emit_particle();
				// set the origin emitter
				p_inst->emitter = pe_inst_id;
				// get the particle type, mass and density from the emitter type
				p_inst->type = p_type;
				p_inst->mass = p_mass;
				p_inst->density = p_density;
				// set the elapsed and remaining iterations from the emitter type's lifetime
				p_inst->elapsed = 0;
				p_inst->remaining = p_remaining;
				p_inst->o = pe_inst->o;
				p_inst->vel = pe_inst->vel;
				// add particle instance to the alive pool
				alive_pool[current_alive_pool].add(*p_inst);
			}
		}

	}

};

point_emitter *ps_emitter_point = new point_emitter();
