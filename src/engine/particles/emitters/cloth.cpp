#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a field emitter.
 */
struct cloth_emitter : public particle_emitter_implementation
{

public:

	static cloth_emitter& instance()
	{
		static cloth_emitter _instance;
		return _instance;
	}
	virtual ~cloth_emitter() { }

	/**
	 * Emits particles from a one, two or three dimensional grid which is specified
	 * by the grid size attributes: grid_size_x, grid_size_y, grid_size_z. The distance of the
	 * points in the grid is specified by the grid_dist attribute.
	 */
	void emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
		particle_emitter_type* pe_type = pe_inst->pe_type;
		pe_inst->millistoprocess += elapsedtime;
		int particlestoemit = pe_inst->millistoprocess / pe_type->rate;
		pe_inst->millistoprocess = pe_inst->millistoprocess % pe_type->rate;

		if (particlestoemit > 0)
		{

			std::vector<particle_instance*> current;
			for (int i = 0; i < cloth_width; i++)
			{
				// get new particle, may increase the pool
				particle_instance *p_inst = ps.emit_particle();
				// set the origin emitter
				p_inst->pe_inst = pe_inst;
				// get the particle type, mass and density from the emitter type
				p_inst->p_type = pe_inst->p_type;
				p_inst->o.x = pe_inst->o.x + (i * pe_inst->density * 0.5f);
				p_inst->o.y = pe_inst->o.y;
				p_inst->o.z = pe_inst->o.z;
				p_inst->vel.x = pe_inst->vel.x;
				// float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float ry = rndscale(1.0f);
				p_inst->vel.y = pe_inst->vel.y + ry * (pe_inst->vel.z);
				p_inst->vel.z = pe_inst->vel.z + pe_inst->vel.z * sin(ps.particlemillis * 0.001f);
				p_inst->mass = pe_inst->mass;
				p_inst->density = pe_inst->density;
				// set the remaining iterations from the emitter type's lifetime
				p_inst->remaining = pe_inst->lifetime;
				// add particle instance to the alive pool
				ps.alive_pool.push_back(p_inst);
				ps.count_alive_pool++;
				// add particle instance to it's renderer
				p_inst->p_type->pr_inst->particles.push_back(p_inst);
				current.push_back(p_inst);
				if (i > 0)
				{
					spring_instance *spring_inst1 = new spring_instance;
					spring_inst1->p_inst_1 = current[i - 1];
					spring_inst1->p_inst_2 = p_inst;
					spring_inst1->spring_constant = cloth_constant;
					spring_inst1->spring_friction = cloth_friction;
					spring_inst1->spring_length = pe_inst->density;
					ps.add_spring(spring_inst1);
				}
				if (previous.size() > i)
				{
					spring_instance *spring_inst2 = new spring_instance;
					spring_inst2->p_inst_1 = previous[i];
					spring_inst2->p_inst_2 = p_inst;
					spring_inst2->spring_constant = cloth_constant;
					spring_inst2->spring_friction = cloth_friction;
					spring_inst2->spring_length = pe_inst->density;
					ps.add_spring(spring_inst2);
					if (i > 0)
					{
						spring_instance *spring_inst3 = new spring_instance;
						spring_inst3->p_inst_1 = previous[i - 1];
						spring_inst3->p_inst_2 = p_inst;
						spring_inst3->spring_constant = cloth_constant;
						spring_inst3->spring_friction = cloth_friction;
						spring_inst3->spring_length = pe_inst->density; // sqrt(2 * (pe_inst->density * pe_inst->density));
						ps.add_spring(spring_inst3);
					}
					if (i < (cloth_width - 1))
					{
						spring_instance *spring_inst4 = new spring_instance;
						spring_inst4->p_inst_1 = previous[i + 1];
						spring_inst4->p_inst_2 = p_inst;
						spring_inst4->spring_constant = cloth_constant;
						spring_inst4->spring_friction = cloth_friction;
						spring_inst4->spring_length = pe_inst->density; // sqrt(2 * (pe_inst->density * pe_inst->density));
						ps.add_spring(spring_inst4);
					}
				}
			}
			previous = current;
		}
	}

private:

	std::vector<particle_instance*> previous;
	int cloth_width;
	float cloth_constant;
	float cloth_friction;

	cloth_emitter() : particle_emitter_implementation("cloth_emitter")
	{
		ps.add_emitter_implementation(this);
		cloth_width = 10;
		cloth_constant = 0.08f;
		cloth_friction = 0.60f;
	}
	cloth_emitter( const cloth_emitter& );
	cloth_emitter & operator = (const cloth_emitter &);

};

cloth_emitter& ps_emitter_cloth = cloth_emitter::instance();
