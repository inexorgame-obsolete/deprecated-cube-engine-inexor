#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Creates faces of the cloth.
 */
struct cloth_faces : public particle_initializer_implementation
{

public:

	static cloth_faces& instance()
	{
		static cloth_faces _instance;
		return _instance;
	}
	virtual ~cloth_faces() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {

		size_x = (int) pi_inst->attributes["size_x"];
		size_y = (int) pi_inst->attributes["size_y"];

		// init matrix [size_x, size_y]
		std::vector<std::vector<particle_instance *> > matrix2(size_x);
		for (x = 0; x < size_x; x++) matrix2[x].resize(size_y);

		// transform 1D list of particles into a 2D matrix
		int p = 0;
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			matrix2[p / size_x][p % size_x] = (*p_it);
			p++;
		}

		face_type* f_type = static_cast<face_type*>(pi_inst->pointers["face_type"]);
		for (x = 0; x < size_x; x++)
			for (y = 0; y < size_y; y++)
				if (x >= 0 && x + 1 < size_x && y >= 0 && y + 1 < size_y)
					f_type->create_instance(matrix2[x][y], matrix2[x + 1][y], matrix2[x + 1][y + 1], matrix2[x][y + 1], face_color);
	}

	void render_edit_overlay(particle_initializer_instance *entity_instance) { }

private:

	int size_x;
	int size_y;

	float slx;
	float sly;
	int x;
	int y;

	vec4 face_color;

	cloth_faces() : particle_initializer_implementation("cloth_faces") {
		ps.add_initializer_implementation(this);
		size_x = 0;
		size_y = 0;
		slx = 0.0f;
		sly = 0.0f;
		x = 0;
		y = 0;
		face_color = vec4(0.9f, 0.9f, 0.9f, 0.5f);
	}
	cloth_faces( const cloth_faces& );
	cloth_faces & operator = (const cloth_faces &);

};

cloth_faces& ps_initializer_cloth_faces = cloth_faces::instance();
