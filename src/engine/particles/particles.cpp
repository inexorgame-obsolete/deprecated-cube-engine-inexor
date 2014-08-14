#include "engine.h"
#include "particles.h"

particle_system ps;

particle_system::particle_system()
{
	particle_frame = 1000.0f;
	particlemillis = 0;
	timer_emitter = 0;
	timer_modifier = 0;
	timer_renderer = 0;
	spring_lock = false;
}

particle_system::~particle_system()
{
}

void particle_system::init_particles()
{
	p_worker.start();
}

void particle_system::clear_particle_pools()
{
	std::list<particle_instance*>::iterator i = alive_pool.begin();
	while (i != alive_pool.end())
	{
		// (*i)->remaining = 0;
		// dead_pool.push_front(*i);
		i = alive_pool.erase(i);
	}
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->particles.clear();
	}
}

void particle_system::cleanup()
{
	for(std::vector<particle_emitter_instance*>::iterator it = particle_emitter_instances.begin(); it != particle_emitter_instances.end(); ++it)
		(*it)->enabled = false;
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->particles.clear();
	}
	particle_renderer_instances.clear();
	particle_renderer_instances_map.clear();
	particle_instances.clear();
	particle_modifier_instances.clear();
	particle_emitter_instances.clear();
	alive_pool.clear();
	dead_pool.clear();
	remove_all_particle_renderer_types();
	remove_all_particle_emitter_types();
	remove_all_particle_modifier_types();
	remove_all_particle_types();
}

/**
 * Apply renderers.
 */
void particle_system::update_particle_system()
{
	int millis = SDL_GetTicks();
    int elapsedtime = millis - particlemillis;
	try
	{
	    render_particles();
	} catch (int e) {
		conoutf("update_particle_system e: %d", e);
	}
    particlemillis = millis;
}

/**
 * Use pools for alive and dead particle instances. Avoid sorting,
 * because sorting is a performance killer. Instead we pick dead
 * particles from the list (efficiently remove elements in the
 * middle) and push it at the end of the dead pool (a vector).
 */
void particle_system::update_particle_pools(int elapsedtime)
{
	std::list<particle_instance*>::iterator i = alive_pool.begin();
	while (i != alive_pool.end())
	{
		if ((*i)->remaining > 0)
		{
			(*i)->elapsed += elapsedtime;
			(*i)->remaining -= elapsedtime;
			++i;
		} else {
			// dead_pool.push_front(*i);
			// int before = (int) alive_pool.size();
			i = alive_pool.erase(i);
		}
	}
}

particle_implementation_base::particle_implementation_base(const std::string& name) : name(name) { }
particle_implementation_base::~particle_implementation_base() { }

particle_emitter_implementation::particle_emitter_implementation(const std::string& name) : particle_implementation_base(name) {
	ps.particle_emitter_implementations_map[name] = this;
}
particle_emitter_implementation::~particle_emitter_implementation() { }

particle_renderer_implementation::particle_renderer_implementation(const std::string& name) : particle_implementation_base(name) {
	ps.particle_renderer_implementations_map[name] = this;
}
particle_renderer_implementation::~particle_renderer_implementation() { }

particle_modifier_implementation::particle_modifier_implementation(const std::string& name) : particle_implementation_base(name) {
	ps.particle_modifier_implementations_map[name] = this;
}
particle_modifier_implementation::~particle_modifier_implementation() { }

// COMMANDN(init_particles, particle_system::init_particles(), "");
// ICOMMAND(clear_particle_pools, "");
// ICOMMAND(reset_particle_system, "");
