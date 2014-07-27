#include "cube.h"
#include "engine/particles/particles.h"

struct point_emitter : particle_emitter_implementation
{

	int millistoprocess;

	point_emitter()
    {
		millistoprocess = 0;
		strcpy(name, newstring("point_emitter"));
		particle_emitter_implementations.add(this);
    }

	void emit(particle_emitter_instance pe_inst, int pe_inst_id, int elapsedtime) {
		// conoutf("point_emitter:emit(%d, %d)", pe_inst.type, elapsedtime);

		particle_emitter_type pe_type = particle_emitter_types[pe_inst.type];

		millistoprocess += elapsedtime;
		int particlestoemit = millistoprocess / pe_type.rate;
		millistoprocess = millistoprocess % pe_type.rate;

		if (particlestoemit > 0) {

			conoutf("spawn particles (count: %d type: %d emitter: %s)", particlestoemit, pe_type.particle_type, pe_type.name);
			int p_type = pe_type.particle_type;
			float p_mass = pe_type.mass;
			float p_density = pe_type.density;
			int p_remaining = pe_type.lifetime;
			int renderer_type = particle_types[p_type].renderer_type;

			loopi(particlestoemit)
			{
				// get new particle, may increase the pool :-)
				particle_instance *p_inst = emit_particle();
//				conoutf("pe_inst_id: %d", pe_inst_id);
				// set the origin emitter
				p_inst->emitter = pe_inst_id;
				// get the particle type, mass and density from the emitter type
//				conoutf("p_type: %d", p_type);
				p_inst->type = p_type;
//				conoutf("p_mass: %2.1f", p_mass);
				p_inst->mass = p_mass;
//				conoutf("p_density: %2.1f", p_density);
				p_inst->density = p_density;
				// set the elapsed and remaining iterations from the emitter type's lifetime
				p_inst->elapsed = 0;
//				conoutf("p_remaining: %d", p_remaining);
				p_inst->remaining = p_remaining;
//				conoutf("x: %2.1f, y: %2.1f, z: %2.1f", pe_inst.o.x, pe_inst.o.y, pe_inst.o.z);
				p_inst->o = pe_inst.o;
				// add particle instance to the alive pool
				alive_pool[current_alive_pool].add(*p_inst);
//				conoutf("added to alive pool");
			}
		}

	}

};

point_emitter *ps_emitter_point = new point_emitter();
