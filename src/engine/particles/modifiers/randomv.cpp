#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a random velocity transformation
 * over time.
 */
struct randomv : public particle_modifier_implementation
{

public:

	static randomv& instance()
	{
		static randomv _instance;
		return _instance;
	}
	virtual ~randomv() { }

	/**
	 * Respects the particle time frame.
	 */
	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / particle_frame;
		float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		p_inst->vel.x += ((rx * 64.0f) - 32.0f) * f;
		p_inst->vel.y += ((ry * 64.0f) - 32.0f) * f;
		p_inst->vel.z += ((rz * 64.0f) - 32.0f) * f;
	}

private:

	randomv() : particle_modifier_implementation("randomv") {
		particle_modifier_implementations.push_back(this);
	}
	randomv( const randomv& );
	randomv & operator = (const randomv &);

};

randomv& ps_modifier_randomv = randomv::instance();
