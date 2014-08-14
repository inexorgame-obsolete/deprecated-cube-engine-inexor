#include "cube.h"
#include "engine/particles/particles.h"

/**
 * Singleton implementation of particle/geometry collision.
 */
struct geometry_collide : public particle_modifier_implementation
{

public:

	static geometry_collide& instance()
	{
		static geometry_collide _instance;
		return _instance;
	}
	virtual ~geometry_collide() { }

	/**
	 * Simulate a simple bouncer
	 */
	inline void modify(particle_modifier_instance *pm_inst, particle_instance *p_inst, int elapsedtime)
	{
		d.o = vec(p_inst->o);
		d.vel = vec(p_inst->vel);
		if (collide(&d, p_inst->vel, 0.5f, false))
		{
	        game::bounced(&d, collidewall);
	        float c = collidewall.dot(d.vel);
	        float m = d.vel.magnitude();
	        if (m == 0.0f) return;
	        float k = 1.0f + (1.0f - elasticity) * c / m;
	        d.vel.mul(k);
	        d.vel.sub(vec(collidewall).mul(elasticity * 2.0f * c));
	        p_inst->vel = vec(d.vel);
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	inline void init(particle_instance *p_inst) { }

private:

	physent d;
	float elasticity;

	geometry_collide() : particle_modifier_implementation("geometry_collide") {
		ps.particle_modifier_implementations.push_back(this);
		elasticity = 0.95f;
		d.type = ENT_BOUNCE;
		d.state = CS_ALIVE;
		d.collidetype = COLLIDE_ELLIPSE_PRECISE;
		d.radius = d.xradius = d.yradius = d.eyeheight = d.aboveeye = 1.5f;
	}
	geometry_collide( const geometry_collide& );
	geometry_collide & operator = (const geometry_collide &);

};

geometry_collide& ps_modifier_geometry_collide = geometry_collide::instance();
