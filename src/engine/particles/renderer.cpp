#include "cube.h"
#include "particles.h"

int timer_renderer = 0;

// abstract definitions - makes everything dynamic
std::vector<particle_renderer_type*> particle_renderer_types;
std::map<std::string, particle_renderer_type*> particle_renderer_types_map;

// implementations - the concrete implementations
std::vector<particle_renderer_implementation*> particle_renderer_implementations;
std::map<std::string, particle_renderer_implementation*> particle_renderer_implementations_map;

// concrete instances refers to the abstract definitions
std::vector<particle_renderer_instance*> particle_renderer_instances;
std::map<std::string, particle_renderer_instance*> particle_renderer_instances_map;

void render_particles()
{
	int started = SDL_GetTicks();
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->pr_type->pr_impl->before(*pr_it);

		std::list<particle_instance*>::iterator p_it = (*pr_it)->particles.begin();
		while (p_it != (*pr_it)->particles.end())
		{
			if ((*p_it)->remaining > 0)
			{
				(*pr_it)->pr_type->pr_impl->render(*pr_it, *p_it);
				++p_it;
			} else {
				p_it = (*pr_it)->particles.erase(p_it);
			}
		}
		(*pr_it)->pr_type->pr_impl->after(*pr_it);
	}
	timer_renderer = SDL_GetTicks() - started;
}

particle_renderer_type* add_particle_renderer_type(std::string name, std::string shader, std::string impl)
{
	particle_renderer_type* pr_type = new particle_renderer_type;
	pr_type->name = name;
	pr_type->shader = shader;
	pr_type->pr_impl = particle_renderer_implementations_map[impl];
	particle_renderer_types.push_back(pr_type);
	particle_renderer_types_map[name] = pr_type;
	conoutf("Added particle renderer type \"%s\" (shader: %s) of implementation \"%s\"", name.c_str(), shader.c_str(), impl.c_str());
	return pr_type;
}

particle_renderer_instance* particle_renderer_type::create_instance(std::string name)
{
	particle_renderer_instance* pr_inst = new particle_renderer_instance;
	pr_inst->name = name;
	pr_inst->pr_type = this;
	pr_inst->attributes.insert(attributes.begin(), attributes.end());
	particle_renderer_instances.push_back(pr_inst);
	particle_renderer_instances_map[name] = pr_inst;
	return pr_inst;
}

particle_renderer_instance* create_particle_renderer_instance(std::string name, std::string type)
{
	return particle_renderer_types_map[type]->create_instance(name);
}

ICOMMAND(add_particle_renderer_type, "ss", (char *name, char *shader, char *impl), add_particle_renderer_type(name, shader, impl));
ICOMMAND(create_particle_renderer_instance, "ss", (char *name, char *type), create_particle_renderer_instance(name, type));

/*
ICOMMAND(particle_renderer_types_num, "", (), intret(particle_renderer_types.length()));
ICOMMAND(ls_particle_renderer_types, "", (),
{
	loopv(particle_renderer_types) {
		conoutf("%i | %s | %s", i, particle_renderer_types[i].name.c_str(), particle_renderer_types[i].shader.c_str());
	}
});
*/
