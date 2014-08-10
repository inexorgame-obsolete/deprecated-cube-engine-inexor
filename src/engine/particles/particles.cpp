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
}

particle_system::~particle_system()
{
}

void particle_system::init_particles()
{
	reset_particle_system();
	p_worker.start();
}

void particle_system::shutdown_particles()
{
	p_worker.stop();
}

void particle_system::clear_particle_pools()
{
	p_worker.stop();
	std::list<particle_instance*>::iterator i = alive_pool.begin();
	while (i != alive_pool.end())
	{
		(*i)->remaining = 0;
		dead_pool.push_front(*i);
		i = alive_pool.erase(i);
	}
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->particles.clear();
	}
	p_worker.start();
}

void particle_system::reset_particle_system()
{
	init_particle_renderer();
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
		// conoutf("remaining: %d", (*i)->remaining);
		if ((*i)->remaining > 0)
		{
			(*i)->elapsed += elapsedtime;
			(*i)->remaining -= elapsedtime;
			++i;
		} else {
			// dead_pool.push_front(*i);
			// int before = (int) alive_pool.size();
			i = alive_pool.erase(i);
			// conoutf("%d:%d", before, (int) alive_pool.size());
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
