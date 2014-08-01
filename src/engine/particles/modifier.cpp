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
//	conoutf("modify %d", elapsedtime);
	loopv(alive_pool[current_alive_pool])
    {
    	// particle_instance p_inst = ;
        // particle_emitter_instance pe_inst = ;
    	// conoutf("modify p[%d] e[%d] eimods[%d]", i, p_inst.emitter, pe_inst.modifier_instances.length());
        // only apply modifiers assigned to the origin emitter
        loopvj(particle_emitter_instances[alive_pool[current_alive_pool][i].emitter].modifier_instances)
        {
        	// particle_modifier_instance pm_inst = particle_modifier_instances[particle_emitter_instances[alive_pool[current_alive_pool][i].emitter].modifier_instances[j]];
        	// particle_modifier_type pm_type = particle_modifier_types[particle_modifier_instances[particle_emitter_instances[alive_pool[current_alive_pool][i].emitter].modifier_instances[j]].type];
        	// conoutf("modify %d %s", pm_inst.type, pm_type.name);
        	particle_modifier_types[particle_modifier_instances[particle_emitter_instances[alive_pool[current_alive_pool][i].emitter].modifier_instances[j]].type].impl->modify(&particle_modifier_instances[particle_emitter_instances[alive_pool[current_alive_pool][i].emitter].modifier_instances[j]], &alive_pool[current_alive_pool][i], elapsedtime);
        }
    }
}

int add_particle_modifier_type(std::string name, const vec &o, const vec &vel, std::string impl)
{
	particle_modifier_types.add();
	int pm_type_id = particle_modifier_types.length() - 1;
	particle_modifier_types[pm_type_id].name = name;
	int impl_id = get_particle_modifier_implementation(impl);
	particle_modifier_types[pm_type_id].impl = particle_modifier_implementations[impl_id];
	particle_modifier_types[pm_type_id].o.x = o.x;
	particle_modifier_types[pm_type_id].o.y = o.y;
	particle_modifier_types[pm_type_id].o.z = o.z;
	particle_modifier_types[pm_type_id].vel.x = vel.x;
	particle_modifier_types[pm_type_id].vel.y = vel.y;
	particle_modifier_types[pm_type_id].vel.z = vel.z;

	conoutf("Added particle modifier type \"%s\" (id: %d) of implementation \"%s\" (id: %d) [%d:%d:%d]", name.c_str(), pm_type_id, impl.c_str(), impl_id, particle_modifier_instances.length(), particle_modifier_types.length(), particle_modifier_implementations.length());
	return pm_type_id;
}

int get_particle_modifier_type(std::string name)
{
	loopv(particle_modifier_types)
	{
		if (particle_modifier_types[i].name.compare(name) == 0) return i;
	}
	return -1;
}

int get_particle_modifier_implementation(std::string name)
{
	loopv(particle_modifier_implementations)
	{
		if (particle_modifier_implementations[i]->name.compare(name) == 0) return i;
	}
	return -1;
}

int create_particle_modifier_instance(int pm_type_id)
{
	particle_modifier_instances.add();
	int pm_inst_id = particle_modifier_instances.length() - 1;
	particle_modifier_instances[pm_inst_id].type = pm_type_id;
	particle_modifier_instances[pm_inst_id].o.x = particle_modifier_types[pm_type_id].o.x;
	particle_modifier_instances[pm_inst_id].o.y = particle_modifier_types[pm_type_id].o.y;
	particle_modifier_instances[pm_inst_id].o.z = particle_modifier_types[pm_type_id].o.z;
	particle_modifier_instances[pm_inst_id].vel.x = particle_modifier_types[pm_type_id].vel.x;
	particle_modifier_instances[pm_inst_id].vel.y = particle_modifier_types[pm_type_id].vel.y;
	particle_modifier_instances[pm_inst_id].vel.z = particle_modifier_types[pm_type_id].vel.z;
	particle_modifier_instances[pm_inst_id].attributes.insert(particle_modifier_types[pm_type_id].attributes.begin(), particle_modifier_types[pm_type_id].attributes.end());

	conoutf("Created modifier instance (id: %d) of type (id: %d)", pm_inst_id, pm_type_id);
	return pm_inst_id;
}

ICOMMAND(add_particle_modifier_type, "siiiiiis", (char *name, int *ox, int *oy, int *oz, int *vx, int *vy, int *vz, char *impl), intret(add_particle_modifier_type(name, vec(*ox, *oy, *oz), vec(*vx, *vy, *vz), impl)));
ICOMMAND(get_particle_modifier_type, "s", (char *name), intret(get_particle_modifier_type(name)));
ICOMMAND(particle_modifier_types_num, "", (), intret(particle_modifier_types.length()));
ICOMMAND(ls_particle_modifier_types, "", (),
{
	loopv(particle_modifier_types) {
		conoutf("%i | %s", i, particle_modifier_types[i].name.c_str());
	}
});
