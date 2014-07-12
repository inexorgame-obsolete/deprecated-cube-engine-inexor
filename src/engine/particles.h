#ifndef ENGINE_PARTICLES_H

#define ENGINE_PARTICLES_H

struct particle_type
{
	string name;
	int renderer_type;
};

struct particle_emitter_type
{
	string name;
	int particle_type;
	int lifetime;
};

struct particle_renderer_type
{
	string name;
	string shader;
};

struct particle_modifier_type
{
	string name;
};

struct particle_instance
{
	// non-mutable states

	// the particle type (the renderer is definied in the particle type definition)
	int type;

	// the origin emitter
	int emitter;

	// required states; mutable

	// particle position
	vec o;

	// particle velocity
    vec vel;

    // the remaining iterations
    int remaining;

    // optional states; mutable
    hashtable<const char *, float> attributes;
};

/**
 * Emits particles
 */
struct particle_emitter_instance
{
	int type;
};

/**
 * Different rendering of particles bound on a single particle.
 */
struct particle_renderer_instance
{
	int type;
};

/**
 * Particle modifiers are altering the state of a particle (for example the position).
 */
struct particle_modifier_instance
{
	int type;
	// >= 0: only apply on particles emitted by a specific emitter
	int emitter;
};

// abstract definitions - makes everything dynamic
extern vector<particle_type> particle_types;
extern vector<particle_emitter_type> particle_emitter_types;
extern vector<particle_renderer_type> particle_renderer_types;
extern vector<particle_modifier_type> particle_modifier_types;

// concrete instances refers to the abstract definitions
extern vector<particle_instance> particles_instances;
extern vector<particle_emitter_instance> particle_emitter_instances;
extern vector<particle_renderer_instance> particle_renderer_instances;
extern vector<particle_modifier_instance> particle_modifier_instances;

// particle pools for performance reasons, replace this with pointers
extern vector<particle_instance> alive_pool;
extern vector<particle_instance> dead_pool;

extern void init_particles();

extern void clear_particle_pools();

extern void reset_particle_system();

extern void apply_particle_emitters();

extern void apply_particle_modifiers();

extern void render_particles();

extern void next_particles_iteration();

extern particle_instance* emit_particle();

extern int add_particle_type(const char *name, const char *renderer);

extern void remove_particle_type(const char *name);

extern int get_particle_type(const char *name);

extern int add_particle_emitter_type(const char *name, const char *particle_type, int lifetime);

extern void remove_particle_emitter_type(const char *name);

extern int get_particle_emitter_type(const char *name);

extern int add_particle_renderer_type(const char *name, const char *shader);

extern void remove_particle_renderer_type(const char *name);

extern int get_particle_renderer_type(const char *name);

extern int add_particle_modifier_type(const char *name);

extern void remove_particle_modifier_type(const char *name);

extern int get_particle_modifier_type(const char *name);

// extern void set_particle_type(int particle_id);

// extern void set_particle_emitter(int particle_id, int emitter_id);

// extern void set_particle_attribute(int particle_id, char * key, float value);

#endif /* ENGINE_PARTICLES_H */
