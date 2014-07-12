#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_type *> particle_types;
vector<particle_emitter_type *> particle_emitter_types;
vector<particle_renderer_type *> particle_renderer_types;
vector<particle_modifier_type *> particle_modifier_types;

// concrete instances refers to the abstract definitions
vector<particle_instance *> particle_instances;
vector<particle_emitter_instance *> particle_emitter_instances;
vector<particle_renderer_instance *> particle_renderer_instances;
vector<particle_modifier_instance *> particle_modifier_instances;

// particle pools for performance reasons
vector<particle_instance *> alive_pool;
vector<particle_instance *> dead_pool;

void init_particles() {
	reset_particle_system();
	clear_particle_pools();
}

void clear_particle_pools() {
	alive_pool.shrink(0);
	dead_pool.shrink(0);
}

void reset_particle_system() {
	particle_types.shrink(0);
	particle_emitter_types.shrink(0);
	particle_renderer_types.shrink(0);
	particle_modifier_types.shrink(0);
	particle_instances.shrink(0);
	particle_emitter_instances.shrink(0);
	particle_renderer_instances.shrink(0);
	particle_modifier_instances.shrink(0);
}

void apply_particle_modifiers() {

}

void apply_particle_emitters() {
	loopv(particle_emitter_instances) {
		particle_emitter_instance *ei = particle_emitter_instances[i];
		particle_emitter_type *et = particle_emitter_types[ei->type];
		int particle_type = et->particle_type;
		int renderer_type = et->renderer_type;
		// get new particle, may increase the pool :-)
		particle_instance *pi = emit_particle();
		// set the origin emitter
		pi->emitter = i;
		// get the particle type from the emitter type
		pi->type = et->particle_type;
		// set the remaining iterations from the emitter type's lifetime
		pi->remaining = et->lifetime;
		// add particle instance to the alive pool
		alive_pool.add(pi);
	}
}

void render_particles() {

}

/**
 * Warning: removing a lot of vector entries just by use vector->remove(i)
 * would cause a performance issue (nested loops)! This is an optimized
 * remove function with only a single loop.
 */
void next_particles_iteration() {
	int n = 0;
	loopv(alive_pool) {
		if (n > 0 && i + n < alive_pool.length()) {
			alive_pool.buf[i] = alive_pool.buf[i + n];
		}
		if (alive_pool[i]->remaining > 1) {
			alive_pool[i]->remaining--;
		} else {
			// move from alive to dead pool
			particle_instance *pi = alive_pool[i];
			dead_pool.add(pi);
			n++;
			i--;
		}
	}
    alive_pool.ulen -= n;
}

/**
 * By emitting a particle we want to reuse dead particles in order to save
 * memory.
 */
particle_instance* emit_particle() {
	if (dead_pool.length() > 0) {
		// reanimate a dead particle
		return dead_pool.pop();
	} else {
		// dynamically create a new particle instance
		return new particle_instance;
	}
}

particle_type* add_particle_type(char *name, char *renderer) {
	name = newstring(name);
	particle_type *pt = particle_types.add();
	pt->name = name;
	pt->renderer_type = get_particle_renderer_type_id(renderer);
	return pt;
}

void remove_particle_type(char *name) {
	particle_types.remove(get_particle_type_id(name));
}

particle_type* get_particle_type(char *name) {
	loopv(particle_types) {
		if(strcmp(particle_types[i]->name, name)) {
			return particle_types[i];
		}
	}
}

int get_particle_type_id(char *name) {
	loopv(particle_types) {
		if(strcmp(particle_types[i]->name, name)) {
			return i;
		}
	}
	return -1;
}

particle_emitter_type* add_particle_emitter_type(char *name, char *particle_type, char *renderer_type, int lifetime) {
	name = newstring(name);
	particle_emitter_type *pet = particle_emitter_types.add();
	pet->name = name;
	pet->particle_type = get_particle_type_id(particle_type);
	pet->renderer_type = get_particle_renderer_type_id(renderer_type);
	pet->lifetime = lifetime;
	return pet;
}

void remove_particle_emitter_type(char *name) {
	particle_emitter_types.remove(get_particle_emitter_type_id(name));
}

particle_emitter_type* get_particle_emitter_type(char *name) {
	loopv(particle_emitter_types) {
		if(strcmp(particle_emitter_types[i]->name, name)) {
			return particle_emitter_types[i];
		}
	}
}

int get_particle_emitter_type_id(char *name) {
	loopv(particle_emitter_types) {
		if(strcmp(particle_emitter_types[i]->name, name)) {
			return i;
		}
	}
	return -1;
}

particle_renderer_type* add_particle_renderer_type(char *name, char *shader) {
	name = newstring(name);
	shader = newstring(shader);
	particle_renderer_type *prt = particle_renderer_types.add();
	prt->name = name;
	prt->shader = shader;
	return prt;
}

void remove_particle_renderer_type(char *name) {
	particle_renderer_types.remove(get_particle_renderer_type_id(name));
}

particle_renderer_type* get_particle_renderer_type(char *name) {
	loopv(particle_renderer_types) {
		if(strcmp(particle_renderer_types[i]->name, name)) {
			return particle_renderer_types[i];
		}
	}
}

int get_particle_renderer_type_id(char *name) {
	loopv(particle_renderer_types) {
		if(strcmp(particle_renderer_types[i]->name, name)) {
			return i;
		}
	}
	return -1;
}

particle_modifier_type* add_particle_modifier_type(char *name) {
	name = newstring(name);
	particle_modifier_type *pmt = particle_modifier_types.add();
	pmt->name = name;
	return pmt;
}

void remove_particle_modifier_type(char *name) {
	particle_modifier_types.remove(get_particle_modifier_type_id(name));
}

particle_modifier_type* get_particle_modifier_type(char *name) {
	loopv(particle_modifier_types) {
		if(strcmp(particle_modifier_types[i]->name, name)) {
			return particle_modifier_types[i];
		}
	}
}

int get_particle_modifier_type_id(char *name) {
	loopv(particle_modifier_types) {
		if(strcmp(particle_modifier_types[i]->name, name)) {
			return i;
		}
	}
	return -1;
}

// commands
COMMAND(init_particles, "");
COMMAND(clear_particle_pools, "");
COMMAND(reset_particle_system, "");

COMMAND(add_particle_type, "si");
COMMAND(add_particle_emitter_type, "s");
COMMAND(add_particle_renderer_type, "s");
COMMAND(add_particle_modifier_type, "s");
