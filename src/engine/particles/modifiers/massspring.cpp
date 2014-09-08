#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of the mass spring simulation.
 */
struct mass_spring_transformation : public particle_modifier_implementation
{

public:

	static mass_spring_transformation& instance()
	{
		static mass_spring_transformation _instance;
		return _instance;
	}
	virtual ~mass_spring_transformation() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) {
	}

	inline void modify(int elapsedtime) {
		if (elapsedtime > 50) return; // skip frame
		time_factor = elapsedtime / (ps.particle_frame * 3.0f);
		std::list<spring_instance *>::iterator spring_it = ps.spring_instances.begin();
		int a = 0;
		while (spring_it != ps.spring_instances.end())
		{
			if ((*spring_it)->p_inst_1->remaining > 0 && (*spring_it)->p_inst_2->remaining > 0)
			{

				o1 = vec((*spring_it)->p_inst_1->pos->o);
				o2 = vec((*spring_it)->p_inst_2->pos->o);
				spring = vec(o1).sub(o2);
				actual_spring_length = spring.magnitude();
				force = vec(0.0f, 0.0f, 0.0f);
				if (actual_spring_length != 0.0f)
					force = spring.mul((actual_spring_length - (*spring_it)->spring_length) * (-(*spring_it)->spring_constant) / actual_spring_length);
				force.add(vec(o2).sub(o1).mul((*spring_it)->spring_friction)).mul(time_factor);

				// Variant 1:

				(*spring_it)->p_inst_1->vel.add(force);
				(*spring_it)->p_inst_2->vel.sub(force);
/*
*/

				// Variant 2:
/*
				vec v1 = vec((*spring_it)->p_inst_1->o).add(vec((*spring_it)->p_inst_1->vel).add(force));
				vec v2 = vec((*spring_it)->p_inst_2->o).add(vec((*spring_it)->p_inst_2->vel).add(force));
				float newlen = v1.sub(v2).magnitude();
				float stretch_factor = newlen / (*spring_it)->spring_length;
				if (a == 30) conoutf("springlen: %2.2f actual_spring_length: %2.2f force: (%2.2f, %2.2f, %2.2f) newlen: %2.2f stretchfactor: %2.2f", (*spring_it)->spring_length, actual_spring_length, force.x, force.y, force.z, newlen, stretch_factor);
				if (stretch_factor < max_stretch && stretch_factor > min_stretch)
				{
					(*spring_it)->p_inst_1->vel.add(force);
					(*spring_it)->p_inst_2->vel.sub(force);
				}
*/

				++spring_it;
			} else {
				spring_it = ps.spring_instances.erase(spring_it);
				ps.spring_lock = true;
			}
		}
	}

	void render_edit_overlay(particle_modifier_instance *entity_instance) { }

private:

	float time_factor;
	float max_stretch;
	float min_stretch;
	float actual_spring_length;
	vec o1;
	vec o2;
	vec spring;
	vec force;

	mass_spring_transformation() : particle_modifier_implementation("mass_spring_transformation") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
		max_stretch = 1.2f;
		min_stretch = 0.8f;
		actual_spring_length = 0.0f;
		o1 = vec(0.0f, 0.0f, 0.0f);
		o2 = vec(0.0f, 0.0f, 0.0f);
		spring = vec(0.0f, 0.0f, 0.0f);
		force = vec(0.0f, 0.0f, 0.0f);
	}
	mass_spring_transformation( const mass_spring_transformation& );
	mass_spring_transformation & operator = (const mass_spring_transformation &);

};

mass_spring_transformation& ps_modifier_mass_spring_transformation = mass_spring_transformation::instance();
