#include "cube.h"
#include "particles.h"

/*
// abstract definitions - makes everything dynamic
std::vector<particle_type*> particle_types;
std::map<std::string, particle_type*> particle_types_map;
*/

particle_type* particle_system::add_particle_type(std::string name, std::string renderer)
{
	return add_particle_type(name, particle_renderer_instances_map[renderer]);
}

particle_type* particle_system::add_particle_type(std::string name, particle_renderer_instance* renderer)
{
	particle_type *pt = new particle_type;
	pt->name = name;
	pt->pr_inst = renderer;
	particle_types.push_back(pt);
	particle_types_map[name] = pt;
	count_particle_types++;
	conoutf("Added particle type \"%s\" for renderer \"%s\"", name.c_str(), renderer->name.c_str());
	return pt;
}

void particle_system::remove_particle_type(std::string name)
{
	if (particle_types_map.count(name))
	{
		particle_types_map.erase(name);
		// TODO: also remove from particle_types
		count_particle_types--;
	} else {
		conoutf("Particle type %s not found!", name.c_str());
	}
}

void particle_system::remove_all_particle_types()
{
	particle_types.clear();
	particle_types_map.clear();
	particle_types.push_back(noop_particle_type);
	particle_types_map["noop"] = noop_particle_type;
	count_particle_types = 1;
}

// ICOMMAND(add_particle_type, "ss", (char *name, char *renderer), add_particle_type(name, renderer));

/*
ICOMMAND(particle_types_num, "", (), intret(particle_types.size()));
ICOMMAND(ls_particle_types, "", (),
{
	for(std::vector<particle_type>::iterator it = particle_types.begin(); it != particle_emitter_instances.end(); ++it) {
		conoutf("%s | %i", it->name.c_str(), it->renderer_type);
	}
});
*/
