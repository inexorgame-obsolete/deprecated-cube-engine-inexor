#include "cube.h"
#include "particles.h"

struct velocity_transformation : particle_modifier_implementation
{
	velocity_transformation()
    {
		strcpy(name, newstring("velocity_transformation"));
		particle_modifier_implementations.add(this);
		add_particle_modifier_type(name, name);
    }

	void modify() {
		conoutf("%s:modify()", "velocity_transformation");
	}

};

velocity_transformation *velt = new velocity_transformation();
