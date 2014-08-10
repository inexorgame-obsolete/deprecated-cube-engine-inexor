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
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;
		p_inst->o.x += p_inst->vel.x * time_factor;
		p_inst->o.y += p_inst->vel.y * time_factor;
		p_inst->o.z += p_inst->vel.z * time_factor;
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	inline void init(particle_instance *p_inst) { }

private:

	float time_factor;

	velocity_transformation() : particle_modifier_implementation("velocity_transformation") {
		ps.particle_modifier_implementations.push_back(this);
		time_factor = 0.0f;
	}
	velocity_transformation( const velocity_transformation& );
	velocity_transformation & operator = (const velocity_transformation &);

};

velocity_transformation& ps_modifier_velocity_transformation = velocity_transformation::instance();
