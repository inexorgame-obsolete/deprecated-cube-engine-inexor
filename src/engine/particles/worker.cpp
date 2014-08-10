#include "engine.h"
#include "particles.h"

particle_state_worker::particle_state_worker()
{
	thread = NULL;
	running = false;
}

particle_state_worker::~particle_state_worker() { }

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
	int totalmillis = 0;
	try
	{
		while(w->running)
		{
	        int millis = getclockmillis();
	        limitfps(millis, totalmillis);
	        if(!game::ispaused()) {
	            int elapsedtime = millis - totalmillis;
	        	ps.update_particle_pools(elapsedtime);
	        	ps.emit_particles(elapsedtime);
	        	ps.modify_particles(elapsedtime);
	        }
	        totalmillis = millis;
		}
	} catch (int e) {
		conoutf("worker e: %d", e);
	}
	return 0;
}
