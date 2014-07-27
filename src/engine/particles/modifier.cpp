#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_modifier_type> particle_modifier_types;

// implementations - the concrete implementations
vector<particle_modifier_implementation *> particle_modifier_implementations;

// concrete instances refers to the abstract definitions
vector<particle_modifier_instance> particle_modifier_instances;


void modify_particles(int elapsedtime)
{
    loopv(alive_pool[current_alive_pool])
    {
        particle_instance part_inst = alive_pool[current_alive_pool][i];
        particle_emitter_instance pe_inst = particle_emitter_instances[part_inst.emitter];
        // only apply modifiers assigned to the origin emitter
        loopvj(pe_inst.modifier_instances)
        {
        	particle_modifier_instance pm_inst = particle_modifier_instances[pe_inst.modifier_instances[j]];
        	particle_modifier_type pm_type = particle_modifier_types[pm_inst.type];
        	pm_type.impl->modify(pm_inst, part_inst, elapsedtime);
        }
    }
}

int add_particle_modifier_type(const char *name, const char *impl)
{
	particle_modifier_types.add();
	int pm_type_id = particle_modifier_types.length() - 1;
	copystring(particle_modifier_types[pm_type_id].name, name);
	impl = newstring(impl);
	int impl_id = get_particle_modifier_implementation(impl);
	particle_modifier_types[pm_type_id].impl = particle_modifier_implementations[impl_id];

	conoutf("Added particle modifier type \"%s\" (id: %d) of implementation \"%s\" (id: %d) [%d:%d:%d]", name, pm_type_id, impl, impl_id, particle_modifier_instances.length(), particle_modifier_types.length(), particle_modifier_implementations.length());
	return pm_type_id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_modifier_type(const char *name)
{
	int modifier_type = get_particle_modifier_type(name);
	if (modifier_type >= 0) particle_modifier_types.remove(modifier_type);
}

int get_particle_modifier_type(const char *name)
{
	loopv(particle_modifier_types)
	{
		if (strcmp(particle_modifier_types[i].name, name) == 0) return i;
	}
	return -1;
}

int get_particle_modifier_implementation(const char *name)
{
	loopv(particle_modifier_implementations)
	{
		if (strcmp(particle_modifier_implementations[i]->name, name) == 0) return i;
	}
	return -1;
}

int create_particle_modifier_instance(int pm_type_id)
{
	particle_modifier_instances.add();
	int pm_inst_id = particle_modifier_instances.length() - 1;
	particle_modifier_instances[pm_inst_id].type = pm_type_id;
	conoutf("Created modifier instance (id: %d) of type (id: %d)", pm_inst_id, pm_type_id);
}

ICOMMAND(add_particle_modifier_type, "ss", (char *name, char *impl), intret(add_particle_modifier_type(name, impl)));
COMMAND(remove_particle_modifier_type, "s");
ICOMMAND(get_particle_modifier_type, "s", (char *name), intret(get_particle_modifier_type(name)));
ICOMMAND(particle_modifier_types_num, "", (), intret(particle_modifier_types.length()));
ICOMMAND(ls_particle_modifier_types, "", (),
{
	loopv(particle_modifier_types) {
		conoutf("%i | %s", i, particle_modifier_types[i].name);
	}
});
