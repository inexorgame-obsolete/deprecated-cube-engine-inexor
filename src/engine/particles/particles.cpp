#include "engine.h"
#include "particles.h"

particle_system ps;

particle_system::particle_system()
{
	particle_frame = 1000.0f;
	particlemillis = 0;
	max_particle_instances = 600;
	max_face_instances = 10000;
	timer_emitter = 0;
	timer_modifier = 0;
	timer_renderer = 0;
	timer_initializer = 0;
	timer_face = 0;
	count_particle_types = 0;
	count_particle_emitter_types = 0;
	count_particle_renderer_types = 0;
	count_particle_modifier_types = 0;
	count_particle_initializer_types = 0;
	count_face_types = 0;
	count_particle_emitter_implementations = 0;
	count_particle_renderer_implementations = 0;
	count_particle_modifier_implementations = 0;
	count_particle_initializer_implementations = 0;
	count_particle_instances = 0;
	count_particle_emitter_instances = 0;
	count_particle_renderer_instances = 0;
	count_particle_modifier_instances = 0;
	count_particle_initializer_instances = 0;
	count_face_instances = 0;
	count_spring_instances = 0;
	count_alive_pool = 0;
	count_dead_pool = 0;
	spring_lock = false;
	noop_emitter_impl = 0;
	noop_modifier_impl = 0;
	noop_renderer_impl = 0;
	noop_initializer_impl = 0;
	noop_particle_type = 0;
	noop_emitter_type = 0;
	noop_modifier_type = 0;
	noop_renderer_type = 0;
	noop_initializer_type = 0;
	noop_face_type = 0;
	noop_emitter_inst = 0;
	noop_modifier_inst = 0;
	noop_renderer_inst = 0;
	noop_initializer_inst = 0;
	init_spring_construction_rules();
	// init_face_construction_rules();
}

particle_system::~particle_system()
{
}

void particle_system::init_particles()
{
	init_defaults();
    /** MT **/
	p_worker.start();
    /** END MT **/
}

void particle_system::init_defaults()
{
	// noop_emitter = create_particle_emitter_instance("noop_emitter", vec(0.0f, 0.0f, 0.0f), vec(0.0f, 0.0f, 0.0f));
	noop_renderer_type = add_particle_renderer_type("noop", "", "", vec4(0.0f, 0.0f, 0.0f, 0.0f), "noop_renderer");
	noop_renderer_inst = noop_renderer_type->create_instance("noop");
	noop_particle_type = add_particle_type("noop", noop_renderer_inst);
	noop_emitter_type = add_particle_emitter_type("noop_emitter", noop_particle_type, 0.0f, 0.0f, 0, 1000000000, "noop_emitter");
	noop_emitter_inst = noop_emitter_type->create_instance(vec(0.0f, 0.0f, 0.0f), vec(0.0f, 0.0f, 0.0f));
	noop_modifier_type = add_particle_modifier_type("noop", "noop_modifier");
	noop_modifier_inst = noop_modifier_type->create_instance(); // vec(0.0f, 0.0f, 0.0f));
	noop_initializer_type = add_particle_initializer_type("noop", "noop_initializer");
	noop_initializer_inst = noop_initializer_type->create_instance();
	noop_face_type = add_face_type("noop", "no_texture");
	conoutf("finished init defaults");
}

void particle_system::clear_particle_pools()
{
	// Destroy alive particles.
	std::list<particle_instance*>::iterator i = alive_pool.begin();
	while (i != alive_pool.end())
	{
		// (*i)->remaining = 0;
		// dead_pool.push_front(*i);
		i = alive_pool.erase(i);
		count_alive_pool--;
	}
	count_alive_pool = 0;
	count_dead_pool = 0;
	count_particle_instances = 0;
	// Also clean up every particle instance reference in the renderers
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->instances.clear();
	}
}

void particle_system::clear_particle_instances()
{
	particle_instances.clear();
	count_particle_instances = 0;
	// TODO: also in the renderers!
}

void particle_system::cleanup()
{
	for(std::vector<particle_emitter_instance*>::iterator it = particle_emitter_instances.begin(); it != particle_emitter_instances.end(); ++it)
		(*it)->enabled = false;
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->instances.clear();
	}
	remove_all_particle_renderer_instances();
	clear_particle_instances();
	remove_all_particle_modifier_instances();
	remove_all_particle_emitter_instances();
	remove_all_particle_initializer_instances();
	remove_all_face_instances();
	clear_particle_pools();
	remove_all_particle_renderer_types();
	remove_all_particle_emitter_types();
	remove_all_particle_modifier_types();
	remove_all_particle_initializer_types();
	remove_all_particle_types();
	remove_all_face_types();

	// TODO: remove_all_spring_instances();
	count_spring_instances = 0;
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
	    // render_particles();
	    // render_faces();
	    // glEnable(GL_DEPTH_TEST);
//	    if (editmode) render_overlay();
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
			dead_pool.push_front(*i);
			i = alive_pool.erase(i);
			count_dead_pool++;
			count_alive_pool--;
		}
	}
}

void particle_system::add_emitter_implementation(particle_emitter_implementation *pe_impl)
{
	particle_emitter_implementations.push_back(pe_impl);
	count_particle_emitter_implementations++;
	conoutf("Added particle emitter implementation \"%s\"", pe_impl->name.c_str());
}

void particle_system::add_renderer_implementation(particle_renderer_implementation *pr_impl)
{
	particle_renderer_implementations.push_back(pr_impl);
	count_particle_renderer_implementations++;
	conoutf("Added particle renderer implementation \"%s\"", pr_impl->name.c_str());
}

void particle_system::add_modifier_implementation(particle_modifier_implementation *pm_impl)
{
	particle_modifier_implementations.push_back(pm_impl);
	count_particle_modifier_implementations++;
	conoutf("Added particle modifier implementation \"%s\"", pm_impl->name.c_str());
}

void particle_system::add_initializer_implementation(particle_initializer_implementation *pi_impl)
{
	particle_initializer_implementations.push_back(pi_impl);
	count_particle_initializer_implementations++;
	conoutf("Added particle initializer implementation \"%s\"", pi_impl->name.c_str());
}

particle_emitter_implementation::particle_emitter_implementation(const std::string& name) : entity_implementation_base<particle_emitter_instance>(name) {
	ps.particle_emitter_implementations_map[name] = this;
}
particle_emitter_implementation::~particle_emitter_implementation() { }

particle_renderer_implementation::particle_renderer_implementation(const std::string& name) : entity_implementation_base<particle_renderer_instance>(name) {
	ps.particle_renderer_implementations_map[name] = this;
}
particle_renderer_implementation::~particle_renderer_implementation() { }

particle_modifier_implementation::particle_modifier_implementation(const std::string& name) : entity_implementation_base<particle_modifier_instance>(name) {
	ps.particle_modifier_implementations_map[name] = this;
}
particle_modifier_implementation::~particle_modifier_implementation() { }

particle_initializer_implementation::particle_initializer_implementation(const std::string& name) : entity_implementation_base<particle_initializer_instance>(name) {
	ps.particle_initializer_implementations_map[name] = this;
}
particle_initializer_implementation::~particle_initializer_implementation() { }


// COMMANDN(init_particles, particle_system::init_particles(), "");
// ICOMMAND(clear_particle_pools, "");
// ICOMMAND(reset_particle_system, "");

int printOglError(std::string file, int line)
{

    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        conoutf("glError in file %s @ line %d: %s\n", file.c_str(), line, gluErrorString(glErr));
        retCode = 1;
    }
    return retCode;
}

