#include "cube.h"
#include "particles.h"

// concrete instances refers to the abstract definitions
vector<particle_instance> particle_instances;

// particle pools for performance reasons
vector<particle_instance> alive_pool[2];
vector<particle_instance> dead_pool[2];
int current_alive_pool = 0;
int current_dead_pool = 0;

void init_particles()
{
	reset_particle_system();
//	clear_particle_pools();
}

void clear_particle_pools()
{
	alive_pool[current_alive_pool].shrink(0);
}

void reset_particle_system()
{
}

int particlemillis = 0;

/**
 * Apply emitters, modifiers and renderers.
 */
void update_particle_system() {
	int millis = SDL_GetTicks();
    int elapsedtime = millis - particlemillis;

    switch_particles_buffer(elapsedtime);
    emit_particles(elapsedtime);
    modify_particles(elapsedtime);
    render_particles();

    particlemillis = millis;
}

/**
 * Use a doubled buffered pool for alive and dead particle instances.
 * Avoid sorting, because sorting is a performance killer.
 */
void switch_particles_buffer(int elapsedtime)
{
	int i = 0;
	while(i < alive_pool[current_alive_pool].length()) {
		if (alive_pool[current_alive_pool][i].remaining > 0)
		{
			alive_pool[current_alive_pool][i].elapsed += elapsedtime;
			alive_pool[current_alive_pool][i].remaining -= elapsedtime;
		} else {
			particle_instance pi = alive_pool[current_alive_pool].removeunordered(i);
			i--;
		}
		i++;
	}
}


COMMAND(init_particles, "");
COMMAND(clear_particle_pools, "");
COMMAND(reset_particle_system, "");
