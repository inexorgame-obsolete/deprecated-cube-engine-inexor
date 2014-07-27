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
		particle_emitter_instance pe_inst = particle_emitter_instances[i];
		particle_emitter_type pe_type = particle_emitter_types[pe_inst.type];
		pe_type.impl->emit(pe_inst, i, elapsedtime);
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

int add_particle_emitter_type(const char *name, const char *particle_type, float mass, float density, int lifetime, int rate, const char *impl)
{
	particle_emitter_types.add();
	int pe_type_id = particle_emitter_types.length() - 1;
	// particle_emitter_type pe_type = particle_emitter_types[pe_type_id];
	copystring(particle_emitter_types[pe_type_id].name, name);
	particle_emitter_types[pe_type_id].particle_type = get_particle_type(particle_type);
	particle_emitter_types[pe_type_id].mass = mass;
	particle_emitter_types[pe_type_id].density = density;
	particle_emitter_types[pe_type_id].lifetime = lifetime;
	particle_emitter_types[pe_type_id].rate = rate;
	impl = newstring(impl);
	int impl_id = get_particle_emitter_implementation(impl);
	particle_emitter_types[pe_type_id].impl = particle_emitter_implementations[impl_id];

	conoutf("Added particle emitter type \"%s\" (id: %d mass: %2.2f density: %2.2f lifetime: %d rate: %d ms parttype: %s) of implementation \"%s\" (id: %d) [%d:%d:%d]", name, pe_type_id, mass, density, lifetime, rate, particle_type, impl, impl_id, particle_emitter_instances.length(), particle_emitter_types.length(), particle_emitter_implementations.length());
	return pe_type_id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_emitter_type(const char *name)
{
	int emitter_type = get_particle_emitter_type(name);
	if (emitter_type >= 0) particle_emitter_types.remove(emitter_type);
}

int get_particle_emitter_type(const char *name)
{
	loopv(particle_emitter_types)
	{
		conoutf("gpet %s == %s", particle_emitter_types[i].name, name);
		if (strcmp(particle_emitter_types[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

int get_particle_emitter_implementation(const char *name)
{
	loopv(particle_emitter_implementations)
	{
		if (strcmp(particle_emitter_implementations[i]->name, name) == 0) return i;
	}
	return -1;
}

int assign_modifier_to_emitter(const char *pe_name, const char *pm_name)
{
    int pe_type_id = get_particle_emitter_type(pe_name);
    int pm_type_id = get_particle_modifier_type(pm_name);
    conoutf("add_modifier_type_to_emitter_type: %s(%d) %s(%d)", pe_name, pe_type_id, pm_name, pm_type_id);
    particle_emitter_types[pe_type_id].modifier_types.add(pm_type_id);
	conoutf("Assigned modifier type \"%s\" (id: %d) to emitter type \"%s\" (id: %d)", pm_name, pm_type_id, pe_name, pe_type_id);
}

int create_particle_emitter_instance(const char *name, const vec &o)
{
	int pe_type_id = get_particle_emitter_type(name);
	particle_emitter_instances.add();
	int pe_inst_id = particle_emitter_instances.length() - 1;
	particle_emitter_instance pe_inst = particle_emitter_instances[pe_inst_id];
	pe_inst.type = pe_type_id;
	pe_inst.o = o;
	particle_emitter_type pe_type = particle_emitter_types[pe_type_id];
	loopv(pe_type.modifier_types)
	{
		int modifier_inst_id = create_particle_modifier_instance(pe_type.modifier_types[i]);
		pe_inst.modifier_instances.add(modifier_inst_id);
	}
	conoutf("Created emitter instance (id: %d) of type \"%s\" (id: %d)", pe_inst_id, name, pe_type_id);
}

ICOMMAND(add_particle_emitter_type, "ssi", (char *name, char *particle_type, int *mass, int *density, int *lifetime, int *rate, char *impl), intret(add_particle_emitter_type(name, particle_type, *mass, *density, *lifetime, *rate, impl)));
COMMAND(remove_particle_emitter_type, "s");
ICOMMAND(get_particle_emitter_type, "s", (char *name), intret(get_particle_emitter_type(name)));
ICOMMAND(particle_emitter_types_num, "", (), intret(particle_emitter_types.length()));
ICOMMAND(assign_modifier_to_emitter, "ss", (char *modifier_name, char *emitter_name), intret(assign_modifier_to_emitter(modifier_name, emitter_name)));
ICOMMAND(ls_particle_emitter_types, "", (),
{
	loopv(particle_emitter_types) {
		conoutf("%i | %s | %i | %i", i, particle_emitter_types[i].name, particle_emitter_types[i].particle_type, particle_emitter_types[i].lifetime);
	}
});
