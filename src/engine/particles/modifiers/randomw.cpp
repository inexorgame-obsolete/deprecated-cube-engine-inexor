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
	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		p_inst->vel.x += (rx * 2.0f) - 1.0f;
		p_inst->vel.y += (ry * 2.0f) - 1.0f;
		p_inst->vel.z += (rz * 2.0f) - 1.0f;
	}

private:

	randomw() : particle_modifier_implementation("randomw") {
		particle_modifier_implementations.push_back(this);
	}
	randomw( const randomw& );
	randomw & operator = (const randomw &);

};

randomw& ps_modifier_randomw = randomw::instance();
