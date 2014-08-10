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
		time_factor = elapsedtime / ps.particle_frame;
		std::list<spring_instance *>::iterator spring_it = ps.spring_instances.begin();
		while (spring_it != ps.spring_instances.end())
		{
			if ((*spring_it)->p_inst_1->remaining > 0 && (*spring_it)->p_inst_2->remaining > 0)
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
				force.add(vec(o2).sub(o1).mul((*spring_it)->spring_friction)).mul(time_factor);
				(*spring_it)->p_inst_1->vel.add(force);
				(*spring_it)->p_inst_2->vel.sub(force);
				++spring_it;
			} else {
				spring_it = ps.spring_instances.erase(spring_it);
			}
		}
	}

	inline void init(particle_instance *p_inst) { }

private:

	float time_factor;

	mass_spring_transformation() : particle_modifier_implementation("mass_spring_transformation") {
		ps.particle_modifier_implementations.push_back(this);
		time_factor = 0.0f;
	}
	mass_spring_transformation( const mass_spring_transformation& );
	mass_spring_transformation & operator = (const mass_spring_transformation &);

};

mass_spring_transformation& ps_modifier_mass_spring_transformation = mass_spring_transformation::instance();
