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
	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		p_inst->vel.mul(pm_inst->attributes["damper"] * (elapsedtime / particle_frame));
	}

private:
	velocity_damper() : particle_modifier_implementation("velocity_damper") {
		particle_modifier_implementations.push_back(this);
	}
	velocity_damper( const velocity_damper& );
	velocity_damper & operator = (const velocity_damper &);

};

velocity_damper& ps_modifier_velocity_damper = velocity_damper::instance();
