#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a velocity damper.
 */
struct velocity_damper : public particle_modifier_implementation
{

public:

	static velocity_damper& instance()
	{
		static velocity_damper _instance;
		return _instance;
	}
	virtual ~velocity_damper() { }

	/**
	 * The velocity of an particle gets reduced. The damping value is specified by
	 * the attribute "damper".
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;
		// damper = pm_inst->attributes["damper"];
		// p_inst->vel.x *= (1.0f - damper * time_factor);
		// p_inst->vel.y *= (1.0f - damper * time_factor);
		// p_inst->vel.z *= (1.0f - damper * time_factor);
		// Use the modifier vec3
		p_inst->vel.x *= (1.0f - pm_inst->o.x * time_factor);
		p_inst->vel.y *= (1.0f - pm_inst->o.y * time_factor);
		p_inst->vel.z *= (1.0f - pm_inst->o.z * time_factor);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

//	inline void init(particle_instance *p_inst) { }

private:

	float time_factor;
	float damper;

	velocity_damper() : particle_modifier_implementation("velocity_damper") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
		damper = 0.0f;
	}
	velocity_damper( const velocity_damper& );
	velocity_damper & operator = (const velocity_damper &);

};

velocity_damper& ps_modifier_velocity_damper = velocity_damper::instance();
