#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a noop modifier.
 */
struct noop_modifier : public particle_modifier_implementation
{

public:

	static noop_modifier& instance()
	{
		static noop_modifier _instance;
		return _instance;
	}
	virtual ~noop_modifier() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) { }

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

private:

	noop_modifier() : particle_modifier_implementation("noop_modifier") {
		ps.add_modifier_implementation(this);
		ps.noop_modifier_impl = this;
	}
	noop_modifier( const noop_modifier& );
	noop_modifier & operator = (const noop_modifier &);

};

noop_modifier& ps_modifier_noop = noop_modifier::instance();
