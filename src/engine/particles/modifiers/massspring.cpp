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

	void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		// conoutf("mass_spring_transformation:modify(type: %d, emitter: %d, elapsedtime: %d)", pi.type, pi.emitter, elapsedtime);
	}

private:
	mass_spring_transformation() : particle_modifier_implementation("mass_spring_transformation") {
		particle_modifier_implementations.push_back(this);
	}
	mass_spring_transformation( const mass_spring_transformation& );
	mass_spring_transformation & operator = (const mass_spring_transformation &);

};

mass_spring_transformation& ps_modifier_mass_spring_transformation = mass_spring_transformation::instance();
