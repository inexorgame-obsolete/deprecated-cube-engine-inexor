#include "cube.h"
#include "particles.h"

VARP(emitters, 0, 1, 1);

void particle_system::emit_particles(int elapsedtime)
{
	if (emitters)
	{
		int started = SDL_GetTicks();
		for(std::vector<particle_emitter_instance*>::iterator it = particle_emitter_instances.begin(); it != particle_emitter_instances.end(); ++it)
		{
			if ((*it)->enabled) (*it)->pe_type->pe_impl->emit(*it, elapsedtime);
		}
		timer_emitter = SDL_GetTicks() - started;
	}
	if (editmode)
	{
		for(std::vector<particle_emitter_instance*>::iterator it = particle_emitter_instances.begin(); it != particle_emitter_instances.end(); ++it)
		{
			// conoutf("%3.1f %3.1f", (*it)->o.x, (*it)->ent->o.x);
			(*it)->o = (*it)->ent->o;
		}
	}
}

/**
 * By emitting a particle we want to reuse dead particles in order to save
 * memory.
 */
particle_instance* particle_system::emit_particle()
{
	if (dead_pool.size() > 0)
	{
		// reanimate a dead particle
		particle_instance* p_inst = dead_pool.back();
		dead_pool.pop_back();
		p_inst->elapsed = 0;
		return p_inst;
	} else {
		// dynamically create a new particle instance
		particle_instance *pi = new particle_instance;
		return pi;
	}
}

particle_emitter_type* particle_system::add_particle_emitter_type(const std::string name, const std::string p_type, float mass, float density, int lifetime, int rate, const std::string impl)
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
	// create entity and attach to the instance object
	int idx;
	pe_inst->ent = newentity(true, vec(o), ET_NEWPARTICLES, 0, 0, 0, 0, 0, idx);  // yeah i love the hard coded entity system, which would break every map if i would insert a new entity type on engine level. This is only a quick fix and have to replace by an integration into the new entity system

// TODO!!!!

	ps.particle_emitter_instances.push_back(pe_inst);
	return pe_inst;
}

particle_emitter_instance* particle_system::create_particle_emitter_instance(std::string type, const vec &o, const vec &vel)
{
	return particle_emitter_types_map[type]->create_instance(o, vel);
}

// ICOMMAND(add_particle_emitter_type, "ssiiiis", (char *name, char *particle_type, int *mass, int *density, int *lifetime, int *rate, char *impl), add_particle_emitter_type(name, particle_type, *mass, *density, *lifetime, *rate, impl));
// ICOMMAND(create_particle_emitter_instance, "siiiiii", (char *type, int *ox, int *oy, int *oz, int *vx, int *vy, int *vz), create_particle_emitter_instance(type, vec(*ox, *oy, *oz), vec(*vx, *vy, *vz)));

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
