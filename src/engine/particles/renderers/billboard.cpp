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

		glShadeModel(GL_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
/*
		GLfloat fSizes[2];
        glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, fSizes);
		glPointSize(pr_inst->attributes["size"]);
*/
		glDepthMask(GL_FALSE);


		glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

		if (!shader) shader = lookupshaderbyname("particlepoints");
		if(!shader) return;
		shader->set();
		//"roher code", wenns funktioniert anpassen an sauers-shader + eig nur ein aufruf benötigt (wenn sich der wert verändert und am anfang)
		glUniform1f_(glGetUniformLocation_(shader->program, "pointSize"), 100.0);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

		glEnable(GL_TEXTURE_2D);
        tex = textureload(pr_inst->texture.c_str(), texclamp);
        glBindTexture(GL_TEXTURE_2D, tex->id);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glBegin(GL_POINTS);
		glColor4f(pr_inst->color.r, pr_inst->color.g, pr_inst->color.b, pr_inst->color.a);
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
		shader = lookupshaderbyname("particlepoints");
		if(!shader) conoutf("cannot find particlepoints shader definition");
	}
	billboard_renderer( const billboard_renderer& );
	billboard_renderer & operator = (const billboard_renderer &);

};

billboard_renderer& ps_renderer_billboard = billboard_renderer::instance();
