#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of rolling particles (like grenade projectiles).
 */
struct rolling : public particle_modifier_implementation
{

public:

	static rolling& instance()
	{
		static rolling _instance;
		return _instance;
	}
	virtual ~rolling() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
        p_inst->roll += p_inst->last.sub(p_inst->pos->o).magnitude() / (4 * RAD);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	rolling() : particle_modifier_implementation("rolling") {
		ps.add_modifier_implementation(this);
	}
	rolling( const rolling& );
	rolling & operator = (const rolling &);

};

rolling& ps_modifier_rolling = rolling::instance();
