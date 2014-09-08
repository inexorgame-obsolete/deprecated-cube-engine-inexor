#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of an noop initializer.
 */
struct noop_initializer : public particle_initializer_implementation
{

public:

	static noop_initializer& instance()
	{
		static noop_initializer _instance;
		return _instance;
	}
	virtual ~noop_initializer() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) { }

	void render_edit_overlay(particle_initializer_instance *entity_instance) { }

private:

	noop_initializer() : particle_initializer_implementation("noop_initializer") {
		ps.add_initializer_implementation(this);
		ps.noop_initializer_impl = this;
	}
	noop_initializer( const noop_initializer& );
	noop_initializer & operator = (const noop_initializer &);

};

noop_initializer& ps_initializer_noop = noop_initializer::instance();
