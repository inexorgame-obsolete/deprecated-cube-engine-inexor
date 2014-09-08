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
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;

		p_inst->vel.x += (rndscale(scale) - scale2) * time_factor;
		p_inst->vel.y += (rndscale(scale) - scale2) * time_factor;
		p_inst->vel.z += (rndscale(scale) - scale2) * time_factor;
		// p_inst->vel.x += ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 64.0f) - 32.0f) * time_factor;
		// p_inst->vel.y += ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 64.0f) - 32.0f) * time_factor;
		// p_inst->vel.z += ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 64.0f) - 32.0f) * time_factor;
		// p_inst->vel.x += ((static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 64.0f) - 32.0f) * time_factor) + 0.01f);
		// p_inst->vel.y += ((static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 64.0f) - 32.0f) * time_factor) + 0.01f);
		// p_inst->vel.z += ((static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 64.0f) - 32.0f) * time_factor) + 0.01f);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	float scale;
	float scale2;
	float time_factor;

	randomv() : particle_modifier_implementation("randomv") {
		ps.add_modifier_implementation(this);
		scale = 32.0f;
		scale2 = 16.0f;
		time_factor = 0.0f;
	}
	randomv( const randomv& );
	randomv & operator = (const randomv &);

};

randomv& ps_modifier_randomv = randomv::instance();
