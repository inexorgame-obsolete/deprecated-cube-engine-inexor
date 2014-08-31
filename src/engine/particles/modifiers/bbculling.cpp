#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of bounding box particle culling.
 */
struct bb_culling : public particle_modifier_implementation
{

public:

	static bb_culling& instance()
	{
		static bb_culling _instance;
		return _instance;
	}
	virtual ~bb_culling() { }

	/**
	 * The bounding box boundaries are the two attached positions.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		if (p_inst->o.x < pm_inst->positions[0]->o.x
			|| p_inst->o.y < pm_inst->positions[0]->o.y
			|| p_inst->o.z < pm_inst->positions[0]->o.z
			|| p_inst->o.x > pm_inst->positions[1]->o.x
			|| p_inst->o.y > pm_inst->positions[1]->o.y
			|| p_inst->o.z > pm_inst->positions[1]->o.z
		) {
			p_inst->remaining = 0;
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

//	inline void init(particle_instance *p_inst) { }

private:

	bb_culling() : particle_modifier_implementation("bb_culling") {
		ps.add_modifier_implementation(this);
	}
	bb_culling( const bb_culling& );
	bb_culling & operator = (const bb_culling &);

};

bb_culling& ps_modifier_bb_culling = bb_culling::instance();
