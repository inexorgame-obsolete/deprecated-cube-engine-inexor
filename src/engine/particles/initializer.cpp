#include "cube.h"
#include "particles.h"

VARP(initializers, 0, 1, 1);

particle_initializer_type* particle_system::add_particle_initializer_type(std::string name, std::string impl)
{
	if (!particle_initializer_types_map.count(name))
	{
		particle_initializer_type* pi_type = new particle_initializer_type;
		pi_type->name = name;
		pi_type->pi_impl = particle_initializer_implementations_map[impl];
		particle_initializer_types.push_back(pi_type);
		particle_initializer_types_map[name] = pi_type;
		conoutf("Added particle initializer type \"%s\" of implementation \"%s\"", name.c_str(), impl.c_str());
		count_particle_initializer_types++;
		return pi_type;
	} else {
		conoutf("Particle initializer type %s already exists!", name.c_str());
		return particle_initializer_types_map[name];
	}
}

particle_initializer_instance* particle_initializer_type::create_instance() {
	particle_initializer_instance* pi_inst = new particle_initializer_instance;
	pi_inst->pi_type = this;
	pi_inst->attributes.insert(attributes.begin(), attributes.end());

	ps.particle_initializer_instances.push_back(pi_inst);
	ps.count_particle_initializer_instances++;
	return pi_inst;
}

particle_initializer_instance* particle_system::create_particle_initializer_instance(std::string pi_type)
{
	if (particle_initializer_types_map.count(pi_type))
	{
		return particle_initializer_types_map[pi_type]->create_instance();
	} else {
		conoutf("Particle initializer type %s not found!", pi_type.c_str());
		return 0;
	}
}

void particle_system::remove_particle_initializer_type(std::string name)
{
	if (particle_initializer_types_map.count(name))
	{
		particle_initializer_types_map.erase(name);
		// TODO: remove from particle_initializer_types
		count_particle_initializer_types--;
	} else {
		conoutf("Particle initializer type %s not found!", name.c_str());
	}
}

void particle_system::remove_all_particle_initializer_types()
{
	particle_initializer_types_map.clear();
	particle_initializer_types.clear();
	count_particle_initializer_types = 0;
}

void create_particle_initializer_instance(std::string pi_type) {
	ps.create_particle_initializer_instance(pi_type);
}

