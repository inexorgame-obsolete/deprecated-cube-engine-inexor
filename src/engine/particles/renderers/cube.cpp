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

	Texture *tex;
	int texclamp;

	void before(particle_renderer_instance *pr_inst) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
        tex = textureload(pr_inst->texture.c_str(), texclamp);
        glBindTexture(GL_TEXTURE_2D, tex->id);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
	}

	/**
	 * Rendering of a colored cube.
	 */
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
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

private:

	cube_renderer() : particle_renderer_implementation("cube_renderer") {
		particle_renderer_implementations.push_back(this);
		tex = NULL;
		texclamp = 0;
	}
	cube_renderer( const cube_renderer& );
	cube_renderer & operator = (const cube_renderer &);

};

cube_renderer& ps_renderer_cube = cube_renderer::instance();
