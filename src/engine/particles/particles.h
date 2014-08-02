#ifndef ENGINE_PARTICLES_H

#define ENGINE_PARTICLES_H

#include <string>
#include <map>
#include <vector>
#include <list>

/**
 * Particle frame in milliseconds.
 */
static float particle_frame = 1000.0f;

struct particle_type;
struct particle_emitter_type;
struct particle_renderer_type;
struct particle_modifier_type;

struct particle_instance;
struct particle_emitter_instance;
struct particle_renderer_instance;
struct particle_modifier_instance;

struct particle_emitter_implementation;
struct particle_renderer_implementation;
struct particle_modifier_implementation;

extern std::map<std::string, particle_emitter_implementation*> particle_emitter_implementations_map;
extern std::map<std::string, particle_renderer_implementation*> particle_renderer_implementations_map;
extern std::map<std::string, particle_modifier_implementation*> particle_modifier_implementations_map;

/**
 * A particle emitter instance is an instance of a particle emitter
 * type.
 */
struct particle_emitter_instance
{

	/**
	 * The emitter type.
	 */
	particle_emitter_type *pe_type;

	/**
	 * The particle type of an emitted particle instance.
	 */
	particle_type *p_type;

	/**
	 * The current position of the particle emitter instance.
	 */
	vec o;

	/**
	 * The velocity.
	 */
	vec vel;

	/**
	 * If true, particles will be emitted.
	 */
	bool enabled;

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
	 * Remaining millis to process.
	 */
	int millistoprocess;

	/**
	 * The modifiers to apply on particles spawned by this emitter.
	 */
	std::vector<particle_modifier_instance*> modifiers;

	/**
	 * Extra attributes per emitter instance.
	 */
	std::map<std::string, float> attributes;

	/**
	 * Adds a modifier instance
	 */
	void add_modifier(particle_modifier_instance* pm_inst);

};

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
	particle_type *p_type;

	/**
	 * Reference to the origin particle emitter. Therefore we can
	 * restore the start conditions of this particle instance.
	 */
	particle_emitter_instance *pe_inst;

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
	std::map<std::string, float> attributes;

};

/**
 * A particle renderer instance.
 * Different rendering of particles bound on a single particle.
 */
struct particle_renderer_instance
{
	/**
	 * The name of the renderer instance.
	 */
	std::string name;

	/**
	 * The particle renderer type.
	 */
	particle_renderer_type *pr_type;

	/**
	 * Extra attributes per renderer instance.
	 */
	std::map<std::string, float> attributes;

	/**
	 * The particle instances to render.
	 */
	std::list<particle_instance*> particles;

};

/**
 * Particle modifiers are altering the state of a particle (for example the position).
 */
struct particle_modifier_instance
{

	/**
	 * The modifier type.
	 */
	particle_modifier_type *pm_type;

	/**
	 * The current position of the particle modifier instance.
	 */
	vec o;

	/**
	 * Extra attributes per modifier instance.
	 */
	std::map<std::string, float> attributes;

};

struct particle_implementation_base {

	/**
	 * The name of the implementation.
	 */
	const std::string name;

	particle_implementation_base(const std::string& name) : name(name) { }
	~particle_implementation_base() {}

};

/**
 * Interface for a particle emitter implementation.
 *
 * Particle emitters should register themselves in their constructor
 * using add_particle_emitter_type()
 */
struct particle_emitter_implementation : public particle_implementation_base
{

	particle_emitter_implementation(const std::string& name) : particle_implementation_base(name) {
		particle_emitter_implementations_map[name] = this;
	}
	~particle_emitter_implementation() { }

	/**
	 * Emits new particle(s).
	 */
	virtual void emit(particle_emitter_instance *pe_inst, int elapsedtime) = 0;

};

/**
 * Interface for a particle renderer implementation.
 *
 * Particle renderers should register themselves in their constructor
 * using add_particle_renderer_type()
 */
struct particle_renderer_implementation : public particle_implementation_base
{

	particle_renderer_implementation(const std::string& name) : particle_implementation_base(name) {
		particle_renderer_implementations_map[name] = this;
	}
	~particle_renderer_implementation() { };

	/**
	 * Called before rendering particles.
	 */
	virtual void before(particle_renderer_instance* pr_inst) = 0;

	/**
	 * Renders particles.
	 */
	virtual void render(particle_renderer_instance* pr_inst, particle_instance *p_inst) = 0;

	/**
	 * Called after rendering particles.
	 */
	virtual void after(particle_renderer_instance* pr_inst) = 0;

};

/**
 * Interface for a particle modifier implementation.
 *
 * Particle modifiers should register themselves in their constructor
 * using add_particle_modifier_type()
 */
struct particle_modifier_implementation : public particle_implementation_base
{

	particle_modifier_implementation(const std::string& name) : particle_implementation_base(name) {
		particle_modifier_implementations_map[name] = this;
	}
	~particle_modifier_implementation() { };

	/**
	 * Modifies particle(s).
	 */
	virtual void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) = 0;

};

/**
 * A particle type.
 */
struct particle_type
{
	/**
	 * The name of the particle type.
	 */
	std::string name;

	/**
	 * The reference to the particle renderer instance.
	 */
	particle_renderer_instance *pr_inst;

	/**
	 * Extra particle attributes.
	 */
	std::map<std::string, float> attributes;
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
	std::string name;

	/**
	 * The particle type of an emitted particle instance.
	 */
	particle_type *p_type;

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
	particle_emitter_implementation *pe_impl;

	/**
	 * Extra particle emitter attributes.
	 */
	std::map<std::string, float> attributes;

	/**
	 * The modifiers to apply on particles spawned by emitters of this type.
	 */
	std::vector<particle_modifier_instance*> modifiers;

	/**
	 * Creates an particle emitter instance of this type.
	 */
	particle_emitter_instance* create_instance(const vec &o, const vec &vel);

};

/**
 * A particle renderer type.
 */
struct particle_renderer_type
{
	/**
	 * The name of the particle renderer type.
	 */
	std::string name;

	/**
	 * The shader to use.
	 */
	std::string shader;

	/**
	 * The implementation.
	 */
	particle_renderer_implementation *pr_impl;

	/**
	 * Extra particle renderer attributes.
	 */
	std::map<std::string, float> attributes;

	/**
	 * Creates an particle renderer instance of this type.
	 */
	particle_renderer_instance* create_instance(std::string name);

};

/**
 * A particle modifier type.
 */
struct particle_modifier_type
{
	/**
	 * The name of the particle modifier type.
	 */
	std::string name;

	/**
	 * The implementation.
	 */
	particle_modifier_implementation *pm_impl;

	/**
	 * Extra particle modifier attributes.
	 */
	std::map<std::string, float> attributes;

	/**
	 * Creates an particle modifier instance of this type.
	 */
	particle_modifier_instance* create_instance();

	/**
	 * Creates an particle modifier instance of this type.
	 */
	particle_modifier_instance* create_instance(const vec &o);

};

// abstract definitions - makes everything dynamic
extern std::vector<particle_type*> particle_types;
extern std::vector<particle_emitter_type*> particle_emitter_types;
extern std::vector<particle_renderer_type*> particle_renderer_types;
extern std::vector<particle_modifier_type*> particle_modifier_types;

extern std::map<std::string, particle_type*> particle_types_map;
extern std::map<std::string, particle_emitter_type*> particle_emitter_types_map;
extern std::map<std::string, particle_renderer_type*> particle_renderer_types_map;
extern std::map<std::string, particle_modifier_type*> particle_modifier_types_map;

// implementations - the concrete implementations
extern std::vector<particle_emitter_implementation*> particle_emitter_implementations;
extern std::vector<particle_renderer_implementation*> particle_renderer_implementations;
extern std::vector<particle_modifier_implementation*> particle_modifier_implementations;

// concrete instances refers to the abstract definitions
extern std::vector<particle_instance*> particle_instances;
extern std::vector<particle_emitter_instance*> particle_emitter_instances;
extern std::vector<particle_renderer_instance*> particle_renderer_instances;
extern std::vector<particle_modifier_instance*> particle_modifier_instances;

extern std::map<std::string, particle_renderer_instance*> particle_renderer_instances_map;

// particle pools for performance reasons, replace this with pointers
extern std::list<particle_instance*> alive_pool;
extern std::list<particle_instance*> dead_pool;

extern void init_particles();
extern void clear_particle_pools();
extern void reset_particle_system();

extern void update_particle_system();
extern void update_particle_pools(int elapsedtime);

extern void emit_particles(int elapsedtime);
extern void modify_particles(int elapsedtime);
extern void render_particles();
extern particle_instance* emit_particle();

extern particle_type* add_particle_type(std::string name, std::string pr_inst);
extern particle_type* add_particle_type(std::string name, particle_renderer_instance* pr_inst);
// extern void remove_particle_type(std::string name);

extern particle_emitter_type* add_particle_emitter_type(std::string name, std::string p_type, float mass, float density, int lifetime, int rate, std::string pe_impl);
// extern void remove_particle_emitter_type(std::string name);
// extern int assign_modifier_to_emitter(std::string emitter_name, std::string modifier_name);
extern particle_emitter_instance* create_particle_emitter_instance(std::string pe_type, const vec &o, const vec &vel);

extern particle_renderer_type* add_particle_renderer_type(std::string name, std::string shader, std::string impl);
extern particle_renderer_instance* create_particle_renderer_instance(std::string name, std::string pr_type);
// extern void remove_particle_renderer_type(std::string name);

extern particle_modifier_type* add_particle_modifier_type(std::string name, std::string pm_impl);
// extern void remove_particle_modifier_type(std::string name);
// extern particle_modifier_instance* create_particle_modifier_instance(int type, const vec &o, const vec &vel);
extern void create_particle_modifier_instance(std::string pm_type, const vec &o);

extern int timer_emitter;
extern int timer_modifier;
extern int timer_renderer;

#endif /* ENGINE_PARTICLES_H */
