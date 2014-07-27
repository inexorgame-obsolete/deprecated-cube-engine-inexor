#ifndef ENGINE_PARTICLES_H

#define ENGINE_PARTICLES_H

/**
 * A particle instance.
 */
struct particle_instance
{
	/*** Non-mutable states ***/

	/**
	 * Reference to the id of the particle type. The particle renderer
	 * belonging to this particle instance is defined in the particle
	 * type definition.
	 */
	int type;

	/**
	 * Reference to the id of the origin particle emitter. Therefore
	 * we can restore the start conditions of this particle instance.
	 */
	int emitter;

	/*** Required states; mutable ***/

	/**
	 * The current position of the particle instance.
	 */
	vec o;

	/**
	 * The current velocity of the particle instance.
	 */
    vec vel;

    /**
     * The remaining iterations of the particle instance. There might be
     * particle modifiers that change the remaining lifetime, for example
     * particle culling would set the remaining iterations to zero.
     */
    int remaining;

    /**
     * The elapsed iterations since birth. This attribute gets constantly
     * increased and should not be modified. It also might differ to
     * calculating (lifetime - remaining iterations) if the remaining
     * iterations attribute was modified. If you need a constant change
     * over time, you should use this!
     */
    int elapsed;

    /**
     * Every particle instance has a mass. Needed for modifiers which are
     * applying physical transformations like gravity.
     */
    float mass;

    /**
     * The density (or volume) of the particle. Needed for volumetric
     * rendering (for example metaballs or cloth).
     */
    float density;

    /*** Optional states; mutable ***/

    /**
     * An unlimited number of additional attributes. These might not as
     * performant as the attributes above because of the additional
     * hashtable lookup. But it allows maximum flexibility for emitters,
     * modifiers and renderers.
     */
    hashtable<const char *, float> attributes;

};

/**
 * A particle emitter instance is an instance of a particle emitter
 * type.
 */
struct particle_emitter_instance
{
	/**
	 * The emitter type id.
	 */
	int type;

	/**
	 * The current position of the particle emitter instance.
	 */
	vec o;

	/**
	 * The modifier instances.
	 */
	vector<int> modifier_instances;
};

/**
 * A particle renderer instance.
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
};

/**
 * Interface for a particle emitter implementation.
 *
 * Particle emitters should register themselves in their constructor
 * using add_particle_emitter_type()
 */
struct particle_emitter_implementation
{

	/**
	 * The name of the particle emitter implementation.
	 */
	string name;

	/**
	 * Emits new particle(s).
	 */
	virtual void emit(particle_emitter_instance pe_inst, int pe_inst_id, int elapsedtime) = 0;

};

/**
 * Interface for a particle renderer implementation.
 *
 * Particle renderers should register themselves in their constructor
 * using add_particle_renderer_type()
 */
struct particle_renderer_implementation
{

	/**
	 * The name of the particle renderer implementation.
	 */
	string name;

	/**
	 * Renders particles.
	 */
	virtual void render(particle_instance p_inst) = 0;

};

/**
 * Interface for a particle modifier implementation.
 *
 * Particle modifiers should register themselves in their constructor
 * using add_particle_modifier_type()
 */
struct particle_modifier_implementation
{

	/**
	 * The name of the particle modifier implementation.
	 */
	string name;

	/**
	 * Modifies particle(s).
	 */
	virtual void modify(particle_modifier_instance pmi, particle_instance pi, int elapsedtime) = 0;

};

/**
 * A particle type.
 */
struct particle_type
{
	/**
	 * The name of the particle type.
	 */
	string name;

	/**
	 * The id reference to the particle renderer type.
	 */
	int renderer_type;
};

/**
 * A particle emitter type. Notice that the actual implementation of
 * an particle emitter type needs to be bind using a function pointer.
 */
struct particle_emitter_type
{

	/**
	 * The name of the particle emitter type.
	 */
	string name;

	/**
	 * The particle type of an emitted particle instance.
	 */
	int particle_type;

	/**
	 * The start mass of an emitted particle instance.
	 */
	float mass;

	/**
	 * The start density of an emitted particle instance.
	 */
	float density;

	/**
	 * The lifetime of an emitted particle instance.
	 */
	int lifetime;

	/**
	 * Emit particles every <rate> milliseconds.
	 */
	int rate;

	/**
	 * The implementation.
	 */
	particle_emitter_implementation *impl;

	/**
	 * The modifier types to apply on particles spawned by an emitter of this type.
	 */
	vector<int> modifier_types;

};

/**
 * A particle renderer type.
 */
struct particle_renderer_type
{
	/**
	 * The name of the particle renderer type.
	 */
	string name;

	/**
	 * The shader to use.
	 */
	string shader;

	/**
	 * The implementation.
	 */
	particle_renderer_implementation *impl;
};

/**
 * A particle modifier type.
 */
struct particle_modifier_type
{
	/**
	 * The name of the particle modifier type.
	 */
	string name;

	/**
	 * The implementation.
	 */
	particle_modifier_implementation *impl;
};

// abstract definitions - makes everything dynamic
extern vector<particle_type> particle_types;
extern vector<particle_emitter_type> particle_emitter_types;
extern vector<particle_renderer_type> particle_renderer_types;
extern vector<particle_modifier_type> particle_modifier_types;

// implementations - the concrete implementations
extern vector<particle_emitter_implementation *> particle_emitter_implementations;
extern vector<particle_renderer_implementation *> particle_renderer_implementations;
extern vector<particle_modifier_implementation *> particle_modifier_implementations;

// concrete instances refers to the abstract definitions
extern vector<particle_instance> particle_instances;
extern vector<particle_emitter_instance> particle_emitter_instances;
extern vector<particle_renderer_instance> particle_renderer_instances;
extern vector<particle_modifier_instance> particle_modifier_instances;

// particle pools for performance reasons, replace this with pointers
extern vector<particle_instance> alive_pool[2];
extern vector<particle_instance> dead_pool[2];
extern int current_alive_pool;
extern int current_dead_pool;

extern void init_particles();
extern void clear_particle_pools();
extern void reset_particle_system();

extern void update_particle_system();
extern void switch_particles_buffer(int elapsedtime);

extern void emit_particles(int elapsedtime);
extern void modify_particles(int elapsedtime);
extern void render_particles();
extern particle_instance* emit_particle();

extern int add_particle_type(const char *name, const char *renderer);
extern void remove_particle_type(const char *name);
extern int get_particle_type(const char *name);

extern int add_particle_emitter_type(const char *name, const char *particle_type, float mass, float density, int lifetime, int rate, const char *impl);
extern void remove_particle_emitter_type(const char *name);
extern int get_particle_emitter_type(const char *name);
extern int get_particle_emitter_implementation(const char *name);
extern int assign_modifier_to_emitter(const char *emitter_name, const char *modifier_name);
extern int create_particle_emitter_instance(const char *name, const vec &o);

extern int add_particle_renderer_type(const char *name, const char *shader, const char *impl);
extern void remove_particle_renderer_type(const char *name);
extern int get_particle_renderer_type(const char *name);
extern int get_particle_renderer_implementation(const char *name);

extern int add_particle_modifier_type(const char *name, const char *impl);
extern void remove_particle_modifier_type(const char *name);
extern int get_particle_modifier_type(const char *name);
extern int get_particle_modifier_implementation(const char *name);
extern int create_particle_modifier_instance(int type);

// extern void set_particle_attribute(int particle_id, char * key, float value);

#endif /* ENGINE_PARTICLES_H */
