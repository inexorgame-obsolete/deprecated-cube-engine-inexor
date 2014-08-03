#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of the velocity transformation.
 */
struct velocity_transformation : public particle_modifier_implementation
{

public:

	static velocity_transformation& instance()
	{
		static velocity_transformation _instance;
		return _instance;
	}
	virtual ~velocity_transformation() { }

	/**
	 * Part of the euler integration.
	 */
	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		float f = elapsedtime / particle_frame;
		p_inst->o.x += p_inst->vel.x * f;
		p_inst->o.y += p_inst->vel.y * f;
		p_inst->o.z += p_inst->vel.z * f;
	}

private:

	velocity_transformation() : particle_modifier_implementation("velocity_transformation") {
		particle_modifier_implementations.push_back(this);
	}
	velocity_transformation( const velocity_transformation& );
	velocity_transformation & operator = (const velocity_transformation &);

};

velocity_transformation& ps_modifier_velocity_transformation = velocity_transformation::instance();
