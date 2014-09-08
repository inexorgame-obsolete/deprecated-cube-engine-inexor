#include "engine.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a cube renderer.
 */
struct cube_renderer : public particle_renderer_implementation
{

public:

	static cube_renderer& instance()
	{
		static cube_renderer _instance;
		return _instance;
	}
	virtual ~cube_renderer() { }

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		defaultshader->set();
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);
		// glEnable(GL_TEXTURE_2D);
		// tex = textureload(pr_inst->texture.c_str(), texclamp);
		// glBindTexture(GL_TEXTURE_2D, tex->id);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glColor4f(pr_inst->color.r, pr_inst->color.g, pr_inst->color.b, pr_inst->color.a);
		glBegin(GL_QUADS);
	}

	/**
	 * Rendering of a colored cube.
	 */
	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst) {
		float bbMinX = p_inst->pos->o.x - p_inst->density;
		float bbMinY = p_inst->pos->o.y - p_inst->density;
		float bbMinZ = p_inst->pos->o.z - p_inst->density;
		float bbMaxX = p_inst->pos->o.x + p_inst->density;
		float bbMaxY = p_inst->pos->o.y + p_inst->density;
		float bbMaxZ = p_inst->pos->o.z + p_inst->density;

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
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_TEXTURE_2D);
        // glEnable(GL_DEPTH_TEST);
		// glEnable(GL_CULL_FACE);
		// glEnable(GL_TEXTURE_2D);
		// particle_shader->set();
		glPopMatrix();
        // defaultshader->set();
	}

	void render_edit_overlay(particle_renderer_instance *entity_instance) { }

private:

	Texture *tex;
	int texclamp;
	Shader *shader;

	cube_renderer() : particle_renderer_implementation("cube_renderer") {
		ps.add_renderer_implementation(this);
		tex = NULL;
		texclamp = 0;
		shader = lookupshaderbyname("stdworld");
	}
	cube_renderer( const cube_renderer& );
	cube_renderer & operator = (const cube_renderer &);

};

cube_renderer& ps_renderer_cube = cube_renderer::instance();
