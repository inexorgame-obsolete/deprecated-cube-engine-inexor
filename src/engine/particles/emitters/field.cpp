#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a field emitter.
 */
struct field_emitter : public particle_emitter_implementation
{

public:

	static field_emitter& instance()
	{
		static field_emitter _instance;
		return _instance;
	}
	virtual ~field_emitter() { }

	/**
	 * Emits particles from a one, two or three dimensional grid which is specified
	 * by the grid size attributes: grid_size_x, grid_size_y, grid_size_z. The distance of the
	 * points in the grid is specified by the grid_dist attribute.
	 */
	inline std::list<particle_instance*> emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
		// grid setup
		grid_dist = pe_inst->attributes["grid_dist"];
		grid_dist_2 = grid_dist / 2.0f;
		grid_size_x = int(pe_inst->attributes["grid_size_x"]);
		grid_size_y = int(pe_inst->attributes["grid_size_y"]);
		grid_size_z = int(pe_inst->attributes["grid_size_z"]);
		// the particle emitter is center, so calculate the origin
		ox = pe_inst->o.x - (grid_size_x > 1 ? (grid_size_x - 1) * grid_dist_2 : 0);
		oy = pe_inst->o.y - (grid_size_y > 1 ? (grid_size_y - 1) * grid_dist_2 : 0);
		oz = pe_inst->o.z - (grid_size_z > 1 ? (grid_size_z - 1) * grid_dist_2 : 0);

		std::list<particle_instance*> emitted;
		for (int i = 0; i < pe_inst->batch_size; i++)
		{
			for (int x = 0; x < grid_size_x; x++)
			{
				float dx = x * grid_dist;
				for (int y = 0; y < grid_size_y; y++)
				{
					float dy = y * grid_dist;
					for (int z = 0; z < grid_size_z; z++)
					{
						float dz = z * grid_dist;
						// get new particle, may increase the pool
						particle_instance *p_inst = ps.emit_particle();
						// set the origin emitter
						p_inst->pe_inst = pe_inst;
						// get the particle type, mass and density from the emitter type
						p_inst->type = pe_inst->p_type;
						p_inst->o.x = ox + dx;
						p_inst->o.y = oy + dy;
						p_inst->o.z = oz + dz;
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
				}
			}
		}
		return emitted;
	}

private:

	float grid_dist;
	float grid_dist_2;
	int grid_size_x;
	int grid_size_y;
	int grid_size_z;
	float ox;
	float oy;
	float oz;

	field_emitter() : particle_emitter_implementation("field_emitter")
	{
		ps.add_emitter_implementation(this);
		grid_dist = 0.0f;
		grid_dist_2 = 0.0f;
		grid_size_x = 1;
		grid_size_y = 1;
		grid_size_z = 1;
		ox = 0.0f;
		oy = 0.0f;
		oz = 0.0f;

	}
	field_emitter( const field_emitter& );
	field_emitter & operator = (const field_emitter &);

};

field_emitter& ps_emitter_field = field_emitter::instance();
