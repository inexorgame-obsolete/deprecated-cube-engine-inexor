#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_emitter_type> particle_emitter_types;

// implementations - the concrete implementations
vector<particle_emitter_implementation *> particle_emitter_implementations;

// concrete instances refers to the abstract definitions
vector<particle_emitter_instance> particle_emitter_instances;

void emit_particles(int elapsedtime)
{
	loopv(particle_emitter_instances)
	{
		// particle_emitter_instance pe_inst = particle_emitter_instances[i];
		// particle_emitter_type pe_type = particle_emitter_types[particle_emitter_instances[i].type];
		// conoutf("pe_inst: %2d pe_type: %2d", i, particle_emitter_instances[i].type);
		particle_emitter_types[particle_emitter_instances[i].type].impl->emit(&particle_emitter_instances[i], i, elapsedtime);
	}
}

/**
 * By emitting a particle we want to reuse dead particles in order to save
 * memory.
 */
particle_instance* emit_particle()
{
	// dynamically create a new particle instance
	particle_instance *pi = new particle_instance;
//	particle_instances.add(*pi);
	return pi;

	/*
	if (dead_pool[current_dead_pool].length() > 1)
	{
		// reanimate a dead particle
		return &dead_pool[current_dead_pool].pop();
	} else {
		// dynamically create a new particle instance
		particle_instance *pi = new particle_instance;
		return pi;
	}
*/
}

int add_particle_emitter_type(std::string name, std::string particle_type, float mass, float density, int lifetime, int rate, std::string impl)
{
	particle_emitter_types.add();
	int pe_type_id = particle_emitter_types.length() - 1;
	// particle_emitter_type pe_type = particle_emitter_types[pe_type_id];
	particle_emitter_types[pe_type_id].name = name;
	particle_emitter_types[pe_type_id].particle_type = get_particle_type(particle_type);
	particle_emitter_types[pe_type_id].mass = mass;
	particle_emitter_types[pe_type_id].density = density;
	particle_emitter_types[pe_type_id].lifetime = lifetime;
	particle_emitter_types[pe_type_id].rate = rate;
	int impl_id = get_particle_emitter_implementation(impl);
	particle_emitter_types[pe_type_id].impl = particle_emitter_implementations[impl_id];

	conoutf("Added particle emitter type \"%s\" (id: %d mass: %2.2f density: %2.2f lifetime: %d rate: %d ms parttype: %s) of implementation \"%s\" (id: %d) [%d:%d:%d]", name.c_str(), pe_type_id, mass, density, lifetime, rate, particle_type.c_str(), impl.c_str(), impl_id, particle_emitter_instances.length(), particle_emitter_types.length(), particle_emitter_implementations.length());
	return pe_type_id;
}

int get_particle_emitter_type(std::string name)
{
	loopv(particle_emitter_types)
	{
		if (particle_emitter_types[i].name.compare(name) == 0) {
			return i;
		}
	}
	return -1;
}

int get_particle_emitter_implementation(std::string name)
{
	loopv(particle_emitter_implementations)
	{
		if (particle_emitter_implementations[i]->name.compare(name) == 0) return i;
	}
	return -1;
}

int assign_modifier_to_emitter(std::string pe_name, std::string pm_name)
{
    int pe_type_id = get_particle_emitter_type(pe_name);
    int pm_type_id = get_particle_modifier_type(pm_name);
    conoutf("assign_modifier_to_emitter: %s(%d) %s(%d)", pe_name.c_str(), pe_type_id, pm_name.c_str(), pm_type_id);
    particle_emitter_types[pe_type_id].modifier_types.add(pm_type_id);
	conoutf("Assigned modifier type \"%s\" (id: %d) to emitter type \"%s\" (id: %d, len: %d)", pm_name.c_str(), pm_type_id, pe_name.c_str(), pe_type_id, particle_emitter_types[pe_type_id].modifier_types.length());
	return 0;
}

int create_particle_emitter_instance(std::string name, const vec &o, const vec &vel)
{
	int pe_type_id = get_particle_emitter_type(name);
	particle_emitter_instances.add();
	int pe_inst_id = particle_emitter_instances.length() - 1;
	particle_emitter_instances[pe_inst_id].type = pe_type_id;
	particle_emitter_instances[pe_inst_id].o = o;
	particle_emitter_instances[pe_inst_id].vel = vel;
	particle_emitter_instances[pe_inst_id].millistoprocess = 0;
	particle_emitter_instances[pe_inst_id].attributes.insert(particle_emitter_types[pe_type_id].attributes.begin(), particle_emitter_types[pe_type_id].attributes.end());

	particle_emitter_type pe_type = particle_emitter_types[pe_type_id];
	conoutf("Created emitter instance (id: %d) of type \"%s\" (id: %d)", pe_inst_id, name.c_str(), pe_type_id);
	loopv(pe_type.modifier_types)
	{
		int pm_inst_id = create_particle_modifier_instance(pe_type.modifier_types[i]);
		particle_emitter_instances[pe_inst_id].modifier_instances.add(pm_inst_id);
		conoutf("Added modifier instance (id: %d) to emitter instance (id: %d, len: %d)", pm_inst_id, pe_inst_id, particle_emitter_instances[pe_inst_id].modifier_instances.length());
	}
	return pe_inst_id;
}

ICOMMAND(add_particle_emitter_type, "ssi", (char *name, char *particle_type, int *mass, int *density, int *lifetime, int *rate, char *impl), intret(add_particle_emitter_type(name, particle_type, *mass, *density, *lifetime, *rate, impl)));
ICOMMAND(get_particle_emitter_type, "s", (char *name), intret(get_particle_emitter_type(name)));
ICOMMAND(particle_emitter_types_num, "", (), intret(particle_emitter_types.length()));
ICOMMAND(assign_modifier_to_emitter, "ss", (char *modifier_name, char *emitter_name), intret(assign_modifier_to_emitter(modifier_name, emitter_name)));
ICOMMAND(ls_particle_emitter_types, "", (),
{
	loopv(particle_emitter_types) {
		conoutf("%i | %s | %i | %i", i, particle_emitter_types[i].name.c_str(), particle_emitter_types[i].particle_type, particle_emitter_types[i].lifetime);
	}
});
