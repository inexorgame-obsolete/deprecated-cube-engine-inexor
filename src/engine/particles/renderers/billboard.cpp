#include "engine.h"
#include "engine/particles/particles.h"

struct billboard_renderer : public particle_renderer_implementation
{

public:

	static billboard_renderer& instance()
	{
		static billboard_renderer _instance;
		return _instance;
	}
	virtual ~billboard_renderer() { }

	Texture *tex;
	int texclamp;
	float fade_threshold_size;
	float min_size;
	float max_size;
	float quadratic[3];

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
        tex = textureload(pr_inst->texture.c_str(), texclamp);
        glBindTexture(GL_TEXTURE_2D, tex->id);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_POINT_SPRITE_ARB);
		glPointParameterfvARB_(GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic);
		glPointParameterfARB_(GL_POINT_FADE_THRESHOLD_SIZE_ARB, fade_threshold_size);
		glPointParameterfARB_(GL_POINT_SIZE_MIN_ARB, min_size);
		glPointParameterfARB_(GL_POINT_SIZE_MAX_ARB, max_size);
		glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE, GL_TRUE);
		glPointSize(pr_inst->attributes["size"]);
		glDepthMask(false);
		glColor4f(pr_inst->color.r, pr_inst->color.g, pr_inst->color.b, pr_inst->color.a);
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

private:

	billboard_renderer() : particle_renderer_implementation("billboard_renderer") {
		particle_renderer_implementations.push_back(this);
		tex = NULL;
		texclamp = 0;
		fade_threshold_size = 75.0f;
		min_size = 1.0f;
		max_size = 150.0f;
		quadratic[0] = 1.0f;
		quadratic[1] = 0.0f;
		quadratic[2] = 0.01f;
	}
	billboard_renderer( const billboard_renderer& );
	billboard_renderer & operator = (const billboard_renderer &);

};

billboard_renderer& ps_renderer_billboard = billboard_renderer::instance();
