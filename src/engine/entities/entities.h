#ifndef ENGINE_ENTITIES_H

#define ENGINE_ENTITIES_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include <deque>

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

/**
 * An instance of an entity type.
 */
template<class ENTITY_TYPE>
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

template<class ENTITY_TYPE>
struct positional_entity_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * Entity position.
	 */
	vec o;

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

template<class ENTITY_TYPE, class ENTITY_INSTANCE_TYPE>
struct entity_modifier_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * Generic pointers per modifier instance.
	 */
	std::map<std::string, void*> pointers;

	/**
	 * A modifier can have multiple positions.
	 */
	std::vector<positional_entity_instance<ENTITY_INSTANCE_TYPE> *> positions;

	/**
	 * Adds a modifier position.
	 */
	positional_entity_instance<ENTITY_INSTANCE_TYPE>* add_position(vec o)
	{
		positional_entity_instance<ENTITY_INSTANCE_TYPE>* position = new positional_entity_instance<ENTITY_INSTANCE_TYPE>;
		position->o = o;
		positions.push_back(position);
		return position;
	}

	/**
	 * Sets the modifier position on the given index.
	 */
	void set_position(int index, vec o)
	{
		positions[index]->o = o;
	}

};

template<class ENTITY_TYPE, class ENTITY_INSTANCE_TYPE>
struct entity_initializer_instance : public entity_instance<ENTITY_TYPE>
{

	/**
	 * Generic pointers per modifier instance.
	 */
	std::map<std::string, void*> pointers;

	/**
	 * A modifier can have multiple positions.
	 */
	std::vector<positional_entity_instance<ENTITY_INSTANCE_TYPE> *> positions;

	/**
	 * Adds a modifier position.
	 */
	positional_entity_instance<ENTITY_INSTANCE_TYPE>* add_position(vec o)
	{
		positional_entity_instance<ENTITY_INSTANCE_TYPE>* position = new positional_entity_instance<ENTITY_INSTANCE_TYPE>;
		position->o = o;
		positions.push_back(position);
		return position;
	}

	/**
	 * Sets the modifier position on the given index.
	 */
	void set_position(int index, vec o)
	{
		// TODO: range check
		positions[index]->o = o;
	}

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

struct entity_system
{

	entity_system();
	~entity_system();

	void cleanup();

	void render_entities();
	// entity_instance* create_entity();

	// void remove_entity(entity_instance* entity);

	// entity_relationship_instance* create_relationship(entity_relationship_type* er_type, entity_instance *e_inst1, entity_instance *e_inst2);

	// void remove_relationship(entity_relationship_type* er_type, entity_instance *e_inst1, entity_instance *e_inst2);

	// std::list<entity_instance *> get_entities_by_type(entity_type *e_type);

};

extern entity_system es;

#endif /* ENGINE_PARTICLES_H */

