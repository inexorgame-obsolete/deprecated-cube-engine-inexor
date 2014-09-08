#include "engine.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a noop renderer.
 */
struct noop_renderer : public particle_renderer_implementation
{

public:

	static noop_renderer& instance()
	{
		static noop_renderer _instance;
		return _instance;
	}
	virtual ~noop_renderer() { }

	void before(particle_renderer_instance *pr_inst) { }

	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst) { }

	void after(particle_renderer_instance *pr_inst) { }

	void render_edit_overlay(particle_renderer_instance *entity_instance) { }

private:

	noop_renderer() : particle_renderer_implementation("noop_renderer") {
		ps.add_renderer_implementation(this);
		ps.noop_renderer_impl = this;
	}
	noop_renderer( const noop_renderer& );
	noop_renderer & operator = (const noop_renderer &);

};

noop_renderer& ps_renderer_noop = noop_renderer::instance();
