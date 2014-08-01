#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_type> particle_types;

int add_particle_type(std::string name, std::string renderer)
{
	particle_types.add();
	int id = particle_types.length() - 1;
	particle_types[id].name = name;
	particle_types[id].renderer_type = get_particle_renderer_type(renderer);
	return id;
}

int get_particle_type(std::string name)
{
	loopv(particle_types)
	{
		if (particle_types[i].name.compare(name) == 0) return i;
	}
	return -1;
}

ICOMMAND(add_particle_type, "ss", (char *name, char *renderer_type), intret(add_particle_type(name, renderer_type)));
ICOMMAND(get_particle_type, "s", (char *name), intret(get_particle_type(name)));
ICOMMAND(particle_types_num, "", (), intret(particle_types.length()));
ICOMMAND(ls_particle_types, "", (),
{
	loopv(particle_types) {
		conoutf("%i | %s | %i", i, particle_types[i].name.c_str(), particle_types[i].renderer_type);
	}
});
