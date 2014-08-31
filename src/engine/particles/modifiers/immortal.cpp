#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Makes particles immortal.
 */
struct immortal : public particle_modifier_implementation
{

public:

	static immortal& instance()
	{
		static immortal _instance;
		return _instance;
	}
	virtual ~immortal() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		p_inst->remaining = RAND_MAX;
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

private:

	immortal() : particle_modifier_implementation("immortal") {
		ps.add_modifier_implementation(this);
	}
	immortal( const immortal& );
	immortal & operator = (const immortal &);

};

immortal& ps_modifier_immortal = immortal::instance();
