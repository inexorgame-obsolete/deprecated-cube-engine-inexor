#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of wind.
 */
struct wind : public particle_modifier_implementation
{

public:

	static wind& instance()
	{
		static wind _instance;
		return _instance;
	}
	virtual ~wind() { }

	/**
	 * Wind is defined by the x,y components of the velocity vector of the modifier.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;
		float rx = fabs(sin(ps.particlemillis));
		float ry = fabs(cos(ps.particlemillis));
		p_inst->vel.x += pm_inst->vel.x * rx * time_factor;
		p_inst->vel.y += pm_inst->vel.y * ry * time_factor;
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	inline void init(particle_instance *p_inst) { }

private:

	float time_factor;

	wind() : particle_modifier_implementation("wind") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
	}
	wind( const wind& );
	wind & operator = (const wind &);

};

wind& ps_modifier_wind = wind::instance();
