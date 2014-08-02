#include "cube.h"
#include "engine/particles/particles.h"

struct velocity_damper : public particle_modifier_implementation
{
	/**
	 * The damper.
	 */
	static const float damper = 0.99f;

	velocity_damper() : particle_modifier_implementation("velocity_damper") {
		particle_modifier_implementations.push_back(this);
	}
	virtual ~velocity_damper() { }

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		// pm_inst->attributes["damper"]
		p_inst->vel.mul(damper * (elapsedtime / particle_frame));
	}

	/*
	std::map<std::string, float> get_default_attributes() {
		std::map<std::string, float> default_attributes;
		default_attributes["damper"] = 0.99f;
		return default_attributes;
	}
	*/

};

velocity_damper *ps_modifier_velocity_damper = new velocity_damper();
