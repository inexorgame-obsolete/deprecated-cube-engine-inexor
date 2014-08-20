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
	inline std::list<particle_instance*> emit(particle_emitter_instance *pe_inst, int elapsedtime)
	{
		std::list<particle_instance*> emitted;
		return emitted;
	}

private:

	noop_emitter() : particle_emitter_implementation("noop_emitter")
	{
		ps.add_emitter_implementation(this);
	}
	noop_emitter( const noop_emitter& );
	noop_emitter & operator = (const noop_emitter &);

};

noop_emitter& ps_emitter_noop = noop_emitter::instance();
