#ifndef ENGINE_PARTICLES_H

#define ENGINE_PARTICLES_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include "../entities/entities.h"
#include "mu/muParser.h"

struct particle_type;
struct particle_emitter_type;
struct particle_renderer_type;
struct particle_modifier_type;
struct particle_initializer_type;

struct particle_instance;
struct particle_emitter_instance;
struct particle_renderer_instance;
struct particle_modifier_instance;
struct particle_initializer_instance;

struct particle_emitter_implementation;
struct particle_renderer_implementation;
struct particle_modifier_implementation;
struct particle_initializer_implementation;

struct noop_emitter;
struct noop_renderer;
struct noop_modifier;
struct noop_initializer;

/**
 * A particle emitter instance is an instance of a particle emitter
 * type.
 */
struct particle_emitter_instance : public entity_instance
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
	 * The entity. May be replaced by a new entity implementation.
	 */
	extentity *ent;

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
	 * Number of particles to emit in a single batch.
	 */
	int batch_size;

	/**
	 * Remaining millis to process.
	 */
	int millistoprocess;

	/**
	 * The modifiers to apply on particles spawned by this emitter.
	 */
	std::vector<particle_modifier_instance*> modifiers;

	/**
	 * The initializers to apply on particles spawned by emitters of this type.
	 */
	std::vector<particle_initializer_instance*> initializers;

	/**
	 * Adds a modifier instance
	 */
	void add_modifier(particle_modifier_instance* pm_inst);

	/**
	 * Adds a initializer instance
	 */
	void add_initializer(particle_initializer_instance* pi_inst);

};

/**
 * A particle instance.
 */
struct particle_instance : public entity_instance
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
	 * The last current position of the particle instance.
	 */
	vec last;

	/**
	 * The current velocity of the particle instance. The last velocity can be calculated
	 * by the current and last position of the particle instance.
	 */
    vec vel;

    /**
     * Rolling particles.
     */
    float roll;

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
     * The time elapsed in the previous iteration.
     */
    int last_elapsed;

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

};

/**
 * A particle renderer instance.
 * Different rendering of particles bound on a single particle.
 */
struct particle_renderer_instance : public entity_instance
{
	/**
	 * The name of the renderer instance.
	 */
	std::string name;

	/**
	 * The name of the texture.
	 */
	std::string texture;

	/**
	 * The name of the shader.
	 */
	std::string shader;

	/**
	 * Position offset.
	 */
	vec offset;

	/**
	 * The color to use.
	 */
	vec4 color;

	/**
	 * The particle renderer type.
	 */
	particle_renderer_type *pr_type;

	/**
	 * The particle instances to render.
	 */
	std::list<particle_instance*> particles;

};

/**
 * Particle modifiers are altering the state of a particle (for example the position).
 */
struct particle_modifier_instance : public entity_instance
{

	/**
	 * The modifier type.
	 */
	particle_modifier_type *pm_type;

	/**
	 * The current position of the particle modifier instance (if any).
	 */
	vec o;

	/**
	 * The velocity of the particle modifier instance.
	 */
	vec vel;

	/**
	 * The entity. May be replaced by a new entity implementation.
	 */
	extentity *ent;

	/**
	 * Generic pointers per modifier instance.
	 */
	std::map<std::string, void*> pointers;

};

/**
 * Particle initializers are initializing the state of a particle.
 */
struct particle_initializer_instance : public entity_instance
{

	/**
	 * The initializer type.
	 */
	particle_initializer_type *pi_type;

	/**
	 * Generic pointers per modifier instance.
	 */
	std::map<std::string, void*> pointers;

	// The following lists allows the initializers to make more complex
	// initializations that an emitter would be able. For example, choose
	// the particle_type by rules.

	/**
	 * The a list of particle types.
	 */
	std::list<particle_type*> particle_types;

	/**
	 * The a list of particle modifier instances.
	 */
	std::list<particle_modifier_instance*> particle_modifiers;

	/**
	 * Adds a particle type.
	 */
	void add_particle_type(particle_type* p_type);

	/**
	 * Adds a modifier instance.
	 */
	void add_particle_modifier(particle_modifier_instance* pm_inst);

};

struct particle_implementation_base {

	/**
	 * The name of the implementation.
	 */
	const std::string name;

	particle_implementation_base(const std::string& name);
	~particle_implementation_base();

};

/**
 * Interface for a particle emitter implementation.
 *
 * Particle emitters should register themselves in their constructor
 * using add_particle_emitter_type()
 */
struct particle_emitter_implementation : public particle_implementation_base
{

	particle_emitter_implementation(const std::string& name);
	virtual ~particle_emitter_implementation();

	/**
	 * Emits new particle(s).
	 */
	virtual std::list<particle_instance*> emit(particle_emitter_instance *pe_inst, int elapsedtime) = 0;

};

/**
 * Interface for a particle renderer implementation.
 *
 * Particle renderers should register themselves in their constructor
 * using add_particle_renderer_type()
 */
struct particle_renderer_implementation : public particle_implementation_base
{

	particle_renderer_implementation(const std::string& name);
	virtual ~particle_renderer_implementation();

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

	particle_modifier_implementation(const std::string& name);
	virtual ~particle_modifier_implementation();

	/**
	 * Modifies particle(s).
	 */
	virtual void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) = 0;

	/**
	 * Called only once per iteration and modifier instance.
	 */
	virtual void modify(particle_modifier_instance *pm_inst, int elapsedtime) = 0;

	/**
	 * Called only once per iteration and modifier implementation.
	 */
	virtual void modify(int elapsedtime) = 0;

	/**
	 * Called directly after emitation.
	 */
//	virtual void init(particle_instance* p_inst) = 0;

};

/**
 * Interface for a particle initializer implementation.
 *
 * Particle initializers should register themselves in their constructor
 * using add_particle_initializer_type()
 */
struct particle_initializer_implementation : public particle_implementation_base
{

	particle_initializer_implementation(const std::string& name);
	virtual ~particle_initializer_implementation();

	/**
	 * Initializes particle(s).
	 */
	virtual void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) = 0;

};

/**
 * A particle type.
 */
struct particle_type : public entity_type
{

	/**
	 * The reference to the particle renderer instance.
	 */
	particle_renderer_instance *pr_inst;

};

/**
 * A particle emitter type. Notice that the actual implementation of
 * an particle emitter type needs to be bind using a function pointer.
 */
struct particle_emitter_type : public entity_type
{

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
	 * Number of particles to emit in a single batch.
	 */
	int batch_size;

	/**
	 * The implementation.
	 */
	particle_emitter_implementation *pe_impl;

	/**
	 * The modifiers to apply on particles spawned by emitters of this type.
	 */
	std::vector<particle_modifier_instance*> modifiers;

	/**
	 * The initializers to apply on particles spawned by emitters of this type.
	 */
	std::vector<particle_initializer_instance*> initializers;

	/**
	 * Creates an particle emitter instance of this type.
	 */
	particle_emitter_instance* create_instance(const vec &o, const vec &vel);

};

/**
 * A particle renderer type.
 */
struct particle_renderer_type : public entity_type
{

	/**
	 * The name of the texture.
	 */
	std::string texture;

	/**
	 * The shader to use.
	 */
	std::string shader;

	/**
	 * The color to use.
	 */
	vec4 color;

	/**
	 * The implementation.
	 */
	particle_renderer_implementation *pr_impl;

	/**
	 * Creates an particle renderer instance of this type.
	 */
	particle_renderer_instance* create_instance(std::string name);

};

/**
 * A particle modifier type.
 */
struct particle_modifier_type : public entity_type
{

	/**
	 * The implementation.
	 */
	particle_modifier_implementation *pm_impl;

	/**
	 * Generic pointers per type.
	 */
	std::map<std::string, void*> pointers;

	/**
	 * Creates an particle modifier instance of this type.
	 */
	particle_modifier_instance* create_instance();

	/**
	 * Creates an particle modifier instance of this type.
	 */
	particle_modifier_instance* create_instance(const vec &o);

};

/**
 * A particle initializer type.
 */
struct particle_initializer_type : public entity_type
{

	/**
	 * The implementation.
	 */
	particle_initializer_implementation *pi_impl;

	/**
	 * Generic pointers per type.
	 */
	std::map<std::string, void*> pointers;

	/**
	 * Creates an particle initializer instance of this type.
	 */
	particle_initializer_instance* create_instance();

};

/**
 * Springs between two particles.
 */
struct spring_instance
{

	/**
	 * The particle at the one side of the spring.
	 */
	particle_instance *p_inst_1;

	/**
	 * The particle at the other side of the spring.
	 */
	particle_instance *p_inst_2;

	/**
	 * The ideal length of the spring.
	 */
	float spring_length;

	/**
	 * The spring constant.
	 */
	float spring_constant;

	/**
	 * The spring friction.
	 */
	float spring_friction;

	/**
	 * If true, the spring is alive.
	 */
	bool alive;

};

struct spring_builder
{
	std::vector<std::string> *rules;
	spring_builder* stretch_x();
	spring_builder* stretch_y();
	spring_builder* stretch_z();
	spring_builder* stretch_xy();
	spring_builder* stretch_xz();
	spring_builder* stretch_yz();
	spring_builder* stretch_xyz();
	spring_builder* sheer_xy();
	spring_builder* sheer_xz();
	spring_builder* sheer_yz();
	spring_builder* sheer_xyz();
	spring_builder* bend_x();
	spring_builder* bend_y();
	spring_builder* bend_z();
	spring_builder* bend_xy();
	spring_builder* bend_xz();
	spring_builder* bend_yz();
	spring_builder* bend_xyz();
	std::vector<std::string>* get();

	spring_builder();
	~spring_builder();
};

/**
 * Worker thread container for calculate particle physics in it's own thread.
 */
struct particle_state_worker
{

	/**
	 * The worker thread.
	 */
	SDL_Thread *thread;

	/**
	 * If true, the worker thread will continue.
	 */
	bool running;

	/**
	 * If false, the worker thread hasn't ended.
	 */
	bool stopped;

	particle_state_worker();
	~particle_state_worker();
	void start();
	void stop();
	static int work(void *data);

};

/**
 * Encapsulates the whole particle system in a single class. The methods and
 * members of this class can be considered as the public API.
 */
struct particle_system
{
	/**
	 * Particle frame in milliseconds.
	 */
	float particle_frame;

	/**
	 * Milliseconds since the last frame.
	 */
	int particlemillis;

	/**
	 * We count the sizes by ourselves to be faster, thread-safe and vendor independent.
	 */
	int count_particle_types;
	int count_particle_emitter_types;
	int count_particle_renderer_types;
	int count_particle_modifier_types;
	int count_particle_initializer_types;
	int count_particle_emitter_implementations;
	int count_particle_renderer_implementations;
	int count_particle_modifier_implementations;
	int count_particle_initializer_implementations;
	int count_particles_instances;
	int count_particle_emitter_instances;
	int count_particle_renderer_instances;
	int count_particle_modifier_instances;
	int count_particle_initializer_instances;
	int count_spring_instances;
	int count_alive_pool;
	int count_dead_pool;

	int timer_emitter;
	int timer_renderer;
	int timer_modifier;
	int timer_initializer;

	// Abstract types - makes everything dynamic
	std::vector<particle_type*> particle_types;
	std::vector<particle_emitter_type*> particle_emitter_types;
	std::vector<particle_renderer_type*> particle_renderer_types;
	std::vector<particle_modifier_type*> particle_modifier_types;
	std::vector<particle_initializer_type*> particle_initializer_types;

	// Name to type mappings
	std::map<std::string, particle_type*> particle_types_map;
	std::map<std::string, particle_emitter_type*> particle_emitter_types_map;
	std::map<std::string, particle_renderer_type*> particle_renderer_types_map;
	std::map<std::string, particle_modifier_type*> particle_modifier_types_map;
	std::map<std::string, particle_initializer_type*> particle_initializer_types_map;

	// Implementations - singleton instances of a concrete implementation
	std::vector<particle_emitter_implementation*> particle_emitter_implementations;
	std::vector<particle_renderer_implementation*> particle_renderer_implementations;
	std::vector<particle_modifier_implementation*> particle_modifier_implementations;
	std::vector<particle_initializer_implementation*> particle_initializer_implementations;

	// Name to implementation mappings
	std::map<std::string, particle_emitter_implementation*> particle_emitter_implementations_map;
	std::map<std::string, particle_renderer_implementation*> particle_renderer_implementations_map;
	std::map<std::string, particle_modifier_implementation*> particle_modifier_implementations_map;
	std::map<std::string, particle_initializer_implementation*> particle_initializer_implementations_map;

	// Instances of types
	std::vector<particle_instance*> particle_instances;
	std::vector<particle_emitter_instance*> particle_emitter_instances;
	std::vector<particle_renderer_instance*> particle_renderer_instances;
	std::vector<particle_modifier_instance*> particle_modifier_instances;
	std::vector<particle_initializer_instance*> particle_initializer_instances;
	std::list<spring_instance *> spring_instances;

	// Name to instance mappings
	std::map<std::string, particle_renderer_instance*> particle_renderer_instances_map;

	// The spring transformation rules
	std::map<std::string, ivec> spring_construction_rules;

	// Use pools for performance reasons
	std::list<particle_instance*> alive_pool;
	std::deque<particle_instance*> dead_pool;

	particle_state_worker p_worker;

	bool spring_lock;

	// Default types and implementations
	particle_type* noop_particle_type;
	particle_emitter_implementation* noop_emitter_impl;
	particle_emitter_type* noop_emitter_type;
	particle_emitter_instance* noop_emitter_inst;
	particle_modifier_implementation* noop_modifier_impl;
	particle_modifier_type* noop_modifier_type;
	particle_modifier_instance* noop_modifier_inst;
	particle_renderer_implementation* noop_renderer_impl;
	particle_renderer_type* noop_renderer_type;
	particle_renderer_instance* noop_renderer_inst;
	particle_initializer_implementation* noop_initializer_impl;
	particle_initializer_type* noop_initializer_type;
	particle_initializer_instance* noop_initializer_inst;

	particle_system();
	~particle_system();

	void init_particles();
	void init_defaults();
	void clear_particle_pools();
	void clear_particle_instances();
	void cleanup();

	void update_particle_system();
	void update_particle_pools(int elapsedtime);

	void emit_particles(int elapsedtime);
	void emit_particles(particle_emitter_instance* pe_inst, int elapsedtime);
	void modify_particles(int elapsedtime);
	void render_particles();
	particle_instance* emit_particle();

	particle_type* add_particle_type(std::string name, std::string pr_inst);
	particle_type* add_particle_type(std::string name, particle_renderer_instance* pr_inst);
	void remove_particle_type(std::string name);
	void remove_all_particle_types();

	particle_emitter_type* add_particle_emitter_type(std::string name, std::string p_type, float mass, float density, int lifetime, int rate, std::string pe_impl);
	particle_emitter_type* add_particle_emitter_type(std::string name, particle_type* p_type, float mass, float density, int lifetime, int rate, std::string pe_impl);
	particle_emitter_instance* create_particle_emitter_instance(std::string pe_type, const vec &o, const vec &vel);
	particle_emitter_instance* create_particle_emitter_instance(particle_emitter_type* pe_type, const vec &o, const vec &vel);
	void remove_particle_emitter_type(std::string name);
	void remove_all_particle_emitter_types();
	void remove_all_particle_emitter_instances();

	// void init_particle_renderer();
	particle_renderer_type* add_particle_renderer_type(std::string name, std::string texture, std::string shader, const vec4 &color, std::string impl);
	particle_renderer_instance* create_particle_renderer_instance(std::string name, std::string pr_type);
	particle_renderer_instance* create_particle_renderer_instance(std::string name, particle_renderer_type* pr_type);
	void remove_particle_renderer_type(std::string name);
	void remove_all_particle_renderer_types();
	void remove_all_particle_renderer_instances();

	particle_modifier_type* add_particle_modifier_type(std::string name, std::string pm_impl);
	particle_modifier_instance* create_particle_modifier_instance(std::string pm_type, const vec &o);
	void remove_particle_modifier_type(std::string name);
	void remove_all_particle_modifier_types();
	void remove_all_particle_modifier_instances();

	particle_initializer_type* add_particle_initializer_type(std::string name, std::string pi_impl);
	particle_initializer_instance* create_particle_initializer_instance(std::string pi_type);
	void remove_particle_initializer_type(std::string name);
	void remove_all_particle_initializer_types();
	void remove_all_particle_initializer_instances();

	void add_spring(spring_instance *spring_inst);
	void add_spring_construction_rule(std::string name, ivec rule);
	void add_spring_construction_rule(std::string name, int x, int y, int z);
	void init_spring_construction_rules();

	void add_emitter_implementation(particle_emitter_implementation *pe_impl);
	void add_modifier_implementation(particle_modifier_implementation *pm_impl);
	void add_renderer_implementation(particle_renderer_implementation *pr_impl);
	void add_initializer_implementation(particle_initializer_implementation *pi_impl);

};

extern particle_system ps;

#endif /* ENGINE_PARTICLES_H */
