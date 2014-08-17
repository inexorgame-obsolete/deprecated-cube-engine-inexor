#include "engine.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a model renderer.
 */
struct model_renderer : public particle_renderer_implementation
{

public:

	static model_renderer& instance()
	{
		static model_renderer _instance;
		return _instance;
	}
	virtual ~model_renderer() { }

	void before(particle_renderer_instance *pr_inst) {
        m = loadmodel(pr_inst->texture.c_str());
		glPushMatrix();
        default_shader->set();
		glDepthMask(false);
	}

	/**
	 * Rendering of a colored model.
	 */
	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst) {
        if(m)
        {
            // entitylight light;
        	// light.color = vec(1, 1, 1);
        	// light.dir = vec(0, -1, 2).normalize();
            // vec center, radius;
            // m->boundbox(center, radius);
            // float dist =  2.0f*max(radius.magnitude2(), 1.1f*radius.z);
            // float yaw = fmod(lastmillis/10000.0f*360.0f, 360.0f);
            // vec o(-center.x, dist - center.y, -0.1f*dist - center.z);
            float yaw, pitch;
            vectoyawpitch(p_inst->vel, yaw, pitch);
            rendermodel(NULL, pr_inst->texture.c_str(), ANIM_MAPMODEL|ANIM_LOOP, p_inst->o, yaw, pitch, MDL_CULL_VFC|MDL_CULL_OCCLUDED|MDL_LIGHT|MDL_LIGHT_FAST|MDL_DYNSHADOW, NULL, NULL, 0);
        }
	}

	void after(particle_renderer_instance *pr_inst) {
		glDepthMask(true);
		glPopMatrix();
		m = NULL;
	}

private:

	model *m;
	Texture *tex;
	int texclamp;
	Shader *default_shader;

	model_renderer() : particle_renderer_implementation("model_renderer") {
		ps.add_renderer_implementation(this);
		m = NULL;
		tex = NULL;
		texclamp = 0;
		default_shader = lookupshaderbyname("default");
	}
	model_renderer( const model_renderer& );
	model_renderer & operator = (const model_renderer &);

};

model_renderer& ps_renderer_model = model_renderer::instance();
