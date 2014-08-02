#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
std::vector<particle_modifier_type*> particle_modifier_types;
std::map<std::string, particle_modifier_type*> particle_modifier_types_map;

// implementations - the concrete implementations
std::vector<particle_modifier_implementation*> particle_modifier_implementations;
std::map<std::string, particle_modifier_implementation*> particle_modifier_implementations_map;

// concrete instances refers to the abstract definitions
std::vector<particle_modifier_instance*> particle_modifier_instances;

void modify_particles(int elapsedtime)
{
	// TODO: special types of modifiers which are called before only
	for(std::list<particle_instance*>::iterator p_it = alive_pool.begin(); p_it != alive_pool.end(); ++p_it)
	{
		for(std::vector<particle_modifier_instance*>::iterator pm_it = (*p_it)->pe_inst->modifiers.begin(); pm_it != (*p_it)->pe_inst->modifiers.end(); ++pm_it)
		{
			(*pm_it)->pm_type->pm_impl->modify(*pm_it, *p_it, elapsedtime);
		}
	}
	// TODO: special types of modifiers which are called afterwards only
}

particle_modifier_type* add_particle_modifier_type(std::string name, std::string impl)
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
	particle_modifier_instances.push_back(pm_inst);
	return pm_inst;
}

void create_particle_modifier_instance(std::string pm_type, const vec &o) {
	particle_modifier_types_map[pm_type]->create_instance(o);
}

/*
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
*/

ICOMMAND(add_particle_modifier_type, "ss", (char *name, char *impl), add_particle_modifier_type(name, impl));
ICOMMAND(create_particle_modifier_instance, "siii", (char *name, int *ox, int *oy, int *oz), create_particle_modifier_instance(name, vec(*ox, *oy, *oz)));
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
