#include "cube.h"
#include "particles.h"

struct mass_spring_transformation : particle_modifier_implementation
{

	mass_spring_transformation()
    {
		strcpy(name, newstring("mass_spring_transformation"));
		particle_modifier_implementations.add(this);
		add_particle_modifier_type(name, name);
    }

	void modify() {
		conoutf("%s:modify()", "mass_spring_transformation");
	}

};

mass_spring_transformation *mst = new mass_spring_transformation();
