#ifndef ENGINE_FACES_H

#define ENGINE_FACES_H

#include "cube.h"
#include "engine.h"

struct particle_instance;
struct face_instance;

struct face_type : public entity_type
{

	/**
	 * The name of the texture.
	 */
	std::string texture;

	/**
	 * The face instances to render.
	 */
	std::list<face_instance*> instances;

	face_type() { };
	virtual ~face_type() { };

	/**
	 * Creates an face instance of this type.
	 */
	virtual face_instance* create_instance(particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3);

	/**
	 * Creates an face instance of this type.
	 */
	virtual face_instance* create_instance(particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3, vec4 color);

};

struct face_instance : public entity_instance<face_type>
{

	/**
	 * Each face consists of 4 particles.
	 */
	particle_instance *p[4];

	/**
	 * The color to use.
	 */
	vec4 color;

	face_instance(particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3) {
		p[0] = p0;
		p[1] = p1;
		p[2] = p2;
		p[3] = p3;
	};

};

/*
struct face_builder
{
	// The construction rules.
	std::vector<std::string> *rules;

	// The current position in the matrix.
	ivec current;

	face_builder* absolute_xyz(int x, int y, int z);
	face_builder* relative_x(int x);
	face_builder* relative_y(int y);
	face_builder* relative_z(int z);
	face_builder* relative_xy(int x, int y);
	face_builder* relative_xz(int x, int z);
	face_builder* relative_yz(int y, int z);
	face_builder* relative_xyz(int x, int y, int z);
	std::vector<std::string>* get();

	face_builder();
	face_builder(int x, int y, int z);
	~face_builder();

};
*/

#endif
