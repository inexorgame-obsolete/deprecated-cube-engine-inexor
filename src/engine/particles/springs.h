#ifndef ENGINE_SPRINGS_H

#define ENGINE_SPRINGS_H

// #include "particles.h"

struct particle_instance;

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

#endif
