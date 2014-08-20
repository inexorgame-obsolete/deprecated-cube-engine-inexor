#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a field emitter.
 */
struct satellite_emitter : public particle_emitter_implementation
{

public:

	static satellite_emitter& instance()
	{
		static satellite_emitter _instance;
		return _instance;
	}
	virtual ~satellite_emitter() { }

	/**
	 * Emits particles from a one, two or three dimensional grid which is specified
	 * by the grid size attributes: grid_size_x, grid_size_y, grid_size_z. The distance of the
	 * points in the grid is specified by the grid_dist attribute.
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

			// get new particle, may increase the pool
			particle_instance *p_inst = ps.emit_particle();
			// set the origin emitter
			p_inst->pe_inst = pe_inst;
			// get the particle type, mass and density from the emitter type
			p_inst->p_type = ps.particle_types_map["primary"];
			// conoutf("x:%3.1f y:%3.1f z:%3.1f", pe_inst->o.x, pe_inst->o.y, pe_inst->o.z);
			p_inst->o.x = pe_inst->o.x;
			p_inst->o.y = pe_inst->o.y;
			p_inst->o.z = pe_inst->o.z;
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

			for (int i = 0; i < 20; i++)
			{
				particle_instance *p_inst_s = ps.emit_particle();
				p_inst_s->pe_inst = pe_inst;
				p_inst_s->p_type = pe_inst->p_type;
				float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				p_inst_s->o.x = pe_inst->o.x + (rx - 0.5f) * 10.0f * pe_inst->density;
				p_inst_s->o.y = pe_inst->o.y + (ry - 0.5f) * 10.0f * pe_inst->density;
				p_inst_s->o.z = pe_inst->o.z + (rz - 0.5f) * 10.0f * pe_inst->density;
				p_inst_s->vel = pe_inst->vel;
				p_inst_s->roll = 0;
				p_inst_s->mass = pe_inst->mass / 10.0f; // the satellites are much weaker!
				p_inst_s->density = pe_inst->density / 10.0f;
				p_inst_s->remaining = pe_inst->lifetime;
				ps.alive_pool.push_back(p_inst_s);
				ps.count_alive_pool++;
				p_inst_s->p_type->pr_inst->particles.push_back(p_inst_s);

				spring_instance *spring_inst = new spring_instance;
				spring_inst->p_inst_1 = p_inst;
				spring_inst->p_inst_2 = p_inst_s;
				spring_inst->spring_constant = 0.2f;
				spring_inst->spring_friction = 0.9f;
				spring_inst->spring_length = pe_inst->density;
				spring_inst->alive = true;
				ps.add_spring(spring_inst);
			}
		}
		return emitted;
	}

private:

	satellite_emitter() : particle_emitter_implementation("satellite_emitter")
	{
		ps.add_emitter_implementation(this);
	}
	satellite_emitter( const satellite_emitter& );
	satellite_emitter & operator = (const satellite_emitter &);

};

satellite_emitter& ps_emitter_satellite = satellite_emitter::instance();
