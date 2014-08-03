#include "cube.h"
#include "particles.h"

// concrete instances refers to the abstract definitions
std::vector<particle_instance*> particle_instances;

// particle pools for performance reasons
std::list<particle_instance*> alive_pool;
std::list<particle_instance*> dead_pool;

struct particle_state_worker
{
	SDL_Thread *thread;
	bool running;

	particle_state_worker()
	{
		thread = NULL;
		running = false;
	}

	void start();
	void stop();
	static int work(void *data);

};

void particle_state_worker::start()
{
	running = true;
	thread = SDL_CreateThread(work, this);
}

void particle_state_worker::stop() {
	running = false;
	SDL_KillThread(thread);
}

int particle_state_worker::work(void *data)
{
	particle_state_worker *w = (particle_state_worker *)data;
	int last_millis = 0;
	while(w->running)
	{
		int current_millis = SDL_GetTicks();
	    int elapsedtime = current_millis - last_millis;
	    update_particle_pools(elapsedtime);
	    emit_particles(elapsedtime);
	    modify_particles(elapsedtime);
	    last_millis = current_millis;
	}
	return 0;
}

particle_state_worker p_worker;

void init_particles()
{
	reset_particle_system();
	p_worker.start();
}

void shutdown_particles()
{
	p_worker.stop();
}

void clear_particle_pools()
{
	p_worker.stop();
	alive_pool.clear();
	dead_pool.clear();
	for(std::vector<particle_renderer_instance*>::iterator pr_it = particle_renderer_instances.begin(); pr_it != particle_renderer_instances.end(); ++pr_it)
	{
		(*pr_it)->particles.clear();
	}
	p_worker.start();
}

void reset_particle_system()
{
}

int particlemillis = 0;


/**
 * Apply emitters, modifiers and renderers.
 */
void update_particle_system()
{
	int millis = SDL_GetTicks();
    int elapsedtime = millis - particlemillis;

    // std::thread t1(modify_particles, elapsedtime);

    // update_particle_pools(elapsedtime);
    // emit_particles(elapsedtime);
    // modify_particles(elapsedtime);
    render_particles();

    particlemillis = millis;
}

/**
 * Use pools for alive and dead particle instances. Avoid sorting,
 * because sorting is a performance killer. Instead we pick dead
 * particles from the list (efficiently remove elements in the
 * middle) and push it at the end of the dead pool (a vector).
 */
void update_particle_pools(int elapsedtime)
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
			dead_pool.push_back(*i);
			i = alive_pool.erase(i);
		}
	}
}


COMMAND(init_particles, "");
COMMAND(clear_particle_pools, "");
COMMAND(reset_particle_system, "");
