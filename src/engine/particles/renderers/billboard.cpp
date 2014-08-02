#define GL_GLEXT_PROTOTYPES
#include "engine.h"
#include "engine/particles/particles.h"
#include <GL/glext.h>

struct billboard_renderer : public particle_renderer_implementation
{

	Texture *tex;
	int texclamp;
	float fade_threshold_size;
	float min_size;
	float max_size;
	float quadratic[3];

	billboard_renderer() : particle_renderer_implementation("billboard_renderer") {
		particle_renderer_implementations.push_back(this);
		texclamp = 0;
		fade_threshold_size = 75.0f;
		min_size = 1.0f;
		max_size = 150.0f;
		quadratic[0] = 1.0f;
		quadratic[1] = 0.0f;
		quadratic[2] = 0.01f;
	}
	virtual ~billboard_renderer() { }

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
        tex = textureload(pr_inst->texture.c_str(), texclamp);
        glBindTexture(GL_TEXTURE_2D, tex->id);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_POINT_SPRITE);
		glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, quadratic);
		glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, fade_threshold_size);
		glPointParameterf(GL_POINT_SIZE_MIN_ARB, min_size);
		glPointParameterf(GL_POINT_SIZE_MAX_ARB, max_size);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
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
		glDisable(GL_POINT_SPRITE);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

};

billboard_renderer *ps_renderer_billboard = new billboard_renderer();
