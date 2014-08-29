#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Spring weaver:
 * 1. Raster with distances: size_x, size_y
 * 2.
 */
struct spring_weaver : public particle_initializer_implementation
{

public:

	static spring_weaver& instance()
	{
		static spring_weaver _instance;
		return _instance;
	}
	virtual ~spring_weaver() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {

		spring_constant = pi_inst->attributes["spring_constant"];
		spring_friction = pi_inst->attributes["spring_friction"];
		spring_length_x = pi_inst->attributes["spring_length_x"];
		spring_length_y = pi_inst->attributes["spring_length_y"];
		size_x = (int) pi_inst->attributes["size_x"];
		size_y = (int) pi_inst->attributes["size_y"];

		// init matrix [size_x X size_y]
		std::vector<std::vector<particle_instance *> > matrix(size_x);
		for (int i = 0; i < size_x; i++) matrix[i].resize(size_y);

		// fill matrix with particle instances from list
		int p = 0;
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			matrix[p / size_x][p % size_x] = (*p_it);
			p++;
		}

		// connect particles by rules
		std::vector<std::string> *rules = static_cast<std::vector<std::string>*>(pi_inst->pointers["rules"]);
		for (int x = 0; x < size_x; x++)
		{
			for (int y = 0; y < size_y; y++)
			{
				for (std::vector<std::string>::iterator it = rules->begin() ; it != rules->end(); ++it)
				{
					ivec spring_transformation_rule = ps.spring_transformation_rules[(*it)];
					int sx = x + spring_transformation_rule.x;
					int sy = y + spring_transformation_rule.y;
					if (sx >= 0 && sx < size_x && sy >= 0 && sy < size_y)
					{
						float slx = spring_length_x * (float) spring_transformation_rule.x;
						float sly = spring_length_y * (float) spring_transformation_rule.y;
						spring_length = sqrt((slx * slx) + (sly * sly));
						// conoutf("x:%d y:%d | sx:%d sy:%d | len:%2.2f", x, y, sx, sy, spring_length);
						create_spring(matrix[x][y], matrix[sx][sy], spring_constant, spring_friction, spring_length);
					}
				}
			}
		}

		// stretch
		//   x+1,y,z,lx
		//   x,y+1,z,ly
		// sheer
		//   x+1,y+1,z,sqrt((lx*lx)+(ly*ly))
		//   x-1,y+1,z,sqrt((lx*lx)+(ly*ly))
		// bend
		//   x+2,y,z,lx*2
		//   x,y+2,z,ly*2
	}

	void create_spring(particle_instance *p1, particle_instance *p2, float spring_constant, float spring_friction, float spring_length)
	{
		// conoutf("p1:%d", p1->remaining);
		// conoutf("p2:%d", p2->remaining);
		spring_instance *spring_inst = new spring_instance;
		spring_inst->p_inst_1 = p1;
		spring_inst->p_inst_2 = p2;
		spring_inst->spring_constant = spring_constant;
		spring_inst->spring_friction = spring_friction;
		spring_inst->spring_length = spring_length;
		spring_inst->alive = true;
		ps.add_spring(spring_inst);
	}

private:

	float time_factor;
	float spring_constant;
	float spring_friction;
	float spring_length;
	float satellite_mass_factor;
	float satellite_density_factor;
	int size_x;
	int size_y;
	int spring_length_x;
	int spring_length_y;

	spring_weaver() : particle_initializer_implementation("spring_weaver") {
		ps.add_initializer_implementation(this);
		time_factor = 0.0f;
		spring_constant = 0.1f;
		spring_friction = 0.95f;
		spring_length = 10.0f;
		satellite_mass_factor = 0.1f;
		satellite_density_factor = 0.1f;
		size_x = 0;
		size_y = 0;
		spring_length_x = 0.0f;
		spring_length_y = 0.0f;
	}
	spring_weaver( const spring_weaver& );
	spring_weaver & operator = (const spring_weaver &);

};

spring_weaver& ps_initializer_spring_weaver = spring_weaver::instance();
