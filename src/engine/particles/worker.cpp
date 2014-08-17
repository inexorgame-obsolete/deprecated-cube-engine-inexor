#include "engine.h"
#include "particles.h"

particle_state_worker::particle_state_worker()
{
	thread = NULL;
	running = false;
	stopped = true;
}

particle_state_worker::~particle_state_worker() { }

void particle_state_worker::start()
{
	if (stopped)
	{
		conoutf("starting worker thread");
		thread = SDL_CreateThread(work, this);
	}
}

void particle_state_worker::stop() {
	if (!stopped)
	{
		running = false;
		// SDL_KillThread(thread);
		conoutf("stopping worker thread");
	    int retValue;
		SDL_WaitThread(thread, &retValue);
	}
}

int particle_state_worker::work(void *data)
{
	particle_state_worker *w = (particle_state_worker *)data;
	int totalmillis = 0;
	try
	{
		w->running = true;
		w->stopped = false;
		conoutf("worker thread started");
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
	w->stopped = true;
	conoutf("worker thread stopped");
	return 0;
}
