#include "engine.h"
#include "engine/particles/particles.h"

struct cube_renderer : public particle_renderer_implementation
{

	cube_renderer() : particle_renderer_implementation("cube_renderer") {
		particle_renderer_implementations.push_back(this);
	}
	virtual ~cube_renderer() { }

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();
		// glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(false);
		glBegin(GL_QUADS);
	}

	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst) {
		float bbMinX = p_inst->o.x - p_inst->density;
		float bbMinY = p_inst->o.y - p_inst->density;
		float bbMinZ = p_inst->o.z - p_inst->density;
		float bbMaxX = p_inst->o.x + p_inst->density;
		float bbMaxY = p_inst->o.y + p_inst->density;
		float bbMaxZ = p_inst->o.z + p_inst->density;

		// TEST: colorize by velocity vector entries
		glColor4f(p_inst->vel.r, p_inst->vel.g, p_inst->vel.b / 255.0f, 0.3f);

		// FRONT
		glVertex3d(bbMinX, bbMinY, bbMinZ);
		glVertex3d(bbMaxX, bbMinY, bbMinZ);
		glVertex3d(bbMaxX, bbMaxY, bbMinZ);
		glVertex3d(bbMinX, bbMaxY, bbMinZ);
		// BACK
		glVertex3d(bbMaxX, bbMaxY, bbMaxZ);
		glVertex3d(bbMinX, bbMaxY, bbMaxZ);
		glVertex3d(bbMinX, bbMinY, bbMaxZ);
		glVertex3d(bbMaxX, bbMinY, bbMaxZ);
		// RIGHT
		glVertex3d(bbMaxX, bbMaxY, bbMaxZ);
		glVertex3d(bbMaxX, bbMaxY, bbMinZ);
		glVertex3d(bbMaxX, bbMinY, bbMinZ);
		glVertex3d(bbMaxX, bbMinY, bbMaxZ);
		// LEFT
		glVertex3d(bbMinX, bbMinY, bbMinZ);
		glVertex3d(bbMinX, bbMaxY, bbMinZ);
		glVertex3d(bbMinX, bbMaxY, bbMaxZ);
		glVertex3d(bbMinX, bbMinY, bbMaxZ);
		// TOP
		glVertex3d(bbMaxX, bbMaxY, bbMaxZ);
		glVertex3d(bbMinX, bbMaxY, bbMaxZ);
		glVertex3d(bbMinX, bbMaxY, bbMinZ);
		glVertex3d(bbMaxX, bbMaxY, bbMinZ);
		// BOTTOM
		glVertex3d(bbMinX, bbMinY, bbMinZ);
		glVertex3d(bbMinX, bbMinY, bbMaxZ);
		glVertex3d(bbMaxX, bbMinY, bbMaxZ);
		glVertex3d(bbMaxX, bbMinY, bbMinZ);
	}

	void after(particle_renderer_instance *pr_inst) {
		glEnd();
		glDepthMask(true);
		// glDisable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPopMatrix();
	}

};

cube_renderer *ps_renderer_cube = new cube_renderer();
