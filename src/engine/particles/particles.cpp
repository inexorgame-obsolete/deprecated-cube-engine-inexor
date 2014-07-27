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
	clear_particle_pools();
}

void clear_particle_pools()
{
/*
	alive_pool[0].shrink(0);
	alive_pool[1].shrink(0);
	dead_pool[0].shrink(0);
	dead_pool[1].shrink(0);
*/
}

void reset_particle_system()
{
/*
	particle_types.shrink(0);
	particle_emitter_types.shrink(0);
	particle_renderer_types.shrink(0);
	particle_modifier_types.shrink(0);
	particle_instances.shrink(0);
	particle_emitter_instances.shrink(0);
	particle_renderer_instances.shrink(0);
	particle_modifier_instances.shrink(0);
*/
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
//    modify_particles(elapsedtime);
//    render_particles();

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
			conoutf("kill particle id: %d", i);
			conoutf("spb alive.ulen: %d alive.alen: %d", alive_pool[current_alive_pool].ulen, alive_pool[current_alive_pool].alen);
			conoutf("spb dead.ulen: %d dead.alen: %d", dead_pool[current_dead_pool].ulen, dead_pool[current_dead_pool].alen);
			particle_instance pi = alive_pool[current_alive_pool].removeunordered(i);
/*
			int ulen = dead_pool[current_dead_pool].ulen;
			int alen = dead_pool[current_dead_pool].alen;
	        if(ulen == alen)
	        {
	        	dead_pool[current_dead_pool].growbuf(ulen + 1);
				conoutf("growbuf %d", ulen + 1);
	        	ulen = dead_pool[current_dead_pool].ulen;
	        	alen = dead_pool[current_dead_pool].alen;
				conoutf("spb dead.ulen: %d dead.alen: %d", ulen, alen);
	        }
	        conoutf("spb ulen: %d", ulen);
	        dead_pool[current_dead_pool].ulen = ulen + 1;
	        conoutf("y");
	        dead_pool[current_dead_pool][ulen] = pi;
	        conoutf("z");
*/

			// dead_pool[current_dead_pool].add(pi);
			i--;
		}
		i++;
	}
	/*
	loopv(alive_pool[current_alive_pool])
	{
		conoutf("C1");
		// move particle instance to inactive alive/dead pool
		conoutf("C2");
//		conoutf("pool id: %d remaining: %d", i, pi.remaining);
		if (pi.remaining > 0)
		{
			pi.elapsed += elapsedtime;
			pi.remaining -= elapsedtime;
//			conoutf("stay alive! elapsed: %d remaining: %d", pi.elapsed, pi.remaining);
		} else {
			conoutf("D1");
//			conoutf("kill particle %d", i);
			alive_pool[current_alive_pool].removeunordered()
			dead_pool[next_dead_pool].add(pi);
			conoutf("D2");
		}
	}

//	conoutf("B");
	conoutf("P1");
	// move all dead particles instances to inactive dead pool
	int next_alive_pool = (current_alive_pool + 1) % 2;
	conoutf("P2");
	int next_dead_pool = (current_dead_pool + 1) % 2;
	conoutf("P3");
	dead_pool[next_dead_pool] = dead_pool[current_dead_pool];
	conoutf("P4");
	loopv(alive_pool[current_alive_pool])
	{
		conoutf("C1");
		// move particle instance to inactive alive/dead pool
		particle_instance pi = alive_pool[current_alive_pool][i];
		conoutf("C2");
//		conoutf("pool id: %d remaining: %d", i, pi.remaining);
		if (pi.remaining > 0)
		{
			pi.elapsed += elapsedtime;
			pi.remaining -= elapsedtime;
			conoutf("A1");
//			conoutf("stay alive! elapsed: %d remaining: %d", pi.elapsed, pi.remaining);
			// alive_pool[next_alive_pool].add(pi);
			conoutf("A2");
		} else {
			conoutf("D1");
//			conoutf("kill particle %d", i);
			dead_pool[next_dead_pool].add(pi);
			conoutf("D2");
		}
	}
	// switch pools
	conoutf("S1");
	// alive_pool[current_alive_pool].shrink(0);
	alive_pool[current_alive_pool].empty();
	conoutf("S2");
	// dead_pool[current_dead_pool].shrink(0);
	dead_pool[current_dead_pool].empty();
	conoutf("S3");
//	conoutf("switch pools %d -> %d ... %d -> %d", current_alive_pool, next_alive_pool, current_dead_pool, next_dead_pool);
	current_alive_pool = next_alive_pool;
	conoutf("S4");
	current_dead_pool = next_dead_pool;
	conoutf("S5");
*/
}


COMMAND(init_particles, "");
COMMAND(clear_particle_pools, "");
COMMAND(reset_particle_system, "");
