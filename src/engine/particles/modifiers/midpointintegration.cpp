#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Explicit midpoint integration.
 */
struct midpoint_integration : public particle_modifier_implementation
{

public:

	static midpoint_integration& instance()
	{
		static midpoint_integration _instance;
		return _instance;
	}
	virtual ~midpoint_integration() { }

	/**
	 * Part of the euler integration.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		time_factor = elapsedtime / ps.particle_frame;
		p_inst->last.x = p_inst->pos->o.x;
		p_inst->last.y = p_inst->pos->o.y;
		p_inst->last.z = p_inst->pos->o.z;

		vec mid = vec(p_inst->pos->o).add(vec(p_inst->vel).mul(time_factor / 2.0f));

	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	float time_factor;

	midpoint_integration() : particle_modifier_implementation("midpoint_integration") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
	}
	midpoint_integration( const midpoint_integration& );
	midpoint_integration & operator = (const midpoint_integration &);

};

midpoint_integration& ps_modifier_midpoint_integration = midpoint_integration::instance();
