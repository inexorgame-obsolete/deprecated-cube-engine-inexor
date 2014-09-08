#ifndef ENGINE_ENTITIES_H

#define ENGINE_ENTITIES_H

#include "engine.h"
#include <string>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

struct position;

struct entity_system
{

	int count_positions;
	std::vector<position*> positions;
	Shader *default_shader;

	entity_system();
	~entity_system();

	void cleanup();

	void update_entity_system();

	void render_entities();

	position* create_position(const vec &o);

	void remove_position(position* pos);

	// entity_instance* create_entity();

	// void remove_entity(entity_instance* entity);

	// entity_relationship_instance* create_relationship(entity_relationship_type* er_type, entity_instance *e_inst1, entity_instance *e_inst2);

	// void remove_relationship(entity_relationship_type* er_type, entity_instance *e_inst1, entity_instance *e_inst2);

	// std::list<entity_instance *> get_entities_by_type(entity_type *e_type);

};

extern entity_system es;

/**
 * An entity type.
 */
struct entity_type
{

	/**
	 * The name of the entity type.
	 */
	std::string name;

	/**
	 * Entity type attributes.
	 */
	std::map<std::string, float> attributes;

};

/**
 * An entity type.
 */
template<class ENTITY_IMPLEMENTATION>
struct entity_implemenation_type : public entity_type
{

	/**
	 * The implementation.
	 */
	ENTITY_IMPLEMENTATION *impl;

};

template<class ENTITY_IMPLEMENTATION, class EMITTER_INSTANCE, class MODIFIER_INSTANCE, class INITIALIZER_INSTANCE>
struct entity_emitter_type : public entity_implemenation_type<ENTITY_IMPLEMENTATION>
{

	/**
	 * Emit entity instances every <rate> milliseconds.
	 */
	int rate;

	/**
	 * Number of entity instances to emit in a single batch.
	 */
	int batch_size;

	/**
	 * The modifiers to apply on entity instances spawned by emitters of this type.
	 */
	std::vector<MODIFIER_INSTANCE*> modifiers;

	/**
	 * The initializers to apply on entity instances spawned by emitters of this type.
	 */
	std::vector<INITIALIZER_INSTANCE*> initializers;

	entity_emitter_type() {
		rate = 0;
		batch_size = 1;
	};

	virtual ~entity_emitter_type() { };

	/**
	 * Creates an entity emitter instance of this type.
	 */
	virtual EMITTER_INSTANCE* create_instance(const vec &o, const vec &vel) = 0;

};

template<class ENTITY_IMPLEMENTATION, class RENDERER_INSTANCE>
struct entity_renderer_type : public entity_implemenation_type<ENTITY_IMPLEMENTATION>
{

	entity_renderer_type() { };
	virtual ~entity_renderer_type() { };

	/**
	 * Creates an entity renderer instance of this type.
	 */
	virtual RENDERER_INSTANCE* create_instance(std::string name) = 0;

};

template<class ENTITY_IMPLEMENTATION, class MODIFIER_INSTANCE>
struct entity_modifier_type : public entity_implemenation_type<ENTITY_IMPLEMENTATION>
{

	entity_modifier_type() { };
	virtual ~entity_modifier_type() { };

	/**
	 * Creates an entity modifier instance of this type.
	 */
	virtual MODIFIER_INSTANCE* create_instance() = 0;

};

template<class ENTITY_IMPLEMENTATION, class INITIALIZER_INSTANCE>
struct entity_initializer_type : public entity_implemenation_type<ENTITY_IMPLEMENTATION>
{

	entity_initializer_type() { };
	virtual ~entity_initializer_type() { };

	/**
	 * Creates an entity initializer instance of this type.
	 */
	virtual INITIALIZER_INSTANCE* create_instance() = 0;

};

/**
 * An instance of an entity type.
 */
template<class ENTITY_TYPE = entity_type>
struct entity_instance
{

	/**
	 * The entity type.
	 */
	ENTITY_TYPE *type;

	/**
	 * Entity instance attributes.
	 */
	std::map<std::string, float> attributes;

	/**
	 * Returns the list of parent entity instances.
	 */
	// std::list<entity_instance*> get_parents();

	/**
	 * Returns the list of child entity instances.
	 */
	// std::list<entity_instance*> get_childs();

};

struct position
{
	/**
	 * Entity position.
	 */
	vec o;

	position() { };

	position(const vec &o) {
		this->o = o;
	};

	position(float x, float y, float z) {
		this->o = vec(x, y, z);
	};

};

template<class ENTITY_TYPE>
struct positional_entity_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * Managed position.
	 */
	position* pos;

};

template<class ENTITY_TYPE>
struct entity_emitter_instance : public positional_entity_instance<ENTITY_TYPE>
{

	/**
	 * If true, the entities will be emitted.
	 */
	bool enabled;

};

template<class ENTITY_TYPE>
struct entity_event_emitter_instance : public entity_emitter_instance<ENTITY_TYPE>
{

	// TODO: event stuff

};

template<class ENTITY_TYPE>
struct entity_time_emitter_instance : public entity_emitter_instance<ENTITY_TYPE>
{

	/**
	 * Emit entities every <rate> milliseconds.
	 */
	int rate;

	/**
	 * Number of entities to emit in a single batch.
	 */
	int batch_size;

	/**
	 * Remaining millis to process.
	 */
	int millistoprocess;

};

template<class ENTITY_TYPE, class ENTITY_INSTANCE>
struct entity_renderer_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * The name of the renderer instance.
	 */
	std::string name;

	/**
	 * The entity instances to render.
	 */
	std::list<ENTITY_INSTANCE*> instances;

};

template<class ENTITY_TYPE>
struct entity_modifier_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * Generic pointers per modifier instance.
	 */
	std::map<std::string, void*> pointers;

	/**
	 * A modifier can have multiple positions.
	 */
	std::vector<position*> positions;

	// TODO: destructor destructs all positions with es->remove_position(pos)

	/**
	 * Adds a modifier position.
	 */
	position* add_position(const vec &o)
	{
		position* pos = es.create_position(o);
		positions.push_back(pos);
		return pos;
	}

	/**
	 * Sets the modifier position on the given index.
	 */
	void set_position(int index, vec o)
	{
		positions[index]->o = o;
	}

};

template<class ENTITY_TYPE>
struct entity_initializer_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * Generic pointers per modifier instance.
	 */
	std::map<std::string, void*> pointers;

	/**
	 * A modifier can have multiple positions.
	 */
	std::vector<position*> positions;

	// TODO: destructor destructs all positions with es->remove_position(pos)

	/**
	 * Adds a modifier position.
	 */
	position* add_position(const vec &o)
	{
		position* pos = es.create_position(o);
		positions.push_back(pos);
		return pos;
	}

	/**
	 * Sets the modifier position on the given index.
	 */
	void set_position(int index, vec o)
	{
		positions[index]->o = o;
	}

};

template<class SPECIALIZED_ENTITY_INSTANCE>
struct entity_implementation_base {

	/**
	 * The name of the implementation.
	 */
	std::string name;

	entity_implementation_base() { }
	entity_implementation_base(const std::string& name) {
		this->name = name;
	}
	virtual ~entity_implementation_base() { };

	virtual void render_edit_overlay(SPECIALIZED_ENTITY_INSTANCE *entity_instance) = 0;

};




/*************************** 	future     ***************************/


/**
 * An entity relationship type.
 */
/*
struct entity_relationship_type
{

	std::string name;
	std::map<std::string, float> attributes;

};
*/

/**
 * Relationship between to entity instances.
 */
// struct entity_relationship_instance
// {

	/**
	 * The relationship type.
	 */
	// entity_relationship_type *er_type;

	/**
	 * The start node.
	 */
	// entity_instance* parent;

	/**
	 * The end node.
	 */
	// entity_instance* child;

// };

#endif /* ENGINE_PARTICLES_H */

