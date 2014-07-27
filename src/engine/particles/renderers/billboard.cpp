#include "cube.h"
#include "engine/particles/particles.h"

struct billboard_renderer : particle_renderer_implementation
{
	billboard_renderer()
    {
		strcpy(name, newstring("billboard_renderer"));
		particle_renderer_implementations.add(this);
    }

	void render(particle_instance p_inst) {
		conoutf("billboard_renderer:render(type: %d emitter: %d elapsed: %d remaining: %d)", p_inst.type, p_inst.emitter, p_inst.elapsed, p_inst.remaining);
		// conoutf("billboard_renderer:render(x: %2.1f y: %2.1f z: %2.1f)", p_inst.o.x, p_inst.o.y, p_inst.o.z);
	}

};

billboard_renderer *ps_renderer_billboard = new billboard_renderer();
