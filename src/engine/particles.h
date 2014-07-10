#ifndef ENGINE_PARTICLES_H

#define ENGINE_PARTICLES_H

struct particle_type
{
	int id;
	string name;
	int render_type;
};

struct particle_emitter_type
{
	int id;
	string name;
	int particle_type;
	int renderer_type;
};

struct particle_renderer_type
{
	int id;
	string name;
};

struct particle_modifier_type
{
	int id;
	string name;
	// >= 0: only apply on particles emitted by a specific emitter
	int emitter;
};

struct particle
{
	// not mutable
	int id;
	int type;
	int emitter; // the origin emitter
	// renderer is definied in the particle type definition
	// required states; mutable
    vec o;
    int remaining;
    // optional states; mutable
    hashtable<const char *, float> attributes;
};

/**
 * Emits particles
 */
struct particle_emitter
{
	int id;
	int type;
};

/**
 * Different rendering of particles bound on a single particle.
 */
struct particle_renderer
{
	int id;
	int type;
};

/**
 * Particle modifiers are altering the state of a particle (for example the position).
 */
struct particle_modifier
{
	int id;
	int type;
};

// abstract definitions - makes everything dynamic
extern vector<particle_type *> particle_types;
extern vector<particle_emitter_type *> particle_emitter_types;
extern vector<particle_renderer_type *> particle_renderer_types;
extern vector<particle_modifier_type *> particle_modifier_types;

// concrete instances refers to the abstract definitions
extern vector<particle *> particles;
extern vector<particle_emitter *> particle_emitters;
extern vector<particle_renderer *> particle_renderers;
extern vector<particle_modifier *> particle_modifiers;

// particle pools for performance reasons
extern vector<particle *> alive_pool;
extern vector<particle *> dead_pool;

#endif /* ENGINE_PARTICLES_H */
