#include "cube.h"
#include "particles.h"

VARP(modifiers, 0, 1, 1);

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
			(*pm_it)->type->impl->modify(*pm_it, elapsedtime);
		}
		// Called for each particle instance and their modifier instances.
		for(std::list<particle_instance*>::iterator p_it = alive_pool.begin(); p_it != alive_pool.end(); ++p_it)
		{
			for(std::vector<particle_modifier_instance*>::iterator pm_it = (*p_it)->pe_inst->modifiers.begin(); pm_it != (*p_it)->pe_inst->modifiers.end(); ++pm_it)
			{
				(*pm_it)->type->impl->modify(*pm_it, *p_it, elapsedtime);
			}
		}
		timer_modifier = SDL_GetTicks() - started;
		// TODO: special types of modifiers which are called afterwards only
	}
	/*
	if (editmode)
	{
		for(std::vector<particle_modifier_instance*>::iterator it = particle_modifier_instances.begin(); it != particle_modifier_instances.end(); ++it)
		{
			(*it)->o = vec((*it)->ent->o);
		}
	}
	*/
}

particle_modifier_type* particle_system::add_particle_modifier_type(std::string name, std::string impl)
{
	if (!particle_modifier_types_map.count(name))
	{
		particle_modifier_type* pm_type = new particle_modifier_type;
		pm_type->name = name;
		pm_type->impl = particle_modifier_implementations_map[impl];
		particle_modifier_types.push_back(pm_type);
		particle_modifier_types_map[name] = pm_type;
		conoutf("Added particle modifier type \"%s\" of implementation \"%s\"", name.c_str(), impl.c_str());
		count_particle_modifier_types++;
		return pm_type;
	} else {
		conoutf("Particle modifier type %s already exists!", name.c_str());
		return particle_modifier_types_map[name];
	}
}

// TODO: no positions anymore!
particle_modifier_instance* particle_modifier_type::create_instance() {
// 	return create_instance(vec(0.0f, 0.0f, 0.0f));
// }

// TODO: no positions anymore!
// particle_modifier_instance* particle_modifier_type::create_instance(const vec &o) {
	particle_modifier_instance* pm_inst = new particle_modifier_instance;
	pm_inst->type = this;
	// pm_inst->o = o;
	// pm_inst->positions =
	pm_inst->attributes.insert(attributes.begin(), attributes.end());
	pm_inst->pointers.insert(pointers.begin(), pointers.end());

/*
	// create entity and attach to the instance object
	int idx;
	pm_inst->ent = newentity(true, vec(o), EP_MODIFIER, 0, 0, 0, 0, 0, idx);  // yeah i love the hard coded entity system, which would break every map if i would insert a new entity type on engine level. This is only a quick fix and have to replace by an integration into the new entity system
	addentity(idx);
	pm_inst->ent->spawned = true;
*/

	ps.particle_modifier_instances.push_back(pm_inst);
	ps.count_particle_modifier_instances++;
	conoutf("Created particle modifier instance of type \"%s\"", name.c_str());
	return pm_inst;
}

// TODO: no positions anymore!
particle_modifier_instance* particle_system::create_particle_modifier_instance(std::string pm_type) // , const vec &o
{
	if (particle_modifier_types_map.count(pm_type))
	{
		return particle_modifier_types_map[pm_type]->create_instance(); // o);
	} else {
		conoutf("Particle modifier type %s not found!", pm_type.c_str());
		return noop_modifier_inst;
	}
}

void particle_system::remove_particle_modifier_type(std::string name)
{
	if (particle_modifier_types_map.count(name))
	{
		particle_modifier_types_map.erase(name);
		// TODO: remove from particle_modifier_types
		count_particle_modifier_types--;
	} else {
		conoutf("Particle modifier type %s not found!", name.c_str());
	}
}

void particle_system::remove_all_particle_modifier_types()
{
	particle_modifier_types_map.clear();
	particle_modifier_types.clear();
	particle_modifier_types.push_back(noop_modifier_type);
	particle_modifier_types_map["noop"] = noop_modifier_type;
	count_particle_modifier_types = 1;
}

void particle_system::remove_all_particle_modifier_instances()
{
	particle_modifier_instances.clear();
	particle_modifier_instances.push_back(noop_modifier_inst);
	count_particle_modifier_instances = 1;
}

void create_particle_modifier_instance(std::string pm_type) { //, const vec &o
	ps.create_particle_modifier_instance(pm_type); //, o);
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
