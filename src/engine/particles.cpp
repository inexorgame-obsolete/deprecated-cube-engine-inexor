#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_type> particle_types;
vector<particle_emitter_type> particle_emitter_types;
vector<particle_renderer_type> particle_renderer_types;
vector<particle_modifier_type> particle_modifier_types;

// implementations - the concrete implementations
vector<particle_emitter_implementation *> particle_emitter_implementations;
vector<particle_renderer_implementation *> particle_renderer_implementations;
vector<particle_modifier_implementation *> particle_modifier_implementations;

// concrete instances refers to the abstract definitions
vector<particle_instance> particle_instances;
vector<particle_emitter_instance> particle_emitter_instances;
vector<particle_renderer_instance> particle_renderer_instances;
vector<particle_modifier_instance> particle_modifier_instances;

// particle pools for performance reasons
vector<particle_instance> pool;
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
	alive_pool[0].shrink(0);
	alive_pool[1].shrink(0);
	dead_pool[0].shrink(0);
	dead_pool[1].shrink(0);
}

void reset_particle_system()
{
	particle_types.shrink(0);
	particle_emitter_types.shrink(0);
	particle_renderer_types.shrink(0);
	particle_modifier_types.shrink(0);
	particle_instances.shrink(0);
	particle_emitter_instances.shrink(0);
	particle_renderer_instances.shrink(0);
	particle_modifier_instances.shrink(0);
}

int particlemillis = 0;

/**
 * Apply emitters, modifiers and renderers.
 * 5. wende modifier an auf alle lebenden (neuer lebend pool)
 * 6. wende emitter an
 * 6.1 hole partikel vom neuen tot pool (pop)
 * 6.2 füge neues partikel zu neuen leben pool hinzu (push)
 * 7. wende renderer an auf alle lebenden (neuer lebend pool)
 */
void apply_particles() {
	int millis = SDL_GetTicks();
    int elapsedtime = millis - particlemillis;

    next_particles_iteration(elapsedtime);
    apply_particle_emitters(elapsedtime);
    apply_particle_modifiers(elapsedtime);
    render_particles();

    particlemillis = millis;
}

/**
 * Use a doubled buffered pool for alive and dead particle instances.
 * Avoid sorting, because sorting is a performance killer.
 */
void next_particles_iteration(int elapsedtime)
{
	// move all dead particles instances to inactive dead pool
	dead_pool[(current_dead_pool + 1) % 2] = dead_pool[current_dead_pool];
	loopv(alive_pool[current_alive_pool])
	{
		// move particle instance to inactive alive/dead pool
		particle_instance pi = alive_pool[current_alive_pool][i];
		if (pi.remaining > 0)
		{
			pi.elapsed += elapsedtime;
			pi.remaining -= elapsedtime;
			alive_pool[(current_dead_pool + 1) % 2].add(pi);
		} else {
			dead_pool[(current_dead_pool + 1) % 2].add(pi);
		}
	}
	// switch pools
	current_alive_pool = (current_alive_pool + 1) % 2;
	current_dead_pool = (current_dead_pool + 1) % 2;
}

void apply_particle_modifiers(int elapsedtime)
{

}

// TODO: spawn X particles every Y milliseconds
// TODO: call actual emitter to initialize particles
void apply_particle_emitters(int elapsedtime)
{
	// conoutf("%i emitters", particle_emitter_instances.length());
	loopv(particle_emitter_instances)
	{
		particle_emitter_instance ei = particle_emitter_instances[i];
		particle_emitter_type et = particle_emitter_types[ei.type];
		// conoutf("emitter of type %s spans particle of type %i", et.name, et.particle_type);
		int particle_type = et.particle_type;
		int renderer_type = particle_types[particle_type].renderer_type;
		// get new particle, may increase the pool :-)
		particle_instance *pi = emit_particle();
		// set the origin emitter
		pi->emitter = i;
		// get the particle type, mass and density from the emitter type
		pi->type = et.particle_type;
		pi->mass = et.mass;
		pi->density = et.density;
		// set the elapsed and remaining iterations from the emitter type's lifetime
		pi->elapsed = 0;
		pi->remaining = et.lifetime;
		// add particle instance to the alive pool
		alive_pool[current_alive_pool].add(*pi);
	}
}

void render_particles()
{

}

/**
 * By emitting a particle we want to reuse dead particles in order to save
 * memory.
 */
particle_instance* emit_particle()
{
	if (dead_pool[current_dead_pool].length() > 0)
	{
		// reanimate a dead particle
		return &dead_pool[current_dead_pool].pop();
	} else {
		// dynamically create a new particle instance
		particle_instance *pi = new particle_instance;
		return pi;
	}
}

int add_particle_type(const char *name, const char *renderer)
{
	particle_types.add();
	int id = particle_types.length() - 1;
	strcpy(particle_types[id].name, newstring(name));
	particle_types[id].renderer_type = get_particle_renderer_type(renderer);
	return id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_type(const char *name)
{
	int particle_type = get_particle_type(name);
	if (particle_type >= 0) particle_types.remove(particle_type);
}

int get_particle_type(const char *name)
{
	loopv(particle_types)
	{
		if (strcmp(particle_types[i].name, name) == 0) return i;
	}
	return -1;
}

int add_particle_emitter_type(const char *name, const char *particle_type, int lifetime)
{
	particle_emitter_types.add();
	int id = particle_emitter_types.length() - 1;
	copystring(particle_emitter_types[id].name, name);
	particle_emitter_types[id].particle_type = get_particle_type(particle_type);
	particle_emitter_types[id].lifetime = lifetime;
	return id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_emitter_type(const char *name)
{
	int emitter_type = get_particle_emitter_type(name);
	if (emitter_type >= 0) particle_emitter_types.remove(emitter_type);
}

int get_particle_emitter_type(const char *name)
{
	loopv(particle_emitter_types)
	{
		if (strcmp(particle_emitter_types[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

int get_particle_emitter_implementation(const char *name)
{
	loopv(particle_emitter_implementations)
	{
		if (strcmp(particle_emitter_implementations[i]->name, name) == 0) return i;
	}
	return -1;
}

int add_particle_renderer_type(const char *name, const char *shader)
{
	particle_renderer_types.add();
	int id = particle_renderer_types.length() - 1;
	copystring(particle_renderer_types[id].name, name);
	copystring(particle_renderer_types[id].shader, shader);
	return id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_renderer_type(const char *name)
{
	int renderer_type = get_particle_renderer_type(name);
	if (renderer_type >= 0) particle_renderer_types.remove(renderer_type);
}

int get_particle_renderer_type(const char *name)
{
	conoutf("get prt | %s", name);
	loopv(particle_renderer_types)
	{
		conoutf("  | %s | %s | %i", particle_renderer_types[i].name, name, strcmp(particle_renderer_types[i].name, name));
		if (strcmp(particle_renderer_types[i].name, name) == 0) {
			conoutf("found prt | %s | %s", particle_renderer_types[i].name, name);
			return i;
		}
	}
	conoutf("prt not found");
	return -1;
}

int get_particle_renderer_implementation(const char *name)
{
	loopv(particle_renderer_implementations)
	{
		if (strcmp(particle_renderer_implementations[i]->name, name) == 0) return i;
	}
	return -1;
}

int add_particle_modifier_type(const char *name, const char *impl)
{
	particle_modifier_types.add();
	int type_id = particle_modifier_types.length() - 1;
	copystring(particle_modifier_types[type_id].name, name);
	impl = newstring(impl);
	int impl_id = get_particle_modifier_implementation(impl);
	particle_modifier_types[type_id].impl = particle_modifier_implementations[impl_id];

	conoutf("Added particle modifier type \"%s\" (id %d) of implementation \"%s\" (id %d)", name, type_id, impl, impl_id);
	return type_id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_modifier_type(const char *name)
{
	int modifier_type = get_particle_modifier_type(name);
	if (modifier_type >= 0) particle_modifier_types.remove(modifier_type);
}

int get_particle_modifier_type(const char *name)
{
	loopv(particle_modifier_types)
	{
		if (strcmp(particle_modifier_types[i].name, name) == 0) return i;
	}
	return -1;
}

int get_particle_modifier_implementation(const char *name)
{
	loopv(particle_modifier_implementations)
	{
		if (strcmp(particle_modifier_implementations[i]->name, name) == 0) return i;
	}
	return -1;
}

COMMAND(init_particles, "");
COMMAND(clear_particle_pools, "");
COMMAND(reset_particle_system, "");

ICOMMAND(add_particle_type, "ss", (char *name, char *renderer_type), intret(add_particle_type(name, renderer_type)));
ICOMMAND(add_particle_emitter_type, "ssi", (char *name, char *particle_type, int *lifetime), intret(add_particle_emitter_type(name, particle_type, *lifetime)));
ICOMMAND(add_particle_renderer_type, "ss", (char *name, char *shader), intret(add_particle_renderer_type(name, shader)));
ICOMMAND(add_particle_modifier_type, "ss", (char *name, char *impl), intret(add_particle_modifier_type(name, impl)));

COMMAND(remove_particle_type, "s");
COMMAND(remove_particle_emitter_type, "s");
COMMAND(remove_particle_renderer_type, "s");
COMMAND(remove_particle_modifier_type, "s");

ICOMMAND(get_particle_type, "s", (char *name), intret(get_particle_type(name)));
ICOMMAND(get_particle_emitter_type, "s", (char *name), intret(get_particle_emitter_type(name)));
ICOMMAND(get_particle_renderer_type, "s", (char *name), intret(get_particle_renderer_type(name)));
ICOMMAND(get_particle_modifier_type, "s", (char *name), intret(get_particle_modifier_type(name)));

ICOMMAND(particle_types_num, "", (), intret(particle_types.length()));
ICOMMAND(particle_emitter_types_num, "", (), intret(particle_emitter_types.length()));
ICOMMAND(particle_renderer_types_num, "", (), intret(particle_renderer_types.length()));
ICOMMAND(particle_modifier_types_num, "", (), intret(particle_modifier_types.length()));

ICOMMAND(ls_particle_types, "", (),
{
	loopv(particle_types) {
		conoutf("%i | %s | %i", i, particle_types[i].name, particle_types[i].renderer_type);
	}
});

ICOMMAND(ls_particle_emitter_types, "", (),
{
	loopv(particle_emitter_types) {
		conoutf("%i | %s | %i | %i", i, particle_emitter_types[i].name, particle_emitter_types[i].particle_type, particle_emitter_types[i].lifetime);
	}
});

ICOMMAND(ls_particle_renderer_types, "", (),
{
	loopv(particle_renderer_types) {
		conoutf("%i | %s | %s", i, particle_renderer_types[i].name, particle_renderer_types[i].shader);
	}
});

ICOMMAND(ls_particle_modifier_types, "", (),
{
	loopv(particle_modifier_types) {
		conoutf("%i | %s", i, particle_modifier_types[i].name);
	}
});

