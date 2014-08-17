#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a density fadeout.
 */
struct rolling : public particle_modifier_implementation
{

public:

	static rolling& instance()
	{
		static rolling _instance;
		return _instance;
	}
	virtual ~rolling() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;
        p_inst->roll += p_inst->last.sub(p_inst->o).magnitude() / (4 * RAD);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	inline void init(particle_instance *p_inst) { }

private:

	float time_factor;

	rolling() : particle_modifier_implementation("rolling") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
	}
	rolling( const rolling& );
	rolling & operator = (const rolling &);

};

rolling& ps_modifier_rolling = rolling::instance();
