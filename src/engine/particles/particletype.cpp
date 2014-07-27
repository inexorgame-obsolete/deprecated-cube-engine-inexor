#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_type> particle_types;

int add_particle_type(const char *name, const char *renderer)
{
	particle_types.add();
	int id = particle_types.length() - 1;
	strcpy(particle_types[id].name, newstring(name));
	particle_types[id].renderer_type = get_particle_renderer_type(renderer);
	return id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_type(const char *name)
{
	int particle_type = get_particle_type(name);
	if (particle_type >= 0) particle_types.remove(particle_type);
}

int get_particle_type(const char *name)
{
	loopv(particle_types)
	{
		if (strcmp(particle_types[i].name, name) == 0) return i;
	}
	return -1;
}

ICOMMAND(add_particle_type, "ss", (char *name, char *renderer_type), intret(add_particle_type(name, renderer_type)));
COMMAND(remove_particle_type, "s");
ICOMMAND(get_particle_type, "s", (char *name), intret(get_particle_type(name)));
ICOMMAND(particle_types_num, "", (), intret(particle_types.length()));
ICOMMAND(ls_particle_types, "", (),
{
	loopv(particle_types) {
		conoutf("%i | %s | %i", i, particle_types[i].name, particle_types[i].renderer_type);
	}
});
