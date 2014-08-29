#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a density fadeout.
 */
struct density_fadeout : public particle_modifier_implementation
{

public:

	static density_fadeout& instance()
	{
		static density_fadeout _instance;
		return _instance;
	}
	virtual ~density_fadeout() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;
		percent_done = p_inst->elapsed / (p_inst->remaining + p_inst->elapsed);
		if (percent_done > fade_out_threshold) {
			p_inst->density *= (1.0f - percent_done) * 10.0f * time_factor * fade_out_frames;
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

private:

	float time_factor;
	float percent_done;
	float fade_out_threshold;
	float fade_out_frames;

	density_fadeout() : particle_modifier_implementation("density_fadeout") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
		percent_done = 0.0f;
		fade_out_threshold = 0.90f;
		fade_out_frames = 0.5f;
	}
	density_fadeout( const density_fadeout& );
	density_fadeout & operator = (const density_fadeout &);

};

density_fadeout& ps_modifier_density_fadeout = density_fadeout::instance();
