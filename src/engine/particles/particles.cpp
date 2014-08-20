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
	count_particle_types = 0;
	count_particle_emitter_types = 0;
	count_particle_renderer_types = 0;
	count_particle_modifier_types = 0;
	count_particle_emitter_implementations = 0;
	count_particle_renderer_implementations = 0;
	count_particle_modifier_implementations = 0;
	count_particles_instances = 0;
	count_particle_emitter_instances = 0;
	count_particle_renderer_instances = 0;
	count_particle_modifier_instances = 0;
	count_spring_instances = 0;
	count_alive_pool = 0;
	count_dead_pool = 0;
	spring_lock = false;
}

particle_system::~particle_system()
{
}

void particle_system::init_particles()
{
    /** MT **/
	p_worker.start();
    /** END MT **/
}

void particle_system::clear_particle_pools()
{
	std::list<particle_instance*>::iterator i = alive_pool.begin();
	while (i != alive_pool.end())
	{
		// (*i)->remaining = 0;
		// dead_pool.push_front(*i);
		i = alive_pool.erase(i);
		count_alive_pool--;
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

	count_particle_types = 0;
	count_particle_emitter_types = 0;
	count_particle_renderer_types = 0;
	count_particle_modifier_types = 0;
	count_particle_emitter_implementations = 0;
	count_particle_renderer_implementations = 0;
	count_particle_modifier_implementations = 0;
	count_particles_instances = 0;
	count_particle_emitter_instances = 0;
	count_particle_renderer_instances = 0;
	count_particle_modifier_instances = 0;
	count_spring_instances = 0;
	count_alive_pool = 0;
	count_dead_pool = 0;
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
        /** NON-MT **/
/*
        if(!game::ispaused()) {
            // int elapsedtime = millis - totalmillis;
        	ps.update_particle_pools(elapsedtime);
        	ps.emit_particles(elapsedtime);
        	ps.modify_particles(elapsedtime);
        }
    	ps.update_particle_pools(elapsedtime);
    	ps.emit_particles(elapsedtime);
    	ps.modify_particles(elapsedtime);
*/
        /** END NON-MT **/
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
			(*i)->last_elapsed += (*i)->elapsed;
			(*i)->elapsed += elapsedtime;
			(*i)->remaining -= elapsedtime;
			++i;
		} else {
			// (*i)->reset();
			dead_pool.push_front(*i);
			i = alive_pool.erase(i);
			count_dead_pool++;
			count_alive_pool--;
		}
	}
}

void particle_system::add_spring(spring_instance *spring_inst)
{
	spring_instances.push_back(spring_inst);
	count_spring_instances++;
}

void particle_system::add_emitter_implementation(particle_emitter_implementation *pe_impl)
{
	particle_emitter_implementations.push_back(pe_impl);
	count_particle_emitter_implementations++;
}

void particle_system::add_renderer_implementation(particle_renderer_implementation *pr_impl)
{
	particle_renderer_implementations.push_back(pr_impl);
	count_particle_renderer_implementations++;
}

void particle_system::add_modifier_implementation(particle_modifier_implementation *pm_impl)
{
	particle_modifier_implementations.push_back(pm_impl);
	count_particle_modifier_implementations++;
}

void particle_system::add_initializer_implementation(particle_initializer_implementation *pi_impl)
{
	particle_initializer_implementations.push_back(pi_impl);
	count_particle_initializer_implementations++;
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

particle_initializer_implementation::particle_initializer_implementation(const std::string& name) : particle_implementation_base(name) {
	ps.particle_initializer_implementations_map[name] = this;
}
particle_initializer_implementation::~particle_initializer_implementation() { }


// COMMANDN(init_particles, particle_system::init_particles(), "");
// ICOMMAND(clear_particle_pools, "");
// ICOMMAND(reset_particle_system, "");
