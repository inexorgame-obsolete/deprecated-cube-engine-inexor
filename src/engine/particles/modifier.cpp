#include "cube.h"
#include "particles.h"

VARP(modifiers, 0, 1, 1);

/*
// abstract definitions - makes everything dynamic
std::vector<particle_modifier_type*> particle_modifier_types;
std::map<std::string, particle_modifier_type*> particle_modifier_types_map;

// implementations - the concrete implementations
std::vector<particle_modifier_implementation*> particle_modifier_implementations;
std::map<std::string, particle_modifier_implementation*> particle_modifier_implementations_map;

// concrete instances refers to the abstract definitions
std::vector<particle_modifier_instance*> particle_modifier_instances;
*/

void particle_system::modify_particles(int elapsedtime)
{
	if (modifiers) {
		int started = SDL_GetTicks();
		// Called once per modifier implementations.
		for(std::vector<particle_modifier_implementation*>::iterator pm_it = particle_modifier_implementations.begin(); pm_it != particle_modifier_implementations.end(); ++pm_it)
		{
			(*pm_it)->modify(elapsedtime);
		}
		// Called for each modifier instances.
		for(std::vector<particle_modifier_instance*>::iterator pm_it = particle_modifier_instances.begin(); pm_it != particle_modifier_instances.end(); ++pm_it)
		{
			(*pm_it)->pm_type->pm_impl->modify(*pm_it, elapsedtime);
		}
		// Called for each particle instance and their modifier instances.
		for(std::list<particle_instance*>::iterator p_it = alive_pool.begin(); p_it != alive_pool.end(); ++p_it)
		{
			for(std::vector<particle_modifier_instance*>::iterator pm_it = (*p_it)->pe_inst->modifiers.begin(); pm_it != (*p_it)->pe_inst->modifiers.end(); ++pm_it)
			{
				(*pm_it)->pm_type->pm_impl->modify(*pm_it, *p_it, elapsedtime);
			}
		}
		timer_modifier = SDL_GetTicks() - started;
		// TODO: special types of modifiers which are called afterwards only
	}
}

particle_modifier_type* particle_system::add_particle_modifier_type(std::string name, std::string impl)
{
	particle_modifier_type* pm_type = new particle_modifier_type;
	pm_type->name = name;
	pm_type->pm_impl = particle_modifier_implementations_map[impl];
	particle_modifier_types.push_back(pm_type);
	particle_modifier_types_map[name] = pm_type;
	conoutf("Added particle modifier type \"%s\" of implementation \"%s\"", name.c_str(), impl.c_str());
	return pm_type;
}

particle_modifier_instance* particle_modifier_type::create_instance() {
	return create_instance(vec(0.0f, 0.0f, 0.0f));
}

particle_modifier_instance* particle_modifier_type::create_instance(const vec &o) {
	particle_modifier_instance* pm_inst = new particle_modifier_instance;
	pm_inst->pm_type = this;
	pm_inst->o = o;
	pm_inst->attributes.insert(attributes.begin(), attributes.end());
	ps.particle_modifier_instances.push_back(pm_inst);
	return pm_inst;
}

void create_particle_modifier_instance(std::string pm_type, const vec &o) {
	ps.particle_modifier_types_map[pm_type]->create_instance(o);
}

// ICOMMAND(add_particle_modifier_type, "ss", (char *name, char *impl), add_particle_modifier_type(name, impl));
// ICOMMAND(create_particle_modifier_instance, "siii", (char *name, int *ox, int *oy, int *oz), create_particle_modifier_instance(name, vec(*ox, *oy, *oz)));

/*
ICOMMAND(particle_modifier_types_num, "", (), intret(particle_modifier_types.size()));
ICOMMAND(particle_modifier_instances_num, "", (), intret(particle_modifier_instances.size()));
ICOMMAND(ls_particle_modifier_types, "", (),
{
	loopv(particle_modifier_types) {
		conoutf("%i | %s", i, particle_modifier_types[i].name.c_str());
	}
});
*/
