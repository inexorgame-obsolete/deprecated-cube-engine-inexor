#include "cube.h"
#include "engine.h"
#include "rendertarget.h"
#include "particles.h"

/*
// abstract definitions - makes everything dynamic
std::vector<particle_renderer_type*> particle_renderer_types;
std::map<std::string, particle_renderer_type*> particle_renderer_types_map;

// implementations - the concrete implementations
std::vector<particle_renderer_implementation*> particle_renderer_implementations;
std::map<std::string, particle_renderer_implementation*> particle_renderer_implementations_map;

// concrete instances refers to the abstract definitions
std::vector<particle_renderer_instance*> particle_renderer_instances;
std::map<std::string, particle_renderer_instance*> particle_renderer_instances_map;

// default particle shaders
Shader *particle_shader = NULL;
Shader *particle_shader_notexture = NULL;
*/

VARP(renderers, 0, 1, 1);

void particle_system::render_particles()
{
	if (renderers && p_worker.running) {
		try {
			int started = SDL_GetTicks();
			for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
			{
				(*pr_it)->type->impl->before(*pr_it);

				std::list<particle_instance*>::iterator p_it = (*pr_it)->instances.begin();
				while (p_it != (*pr_it)->instances.end())
				{
					if ((*p_it)->remaining > 0)
					{
						(*pr_it)->type->impl->render(*pr_it, *p_it);
						++p_it;
					} else {
						p_it = (*pr_it)->instances.erase(p_it);
					}
				}
				(*pr_it)->type->impl->after(*pr_it);
			}
			timer_renderer = SDL_GetTicks() - started;
		} catch (int e) {
			conoutf("renderer e: %d", e);
		}
		printOpenGLError();
	}
}

particle_renderer_type* particle_system::add_particle_renderer_type(std::string name, std::string texture, std::string shader, const vec4 &color, std::string impl)
{
	if (!particle_renderer_types_map.count(name))
	{
		particle_renderer_type* pr_type = new particle_renderer_type;
		pr_type->name = name;
		pr_type->texture = texture;
		pr_type->shader = shader;
		pr_type->color = color;
		pr_type->impl = particle_renderer_implementations_map[impl];
		particle_renderer_types.push_back(pr_type);
		particle_renderer_types_map[name] = pr_type;
		ps.count_particle_renderer_types++;
		conoutf("Added particle renderer type \"%s\" (shader: %s) of implementation \"%s\"", name.c_str(), shader.c_str(), impl.c_str());
		return pr_type;
	} else {
		conoutf("Particle renderer type %s already exists!", name.c_str());
		return particle_renderer_types_map[name];
	}
}

particle_renderer_instance* particle_renderer_type::create_instance(std::string name)
{
	particle_renderer_instance* pr_inst = new particle_renderer_instance;
	pr_inst->name = name;
	pr_inst->texture = texture;
	pr_inst->shader = shader;
	pr_inst->color = color;
	pr_inst->type = this;
	pr_inst->offset = vec(0.0f, 0.0f, 0.0f);
	pr_inst->attributes.insert(attributes.begin(), attributes.end());
	ps.particle_renderer_instances.push_back(pr_inst);
	ps.particle_renderer_instances_map[name] = pr_inst;
	ps.count_particle_renderer_instances++;
	conoutf("Created particle renderer instance of type \"%s\"", name.c_str());
	return pr_inst;
}

particle_renderer_instance* particle_system::create_particle_renderer_instance(std::string name, std::string pr_type)
{
	if (particle_renderer_types_map.count(pr_type))
	{
		return particle_renderer_types_map[pr_type]->create_instance(name);
	} else {
		conoutf("Particle renderer type %s not found!", pr_type.c_str());
		return noop_renderer_inst;
	}
}

void particle_system::remove_particle_renderer_type(std::string name)
{
	if (particle_renderer_types_map.count(name))
	{
		particle_renderer_types_map.erase(name);
		// TODO: iterate and remove from particle_renderer_types
		count_particle_renderer_types--;
	} else {
		conoutf("Particle renderer type %s not found!", name.c_str());
	}
}

void particle_system::remove_all_particle_renderer_types()
{
	particle_renderer_types_map.clear();
	particle_renderer_types.clear();
	particle_renderer_types.push_back(noop_renderer_type);
	particle_renderer_types_map["noop"] = noop_renderer_type;
	count_particle_renderer_types = 1;
}

void particle_system::remove_all_particle_renderer_instances()
{
	particle_renderer_instances_map.clear();
	particle_renderer_instances.clear();
	particle_renderer_instances.push_back(noop_renderer_inst);
	particle_renderer_instances_map["noop"] = noop_renderer_inst;
	count_particle_renderer_instances = 1;
}

void create_particle_renderer_instance(std::string name, std::string pr_type) {
	ps.create_particle_renderer_instance(name, pr_type);
}

// ICOMMAND(add_particle_renderer_type, "sssiiiis", (char *name, char *texture, char *shader, int *r, int *g, int *b, int *a, char *impl), add_particle_renderer_type(name, texture, shader, vec4(*r, *g, *b, *a), impl));
// ICOMMAND(create_particle_renderer_instance, "ss", (char *name, char *type), create_particle_renderer_instance(name, type));

/*
ICOMMAND(particle_renderer_types_num, "", (), intret(particle_renderer_types.length()));
ICOMMAND(ls_particle_renderer_types, "", (),
{
	loopv(particle_renderer_types) {
		conoutf("%i | %s | %s", i, particle_renderer_types[i].name.c_str(), particle_renderer_types[i].shader.c_str());
	}
});
*/
