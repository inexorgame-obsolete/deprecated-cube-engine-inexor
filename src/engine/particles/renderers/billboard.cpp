#include "cube.h"
#include "engine/particles/particles.h"

struct billboard_renderer : public particle_renderer_implementation
{

	billboard_renderer() : particle_renderer_implementation("billboard_renderer") {
		particle_renderer_implementations.push_back(this);
	}
	virtual ~billboard_renderer() { }

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glPointSize(pr_inst->attributes["size"]);
		glDepthMask(false);
		glColor4f(pr_inst->attributes["r"], pr_inst->attributes["g"], pr_inst->attributes["b"], pr_inst->attributes["a"]);
		glBegin(GL_POINTS);
	}

	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst) {
		glVertex3f(p_inst->o.x, p_inst->o.y, p_inst->o.z);
	}

	void after(particle_renderer_instance *pr_inst) {
		glEnd();
		glDepthMask(true);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
		glPopMatrix();
	}

};

billboard_renderer *ps_renderer_billboard = new billboard_renderer();
