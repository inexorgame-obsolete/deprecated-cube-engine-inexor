#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Spring weaver:
 * 1. Raster with distances: size_x, size_y, size_z
 * 2.
 */
struct jelly_faces : public particle_initializer_implementation
{

public:

	static jelly_faces& instance()
	{
		static jelly_faces _instance;
		return _instance;
	}
	virtual ~jelly_faces() { }

	inline void init(particle_initializer_instance *pi_inst, std::list<particle_instance *> particles, int elapsedtime) {

		size_x = (int) pi_inst->attributes["size_x"];
		size_y = (int) pi_inst->attributes["size_y"];
		size_z = (int) pi_inst->attributes["size_z"];

		// init matrix [size_x, size_y, size_z]
		std::vector<std::vector<std::vector<particle_instance *> > > matrix(size_x);
		for (x = 0; x < size_x; x++)
		{
			matrix[x].resize(size_y);
			for (y = 0; y < size_y; y++) matrix[x][y].resize(size_z);
		}

		// transform 1D list of particles into a 3D matrix
		int p = 0;
		for(std::list<particle_instance*>::iterator p_it = particles.begin(); p_it != particles.end(); ++p_it)
		{
			z = p / (size_x * size_y);
			y = (p % (size_x * size_y)) / size_x;
			x = p - y * size_x - z * size_x * size_y;
			matrix[x][y][z] = (*p_it);
			p++;
		}

		p = 0;
		face_type* f_type = static_cast<face_type*>(pi_inst->pointers["face_type"]);
		for (x = 0; x < size_x; x++)
		{
			// xy
			for (y = 0; y < size_y; y++)
			{
				if (x >= 0 && x + 1 < size_x && y >= 0 && y + 1 < size_y)
				{
					p++;
					// vec4 color = vec4(0.7f + (p % 2) * 0.2f, 0.5f, 0.0f, 0.4f);
					f_type->create_instance(matrix[x][y][0], matrix[x + 1][y][0], matrix[x + 1][y + 1][0], matrix[x][y + 1][0], face_color);
					f_type->create_instance(matrix[x][y][size_z - 1], matrix[x][y + 1][size_z - 1], matrix[x + 1][y + 1][size_z - 1], matrix[x + 1][y][size_z - 1], face_color);
				}
			}
			// xz
			for (z = 0; z < size_z; z++)
			{
				if (x >= 0 && x + 1 < size_x && z >= 0 && z + 1 < size_z)
				{
					p++;
					// vec4 color = vec4(0.7f + (p % 2) * 0.2f, 0.5f, 0.0f, 0.4f);
					f_type->create_instance(matrix[x][0][z], matrix[x][0][z + 1], matrix[x + 1][0][z + 1], matrix[x + 1][0][z], face_color);
					f_type->create_instance(matrix[x][size_y - 1][z], matrix[x + 1][size_y - 1][z], matrix[x + 1][size_y - 1][z + 1], matrix[x][size_y - 1][z + 1], face_color);
				}
			}
		}
		for (y = 0; y < size_y; y++)
		{
			// yz
			for (z = 0; z < size_z; z++)
			{
				if (y >= 0 && y + 1 < size_y && z >= 0 && z + 1 < size_z)
				{
					p++;
					// vec4 color = vec4(0.7f + (p % 2) * 0.2f, 0.5f, 0.0f, 0.4f);

					f_type->create_instance(matrix[0][y][z], matrix[0][y + 1][z], matrix[0][y + 1][z + 1], matrix[0][y][z + 1], face_color);
					f_type->create_instance(matrix[size_x - 1][y][z], matrix[size_x - 1][y][z + 1], matrix[size_x - 1][y + 1][z + 1], matrix[size_x - 1][y + 1][z], face_color);
				}
			}
		}
	}

	void render_edit_overlay(particle_initializer_instance *entity_instance) { }

private:

	int size_x;
	int size_y;
	int size_z;

	float slx;
	float sly;
	float slz;
	int x;
	int y;
	int z;

	vec4 face_color;

	jelly_faces() : particle_initializer_implementation("jelly_faces") {
		ps.add_initializer_implementation(this);
		size_x = 0;
		size_y = 0;
		size_z = 0;
		slx = 0.0f;
		sly = 0.0f;
		slz = 0.0f;
		x = 0;
		y = 0;
		z = 0;
		face_color = vec4(0.9f, 0.9f, 0.9f, 0.5f);
	}
	jelly_faces( const jelly_faces& );
	jelly_faces & operator = (const jelly_faces &);

};

jelly_faces& ps_initializer_jelly_faces = jelly_faces::instance();
