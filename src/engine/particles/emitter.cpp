#include "cube.h"
#include "particles.h"

int timer_emitter = 0;

// abstract definitions - makes everything dynamic
std::vector<particle_emitter_type*> particle_emitter_types;
std::map<std::string, particle_emitter_type*> particle_emitter_types_map;

// implementations - the concrete implementations
std::vector<particle_emitter_implementation*> particle_emitter_implementations;
std::map<std::string, particle_emitter_implementation*> particle_emitter_implementations_map;

// concrete instances refers to the abstract definitions
std::vector<particle_emitter_instance*> particle_emitter_instances;

void emit_particles(int elapsedtime)
{
	int started = SDL_GetTicks();
	for(std::vector<particle_emitter_instance*>::iterator it = particle_emitter_instances.begin(); it != particle_emitter_instances.end(); ++it)
	{
		if ((*it)->enabled) (*it)->pe_type->pe_impl->emit(*it, elapsedtime);
	}
	timer_emitter = SDL_GetTicks() - started;
}

/**
 * By emitting a particle we want to reuse dead particles in order to save
 * memory.
 */
particle_instance* emit_particle()
{
	if (dead_pool.size() > 0)
	{
		// reanimate a dead particle
		particle_instance* p_inst = dead_pool.back();
		dead_pool.pop_back();
		return p_inst;
	} else {
		// dynamically create a new particle instance
		particle_instance *pi = new particle_instance;
		return pi;
	}
}

particle_emitter_type* add_particle_emitter_type(const std::string name, const std::string p_type, float mass, float density, int lifetime, int rate, const std::string impl)
{
	particle_emitter_type* pe_type = new particle_emitter_type;
	pe_type->name = name;
	pe_type->mass = mass;
	pe_type->density = density;
	pe_type->lifetime = lifetime;
	pe_type->rate = rate;
	pe_type->p_type = particle_types_map[p_type];
	pe_type->pe_impl = particle_emitter_implementations_map[impl];
	particle_emitter_types.push_back(pe_type);
	particle_emitter_types_map[name] = pe_type;
	// conoutf("name: %s", impl.c_str());
	// conoutf("name: %s", pe_type->pe_impl->name.c_str());
	// conoutf("Added particle emitter type \"%s\" (mass: %2.2f density: %2.2f lifetime: %d rate: %d ms parttype: %s) of implementation \"%s\"", pe_type->name.c_str(), mass, density, lifetime, rate, pe_type->p_type->name.c_str(), pe_type->pe_impl->name.c_str());
	return pe_type;
}

void particle_emitter_instance::add_modifier(particle_modifier_instance* pm_inst)
{
	modifiers.push_back(pm_inst);
}

particle_emitter_instance* particle_emitter_type::create_instance(const vec &o, const vec &vel)
{
	particle_emitter_instance* pe_inst = new particle_emitter_instance;
	pe_inst->pe_type = this;
	pe_inst->p_type = p_type;
	pe_inst->o = o;
	pe_inst->vel = vel;
	pe_inst->enabled = true;
	pe_inst->mass = mass;
	pe_inst->density = density;
	pe_inst->lifetime = lifetime;
	pe_inst->rate = rate;
	pe_inst->millistoprocess = 0;
	// initialize default modifiers by copy all modifiers
	pe_inst->modifiers = modifiers;
	// initialize default attributes by copy the attributes map
	pe_inst->attributes.insert(attributes.begin(), attributes.end());
	particle_emitter_instances.push_back(pe_inst);
	return pe_inst;
}

particle_emitter_instance* create_particle_emitter_instance(std::string type, const vec &o, const vec &vel)
{
	return particle_emitter_types_map[type]->create_instance(o, vel);
}

ICOMMAND(add_particle_emitter_type, "ssiiiis", (char *name, char *particle_type, int *mass, int *density, int *lifetime, int *rate, char *impl), add_particle_emitter_type(name, particle_type, *mass, *density, *lifetime, *rate, impl));
ICOMMAND(create_particle_emitter_instance, "siiiiii", (char *type, int *ox, int *oy, int *oz, int *vx, int *vy, int *vz), create_particle_emitter_instance(type, vec(*ox, *oy, *oz), vec(*vx, *vy, *vz)));

/*
ICOMMAND(particle_emitter_types_num, "", (), intret(particle_emitter_types.size()));
ICOMMAND(assign_modifier_to_emitter, "ss", (char *modifier_name, char *emitter_name), intret(assign_modifier_to_emitter(modifier_name, emitter_name)));
ICOMMAND(ls_particle_emitter_types, "", (),
{
	for(std::vector<particle_emitter_type>::iterator it = particle_emitter_types.begin(); it != particle_emitter_types.end(); ++it) {
		conoutf("%s | %i | %i", it->name.c_str(), it->particle_type, particle_emitter_types[i].lifetime);
	}
});
*/
