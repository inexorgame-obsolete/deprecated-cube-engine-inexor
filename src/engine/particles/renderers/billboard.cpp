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

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();
		// glDisable(GL_TEXTURE_CUBE_MAP_ARB);
		// glDisable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        // glDisable(GL_DEPTH_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// default_shader->set();

/*
		GLfloat fSizes[2];
        glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, fSizes);
*/

/**
		glEnable(GL_POINT_SPRITE);
        glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, quadratic);
		glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, fade_threshold_size);
		glPointParameterf(GL_POINT_SIZE_MIN, fSizes[0]);
		glPointParameterf(GL_POINT_SIZE_MAX, fSizes[1]);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
**/

/*
		glPointSize(pr_inst->attributes["size"]);

		glEnable(GL_POINT_SPRITE_ARB);
		glPointParameterfvARB_(GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic);
		glPointParameterfARB_(GL_POINT_FADE_THRESHOLD_SIZE_ARB, fade_threshold_size);
		glPointParameterfARB_(GL_POINT_SIZE_MIN_ARB, fSizes[0]);
		glPointParameterfARB_(GL_POINT_SIZE_MAX_ARB, fSizes[1]);
		glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);

		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glDisable(GL_TEXTURE_2D);

*/
		glDepthMask(GL_FALSE);


		glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

		if (!shader) shader = lookupshaderbyname("particlepoints");
		if(!shader) return;
		shader->set();
		//"roher code", wenns funktioniert anpassen an sauers-shader + eig nur ein aufruf benötigt (wenn sich der wert verändert und am anfang)
		glUniform1f(glGetUniformLocation_(shader->program, "pointSize"), 100.0);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

		glEnable(GL_TEXTURE_2D);
        tex = textureload(pr_inst->texture.c_str(), texclamp);
        glBindTexture(GL_TEXTURE_2D, tex->id);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glBegin(GL_POINTS);
		glColor4f(pr_inst->color.r, pr_inst->color.g, pr_inst->color.b, pr_inst->color.a);
		//        conoutf("GL_SMOOTH_POINT_SIZE_RANGE: %3.3f - %3.3f", fSizes[0], fSizes[1]);
	}

	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst) {
		// glTexCoord2f(0.5f, 0.5f);
		glVertex3f(p_inst->pos->o.x, p_inst->pos->o.y, p_inst->pos->o.z);
	}

	void after(particle_renderer_instance *pr_inst) {
		glEnd();
		glDisable(GL_POINT_SPRITE);
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_TEXTURE_2D);
		/*
//		glDisable(GL_POINT_SPRITE);
		glDisable(GL_POINT_SPRITE_ARB);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_TEXTURE_2D);
//		glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE, GL_TRUE);
//		glDisable(GL_DEPTH_TEST);
//		glEnable(GL_CULL_FACE);

*/
		glPopMatrix();
	}

	void render_edit_overlay(particle_renderer_instance *entity_instance) { }

private:

	Texture *tex;
	int texclamp;
	float fade_threshold_size;
	float min_size;
	float max_size;
	float quadratic[3];
	Shader *shader;
	// Shader *stdworldshader;
	// Shader *default_shader;
	// Shader *particle_shader;
	// Shader *particle_shader_notexture;
	// Shader *particlesoftshader;
	// int program;

	billboard_renderer() : particle_renderer_implementation("billboard_renderer") {
		ps.add_renderer_implementation(this);
		tex = NULL;
		texclamp = 0;
		fade_threshold_size = 0.5f;
		min_size = 1.0f;
		max_size = 150.0f;
		// quadratic[0] = 1.0f;
		// quadratic[1] = 0.0f;
		// quadratic[2] = 0.01f;
		quadratic[0] = 0.25f;
		quadratic[1] = 0.0f;
		quadratic[2] = 1 / 60.0f;
	    // stdworldshader = lookupshaderbyname("stdworld");
		// default_shader = lookupshaderbyname("default");
		// particle_shader = lookupshaderbyname("particle");
		// particle_shader_notexture = lookupshaderbyname("particlenotexture");
        // particlesoftshader = lookupshaderbyname("particlesoft");
		shader = lookupshaderbyname("particlepoints");
		if(!shader) conoutf("cannot find particlepoints shader definition");
	}
	billboard_renderer( const billboard_renderer& );
	billboard_renderer & operator = (const billboard_renderer &);

};

billboard_renderer& ps_renderer_billboard = billboard_renderer::instance();
