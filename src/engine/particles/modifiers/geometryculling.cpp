#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of a geometry culling.
 */
struct geometry_culling : public particle_modifier_implementation
{

public:

	static geometry_culling& instance()
	{
		static geometry_culling _instance;
		return _instance;
	}
	virtual ~geometry_culling() { }

	/**
	 * Particles dies when colliding with the geometry.
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime) {
		d.o = vec(p_inst->o);
		d.vel = vec(p_inst->vel);
		// suppress collision check for mapmodels
		if (collide(&d, vec(p_inst->vel), 0.1f, false, false))
		{
			p_inst->remaining = 0;
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

//	inline void init(particle_instance *p_inst) { }

private:

	physent d;

	geometry_culling() : particle_modifier_implementation("geometry_culling") {
		ps.add_modifier_implementation(this);
		d.type = ENT_BOUNCE;
		d.state = CS_ALIVE;
		d.collidetype = COLLIDE_ELLIPSE_PRECISE;
		d.radius = d.xradius = d.yradius = d.eyeheight = d.aboveeye = 1.5f;
	}
	geometry_culling( const geometry_culling& );
	geometry_culling & operator = (const geometry_culling &);

};

geometry_culling& ps_modifier_geometry_culling = geometry_culling::instance();
