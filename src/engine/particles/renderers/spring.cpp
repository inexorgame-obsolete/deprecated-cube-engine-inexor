#include "engine.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a spring renderer.
 */
struct spring_renderer : public particle_renderer_implementation
{

public:

	static spring_renderer& instance()
	{
		static spring_renderer _instance;
		return _instance;
	}
	virtual ~spring_renderer() { }

	void before(particle_renderer_instance *pr_inst)
	{
		if (editmode)
		{
			glPushMatrix();
			shader->set();
			glBegin(GL_LINES);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			ps.spring_lock = false;
			std::list<spring_instance *>::iterator spring_it = ps.spring_instances.begin();
			if (color_forces)
			{
				while (!ps.spring_lock && spring_it != ps.spring_instances.end())
				{
					vec o1 = vec((*spring_it)->p_inst_1->o);
					vec o2 = vec((*spring_it)->p_inst_2->o);
					vec spring = vec(o1).sub(o2);
					float actual_spring_length = spring.magnitude();
					vec force(0.0f, 0.0f, 0.0f);
					if (actual_spring_length != 0.0f)
					{
						force = spring.mul((actual_spring_length - (*spring_it)->spring_length) * (-(*spring_it)->spring_constant) / actual_spring_length);
					}
					force.add(vec(o2).sub(o1).mul((*spring_it)->spring_friction)).div(max_force);
					glColor4f(force.r, force.g, force.b, 0.75f);
					max_force.r = std::max(max_force.r, force.r);
					max_force.g = std::max(max_force.g, force.g);
					max_force.b = std::max(max_force.b, force.b);
					glVertex3d((*spring_it)->p_inst_1->o.x, (*spring_it)->p_inst_1->o.y, (*spring_it)->p_inst_1->o.z);
					glVertex3d((*spring_it)->p_inst_2->o.x, (*spring_it)->p_inst_2->o.y, (*spring_it)->p_inst_2->o.z);
					++spring_it;
				}
			} else {
				while (!ps.spring_lock && spring_it != ps.spring_instances.end())
				{
					glVertex3d((*spring_it)->p_inst_1->o.x, (*spring_it)->p_inst_1->o.y, (*spring_it)->p_inst_1->o.z);
					glVertex3d((*spring_it)->p_inst_2->o.x, (*spring_it)->p_inst_2->o.y, (*spring_it)->p_inst_2->o.z);
					++spring_it;
				}
				// conoutf("springs: %d", (int) ps.spring_instances.size());
			}
			glEnd();
			glPopMatrix();
		}
	}

	/**
	 * No particles to render.
	 */
	void render(particle_renderer_instance *pr_inst, particle_instance *p_inst)
	{
	}

	void after(particle_renderer_instance *pr_inst)
	{
	}

private:

	vec max_force;
	bool color_forces; // TODO: use attributes in renderer instance
	Shader *shader;

	spring_renderer() : particle_renderer_implementation("spring_renderer") {
		ps.particle_renderer_implementations.push_back(this);
		max_force = vec(1.0f, 1.0f, 1.0f);
		color_forces = true;
		shader = lookupshaderbyname("stdworld");
	}
	spring_renderer( const spring_renderer& );
	spring_renderer & operator = (const spring_renderer &);

};

spring_renderer& ps_renderer_spring = spring_renderer::instance();
