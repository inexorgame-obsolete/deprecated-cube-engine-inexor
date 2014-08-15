#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a random velocity transformation
 * over time.
 */
struct randomw : public particle_modifier_implementation
{

public:

	static randomw& instance()
	{
		static randomw _instance;
		return _instance;
	}
	virtual ~randomw() { }

	/**
	 * Doesn't respect the particle time frame.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		p_inst->vel.x += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f) - 1.0f;
		p_inst->vel.y += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f) - 1.0f;
		p_inst->vel.z += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f) - 1.0f;
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	inline void init(particle_instance *p_inst) { }

private:

	randomw() : particle_modifier_implementation("randomw") {
		ps.add_modifier_implementation(this);
	}
	randomw( const randomw& );
	randomw & operator = (const randomw &);

};

randomw& ps_modifier_randomw = randomw::instance();
