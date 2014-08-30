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
	 * The name of the particle type.
	 */
	std::string name;

	/**
	 * Type attributes.
	 */
	std::map<std::string, float> attributes;

};

/**
 * An entity relationship type.
 */
struct entity_relationship_type
{

	/**
	 * The name of the particle type.
	 */
	std::string name;

	/**
	 * Type attributes.
	 */
	std::map<std::string, float> attributes;

};

/**
 * An instance of an entity type.
 */
struct entity_instance
{

	/**
	 * The entity type.
	 */
	entity_type *e_type;

	/**
	 * Attributes per entity instance.
	 */
	std::map<std::string, float> attributes;

	/**
	 * Returns the list of parent entity instances.
	 */
	std::list<entity_instance*> get_parents();

	/**
	 * Returns the list of child entity instances.
	 */
	std::list<entity_instance*> get_childs();

};

/**
 * Relationship between to entity instances.
 */
struct entity_relationship_instance
{

	/**
	 * The relationship type.
	 */
	entity_relationship_type *er_type;

	/**
	 * The start node.
	 */
	entity_instance* parent;

	/**
	 * The end node.
	 */
	entity_instance* child;

};

struct positional_entity_instance : public entity_instance
{

	/**
	 * Entity position.
	 */
	vec o;

	/**
	 * Rendering of the entity.
	 */
	void render();

	/**
	 * Rendering of the entity in edit mode;
	 */
	void render_edit();

};

struct entity_system
{

	entity_instance* create_entity();

	void remove_entity(entity_instance* entity);

	entity_relationship_instance* create_relationship(entity_relationship_type* er_type, entity_instance *e_inst1, entity_instance *e_inst2);

	void remove_relationship(entity_relationship_type* er_type, entity_instance *e_inst1, entity_instance *e_inst2);

	std::list<entity_instance *> get_entities_by_type(entity_type *e_type);

};

extern entity_system es;

#endif /* ENGINE_PARTICLES_H */

