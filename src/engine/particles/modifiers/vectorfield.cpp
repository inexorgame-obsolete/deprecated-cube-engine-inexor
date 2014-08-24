#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a 3D/2D vector field.
 */
struct vector_field : public particle_modifier_implementation
{

public:

	static vector_field& instance()
	{
		static vector_field _instance;
		return _instance;
	}
	virtual ~vector_field() { }

	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		ix = p_inst->o.x - pm_inst->o.x;
		iy = p_inst->o.y - pm_inst->o.y;
		iz = p_inst->o.z - pm_inst->o.z;
		try {
			mu::value_type *v = parser.Eval(args);
			p_inst->o.x = v[0];
			p_inst->o.y = v[1];
			p_inst->o.z = v[2];
			conoutf("ix: %2.2f iy: %2.2f iz: %2.2f ox: %2.2f oy: %2.2f oz: %2.2f", ix, iy, iz, v[0], v[1], v[2]);
			// parser.Eval();
		} catch (mu::Parser::exception_type &e) {
			conoutf("Error parsing vector field expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

private:

	float time_factor;
	float ix;
	float iy;
	float iz;
	int args;
	mu::Parser parser;
	std::string expression;

	vector_field() : particle_modifier_implementation("vector_field") {
		ps.add_modifier_implementation(this);
		time_factor = 0.0f;
		args = 3;
		ix = 0;
		iy = 0;
		iz = 0;
		parser.DefineVar("x", &ix);
		parser.DefineVar("y", &iy);
		parser.DefineVar("z", &iz);
		// parser.SetExpr("y,x,z");
		expression = "y,x,z";
		parser.SetExpr(expression);
	}
	vector_field( const vector_field& );
	vector_field & operator = (const vector_field &);

};

vector_field& ps_modifier_vector_field = vector_field::instance();
