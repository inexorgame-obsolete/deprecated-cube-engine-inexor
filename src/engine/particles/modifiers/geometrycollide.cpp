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
		physent d;
		d.type = ENT_BOUNCE;
		d.state = CS_ALIVE;
		d.o = vec(p_inst->o);
		d.vel = vec(p_inst->vel);
		d.collidetype = COLLIDE_ELLIPSE_PRECISE;
		d.radius = d.xradius = d.yradius = d.eyeheight = d.aboveeye = 1.5f;
		if (collide(&d, p_inst->vel, 0.5f, false))
		{
	        game::bounced(&d, collidewall);
	        float c = collidewall.dot(d.vel);
	        float k = 1.0f + (1.0f - elasticity)*c/d.vel.magnitude();
	        // conoutf("c: %2.2f k: %2.2f", c, k);
	        d.vel.mul(k);
	        d.vel.sub(vec(collidewall).mul(elasticity*2.0f*c));
			// conoutf("particle collide: vel(%2.2f,%2.2f,%2.2f) -> vel(%2.2f,%2.2f,%2.2f)", p_inst->vel.x, p_inst->vel.y, p_inst->vel.z, d.vel.x, d.vel.y, d.vel.z);
	        p_inst->vel = vec(d.vel);
		}
	}

	inline void modify(particle_modifier_instance *pm_inst, int elapsedtime) { }

	inline void modify(int elapsedtime) { }

	inline void init(particle_instance *p_inst) { }

private:

	float elasticity;

	geometry_collide() : particle_modifier_implementation("geometry_collide") {
		ps.particle_modifier_implementations.push_back(this);
		elasticity = 0.95f;
	}
	geometry_collide( const geometry_collide& );
	geometry_collide & operator = (const geometry_collide &);

};

geometry_collide& ps_modifier_geometry_collide = geometry_collide::instance();
