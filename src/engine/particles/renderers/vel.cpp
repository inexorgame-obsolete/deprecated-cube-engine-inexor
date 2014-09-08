#include "engine.h"
#include "engine/particles/particles.h"

/**
 * Renders a line between the old position and the new position of a particle.
 */
struct vel_renderer : public particle_renderer_implementation
{

public:

	static vel_renderer& instance()
	{
		static vel_renderer _instance;
		return _instance;
	}
	virtual ~vel_renderer() { }

	void before(particle_renderer_instance *pr_inst)
	{
		glPushMatrix();
		shader->set();
		glBegin(GL_LINES);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst)
	{
		vec n = vec(p_inst->vel);
		glVertex3d(p_inst->pos->o.x, p_inst->pos->o.y, p_inst->pos->o.z);
		glVertex3d(n.x, n.y, n.z);
	}

	void after(particle_renderer_instance *pr_inst)
	{
		glEnd();
		glPopMatrix();
	}

	void render_edit_overlay(particle_renderer_instance *entity_instance) { }

private:

	Shader *shader;

	vel_renderer() : particle_renderer_implementation("vel_renderer") {
		ps.add_renderer_implementation(this);
		shader = lookupshaderbyname("stdworld");
	}
	vel_renderer( const vel_renderer& );
	vel_renderer & operator = (const vel_renderer &);

};

vel_renderer& ps_renderer_vel = vel_renderer::instance();
