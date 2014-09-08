#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a modifier that calls a sub emitter.
 */
struct sub_emitter : public particle_modifier_implementation
{

public:

	static sub_emitter& instance()
	{
		static sub_emitter _instance;
		return _instance;
	}
	virtual ~sub_emitter() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		particle_emitter_instance* pe_inst = static_cast<particle_emitter_instance*>(pm_inst->pointers["sub_emitter"]);
		pe_inst->pos->o = vec(p_inst->pos->o);
		pe_inst->vel = vec(p_inst->vel);
		ps.emit_particles(pe_inst, elapsedtime);
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	sub_emitter() : particle_modifier_implementation("sub_emitter") {
		ps.add_modifier_implementation(this);
	}
	sub_emitter( const sub_emitter& );
	sub_emitter & operator = (const sub_emitter &);

};

sub_emitter& ps_modifier_sub_emitter = sub_emitter::instance();
