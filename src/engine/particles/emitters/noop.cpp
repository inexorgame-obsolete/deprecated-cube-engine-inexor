#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a noop emitter.
 */
struct noop_emitter : public particle_emitter_implementation
{

public:

	static noop_emitter& instance()
	{
		static noop_emitter _instance;
		return _instance;
	}
	virtual ~noop_emitter() { }

	/**
	 * Emits particles from a single point (x,y,z).
	 */
	inline void emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
	}

private:

	noop_emitter() : particle_emitter_implementation("noop_emitter")
	{
		ps.particle_emitter_implementations.push_back(this);
	}
	noop_emitter( const noop_emitter& );
	noop_emitter & operator = (const noop_emitter &);

};

noop_emitter& ps_emitter_noop = noop_emitter::instance();
