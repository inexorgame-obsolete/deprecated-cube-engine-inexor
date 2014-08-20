#include "cube.h"
#include "particles/particles.h"

struct ptest
{

	ptest()
    {
    }

	void setup(int setup)
	{
		switch (setup) {
			case 1: setup1(); break;
			case 2: setup2(); break;
			case 3: setup3(); break;
			case 4: setup4(); break;
			case 5: setup5(); break;
			case 6: setup6(); break;
			case 7: setup7(); break;
			case 8: setup8(); break;
			case 9: setup9(); break;
			case 10: setup10(); break;
			case 11: setup11(); break;
			case 12: setup12(); break;
			case 13: setup13(); break;
		}
	}

	void setup1()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 30000;
		int rate = 1;

		particle_renderer_type* pr_type_ball = ps.add_particle_renderer_type("ball_renderer", "packages/particles/ball1.png", "shader", vec4(255.0f, 255.0f, 0.0f, 0.3f), "billboard_renderer");
		particle_renderer_instance* pr_inst_fire = pr_type_ball->create_instance("fire");
		particle_type* p_type_fire = ps.add_particle_type("fire", "fire");
		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_randomv = ps.add_particle_modifier_type("randomv", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();
		particle_emitter_type* pe_point_fire_type = ps.add_particle_emitter_type("fire_point_emitter", "fire", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_1 = pe_point_fire_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(-40.0f, 0.0f, 0.0f));
		pe_inst_point_1->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_1->add_modifier(pm_inst_randomv);
    }

	void setup2()
    {
		float mass = 1.0f;
		float density = 1.0f;
		// int lifetime1 = 3500;
		// int rate1 = 1;
		int lifetime2 = 10000;
		int rate2 = 10;

		int lifetime3 = 500;
		int rate3 = 20;

		float density4 = 5.0f;
		int lifetime4 = 500;
		int rate4 = 10;

		/** Renderer types and instances **/

		particle_renderer_type* pr_type_cube = ps.add_particle_renderer_type("cube_renderer", "packages/particles/flare.jpg", "shader", vec4(255.0f, 255.0f, 255.0f, 0.9f), "cube_renderer");

		particle_renderer_type* pr_type_ball = ps.add_particle_renderer_type("ball_renderer", "packages/particles/ball1.png", "shader", vec4(255.0f, 255.0f, 255.0f, 0.3f), "billboard_renderer");
		pr_type_ball->attributes["size"] = 20.0f;

		particle_renderer_type* pr_type_smoke = ps.add_particle_renderer_type("smoke_renderer", "<grey>packages/particles/smoke.png", "shader", vec4(255.0f, 220.0f, 220.0f, 0.1f), "billboard_renderer");
		pr_type_smoke->attributes["size"] = 75.0f;

		particle_renderer_instance* pr_inst_fire = pr_type_ball->create_instance("fire");
		pr_inst_fire->color.r = 200.0f;
		pr_inst_fire->color.b = 0.0f;

		particle_renderer_instance* pr_inst_poison = pr_type_ball->create_instance("poison");
		pr_inst_poison->color.r = 0.0f;
		pr_inst_poison->color.b = 200.0f;

		particle_renderer_instance* pr_inst_smoke = pr_type_smoke->create_instance("smoke");

		particle_renderer_instance* pr_inst_cube = pr_type_cube->create_instance("cube");
		pr_inst_cube->color.g = 100.0f;

		/** Particle types **/

		particle_type* p_type_fire = ps.add_particle_type("fire", "fire");
		particle_type* p_type_poison = ps.add_particle_type("poison", "poison");
		particle_type* p_type_smoke = ps.add_particle_type("smoke", "smoke");
		particle_type* p_type_cube = ps.add_particle_type("cube", "cube");

		/** Modifier types and instances **/

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_randomv = ps.add_particle_modifier_type("randomv", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();

		particle_modifier_type* pm_type_randomw = ps.add_particle_modifier_type("randomw", "randomw");
		particle_modifier_instance* pm_inst_randomw = pm_type_randomw->create_instance();

		particle_modifier_type* pm_type_gravity_point = ps.add_particle_modifier_type("gravity_point", "gravity_point");
		pm_type_gravity_point->attributes["mass"] = 1000.0f;
		pm_type_gravity_point->attributes["gravity"] = 0.8f;
		particle_modifier_instance* pm_inst_gravity_point_1 = pm_type_gravity_point->create_instance(vec(768.0f, 768.0f, 532.0f));
		particle_modifier_instance* pm_inst_gravity_point_2 = pm_type_gravity_point->create_instance(vec(256.0f, 256.0f, 532.0f));
		particle_modifier_instance* pm_inst_gravity_point_3 = pm_type_gravity_point->create_instance(vec(768.0f, 256.0f, 532.0f));
		particle_modifier_instance* pm_inst_gravity_point_4 = pm_type_gravity_point->create_instance(vec(256.0f, 768.0f, 532.0f));

		particle_modifier_type* pm_type_black_hole = ps.add_particle_modifier_type("black_hole", "black_hole");
		pm_type_black_hole->attributes["mass"] = 5000.0f;
		pm_type_black_hole->attributes["gravity"] = 1.8f;

		particle_modifier_instance* pm_inst_black_hole = pm_type_black_hole->create_instance(vec(768.0f, 768.0f, 532.0f));

		/** Emitter types and instances **/

		particle_emitter_type* pe_point_fire_type = ps.add_particle_emitter_type("fire_point_emitter", "fire", mass, density, lifetime2, rate2, "point_emitter");
		particle_emitter_instance* pe_inst_point_1 = pe_point_fire_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(-40.0f, 0.0f, 0.0f));
		particle_emitter_instance* pe_inst_point_2 = pe_point_fire_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, -40.0f, 0.0f));

		particle_emitter_type* pe_point_poison_type = ps.add_particle_emitter_type("poison_point_emitter", "poison", mass, density, lifetime2, rate2, "point_emitter");
		particle_emitter_instance* pe_inst_point_3 = pe_point_poison_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(40.0f, 0.0f, 0.0f));
		particle_emitter_instance* pe_inst_point_4 = pe_point_poison_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 40.0f, 0.0f));

		particle_emitter_type* pe_type_smoke_field = ps.add_particle_emitter_type("smoke_field_emitter", "smoke", mass, density, lifetime3, rate3, "field_emitter");
		pe_type_smoke_field->attributes["grid_size_x"] = 3.0f;
		pe_type_smoke_field->attributes["grid_size_y"] = 3.0f;
		pe_type_smoke_field->attributes["grid_size_z"] = 3.0f;
		pe_type_smoke_field->attributes["grid_dist"] = 20.0f;
		particle_emitter_instance* pe_inst_smoke_field = pe_type_smoke_field->create_instance(vec(768.0f, 768.0f, 514.0f), vec(0.0f, 0.0f, 10.0f));

		particle_emitter_type* pe_type_cube_field = ps.add_particle_emitter_type("cube_field_emitter", "cube", mass, density4, lifetime4, rate4, "field_emitter");
		pe_type_cube_field->attributes["grid_size_x"] = 6.0f;
		pe_type_cube_field->attributes["grid_size_y"] = 6.0f;
		pe_type_cube_field->attributes["grid_size_z"] = 1.0f;
		pe_type_cube_field->attributes["grid_dist"] = 20.0f;
		particle_emitter_instance* pe_inst_cube_field = pe_type_cube_field->create_instance(vec(256.0f, 256.0f, 514.0f), vec(0.0f, 0.0f, 70.0f));

		/** Connect emitters and modifiers **/

		pe_inst_point_1->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_2->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_3->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_4->add_modifier(pm_inst_velocity_transformation);
		pe_inst_smoke_field->add_modifier(pm_inst_velocity_transformation);
		pe_inst_cube_field->add_modifier(pm_inst_velocity_transformation);

		pe_inst_point_1->add_modifier(pm_inst_randomv);
		pe_inst_point_2->add_modifier(pm_inst_randomv);
		pe_inst_point_3->add_modifier(pm_inst_randomv);
		pe_inst_point_4->add_modifier(pm_inst_randomv);
		pe_inst_smoke_field->add_modifier(pm_inst_randomw);
		pe_inst_cube_field->add_modifier(pm_inst_randomv);

		pe_inst_point_1->add_modifier(pm_inst_gravity_point_1);
		pe_inst_point_2->add_modifier(pm_inst_gravity_point_2);
		pe_inst_point_3->add_modifier(pm_inst_gravity_point_3);
		pe_inst_point_4->add_modifier(pm_inst_gravity_point_4);

		pe_inst_smoke_field->add_modifier(pm_inst_black_hole);

		// pe_inst_cube_field->add_modifier(pm_inst_black_hole);
    }

	void setup3()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 1000;
		int rate = 1;

		particle_renderer_type* pr_type_ball = ps.add_particle_renderer_type("ball_renderer", "packages/particles/ball1.png", "shader", vec4(255.0f, 255.0f, 0.0f, 0.3f), "billboard_renderer");
		pr_type_ball->attributes["size"] = 100.0f;
		particle_renderer_instance* pr_inst_fire = pr_type_ball->create_instance("fire");
		particle_type* p_type_fire = ps.add_particle_type("fire", "fire");
		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_randomv = ps.add_particle_modifier_type("randomv", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();
		particle_modifier_type* pm_type_velocity_damper = ps.add_particle_modifier_type("velocity_damper", "velocity_damper");
		particle_modifier_instance* pm_inst_velocity_damper = pm_type_velocity_damper->create_instance(vec(0.01f, 0.02f, 0.1f));
		// pm_inst_velocity_damper->attributes["damper"] = 0.999f;
		particle_emitter_type* pe_sphere_fire_type = ps.add_particle_emitter_type("sphere_point_emitter", "fire", mass, density, lifetime, rate, "sphere_emitter");
		particle_emitter_instance* pe_inst_sphere_1 = pe_sphere_fire_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(1.0f, 5.0f, 200.0f));
		pe_inst_sphere_1->add_modifier(pm_inst_velocity_transformation);
		pe_inst_sphere_1->add_modifier(pm_inst_velocity_damper);
		pe_inst_sphere_1->add_modifier(pm_inst_randomv);
    }

	void setup4()
    {
		float mass = 1.0f;
		float density = 5.0f;
		int lifetime = 20000;
		int rate = 900;

		particle_renderer_type* pr_type_spring = ps.add_particle_renderer_type("spring_renderer_4", "packages/particles/flare.jpg", "shader", vec4(255.0f, 255.0f, 255.0f, 0.3f), "spring_renderer");
		particle_renderer_instance* pr_inst_spring = pr_type_spring->create_instance("spring4");
		particle_type* p_type_cube = ps.add_particle_type("spring4", "spring4");

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_mass_spring_transformation = ps.add_particle_modifier_type("mass_spring_transformation", "mass_spring_transformation");
		particle_modifier_instance* pm_inst_mass_spring_transformation = pm_type_mass_spring_transformation->create_instance();

		particle_modifier_type* pm_type_gravity_point = ps.add_particle_modifier_type("gravity_point", "gravity_point");
		pm_type_gravity_point->attributes["mass"] = 1000.0f;
		pm_type_gravity_point->attributes["gravity"] = 5.0f;
		particle_modifier_instance* pm_inst_gravity_point_1 = pm_type_gravity_point->create_instance(vec(768.0f, 768.0f, 832.0f));

		particle_modifier_type* pm_type_gravity_point_2 = ps.add_particle_modifier_type("gravity_point_2", "gravity_point");
		pm_type_gravity_point_2->attributes["mass"] = 2000.0f;
		pm_type_gravity_point_2->attributes["gravity"] = 10.0f;
		particle_modifier_instance* pm_inst_gravity_point_2 = pm_type_gravity_point_2->create_instance(vec(512.0f, 512.0f, 1000.0f));

		particle_modifier_type* pm_type_bb_culling = ps.add_particle_modifier_type("bb_culling", "bb_culling");
		particle_modifier_instance* pm_inst_bb_culling = pm_type_bb_culling->create_instance(vec(1024.0f, 1024.0f, 1024.0f));

		particle_emitter_type* pe_type_fire_field = ps.add_particle_emitter_type("fire_field_emitter", "spring4", mass, density, lifetime, rate, "field_emitter");
		pe_type_fire_field->attributes["grid_size_x"] = 5.0f;
		pe_type_fire_field->attributes["grid_size_y"] = 5.0f;
		pe_type_fire_field->attributes["grid_size_z"] = 1.0f;
		pe_type_fire_field->attributes["grid_dist"] = 50.0f;
		particle_emitter_instance* pe_inst_fire_field = pe_type_fire_field->create_instance(vec(768.0f, 768.0f, 514.0f), vec(0.0f, 0.0f, 50.0f));
		pe_inst_fire_field->add_modifier(pm_inst_velocity_transformation);
		pe_inst_fire_field->add_modifier(pm_inst_mass_spring_transformation);
		pe_inst_fire_field->add_modifier(pm_inst_gravity_point_2);
		pe_inst_fire_field->add_modifier(pm_inst_bb_culling);
    }

	void setup5()
    {
		float mass = 1.0f;
		float density = 5.0f;
		int lifetime = 20000;
		int rate = 900;

		particle_renderer_type* pr_type_primary = ps.add_particle_renderer_type("primary_renderer", "packages/particles/ball1.png", "shader", vec4(255.0f, 128.0f, 0.0f, 0.7f), "billboard_renderer");
		pr_type_primary->attributes["size"] = 30.0f;
		particle_renderer_instance* pr_inst_primary = pr_type_primary->create_instance("primary");
		particle_type* p_type_primary = ps.add_particle_type("primary", "primary");

		particle_renderer_type* pr_type_satellite = ps.add_particle_renderer_type("satellite_renderer", "packages/particles/ball1.png", "shader", vec4(255.0f, 0.0f, 0.0f, 0.3f), "billboard_renderer");
		pr_type_satellite->attributes["size"] = 10.0f;
		particle_renderer_instance* pr_inst_satellite = pr_type_satellite->create_instance("satellite");
		particle_type* p_type_satellite = ps.add_particle_type("satellite", "satellite");

		particle_renderer_type* pr_type_spring = ps.add_particle_renderer_type("spring_renderer_5", "packages/particles/flare.jpg", "shader", vec4(255.0f, 255.0f, 255.0f, 0.3f), "spring_renderer");
		particle_renderer_instance* pr_inst_spring = pr_type_spring->create_instance("spring5");
		particle_type* p_type_cube = ps.add_particle_type("spring5", "spring5");

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_mass_spring_transformation = ps.add_particle_modifier_type("mass_spring_transformation", "mass_spring_transformation");
		particle_modifier_instance* pm_inst_mass_spring_transformation = pm_type_mass_spring_transformation->create_instance();

		particle_modifier_type* pm_type_gravity_point_5 = ps.add_particle_modifier_type("gravity_point_5", "gravity_point");
		pm_type_gravity_point_5->attributes["mass"] = 5000.0f;
		pm_type_gravity_point_5->attributes["gravity"] = 10.0f;
		particle_modifier_instance* pm_inst_gravity_point = pm_type_gravity_point_5->create_instance(vec(512.0f, 512.0f, 1000.0f));

		particle_modifier_type* pm_type_global_gravity_5 = ps.add_particle_modifier_type("global_gravity_5", "global_gravity");
		pm_type_global_gravity_5->attributes["mass"] = 250.0f;
		pm_type_global_gravity_5->attributes["gravity"] = 1.0f;
		particle_modifier_instance* pm_inst_global_gravity_5 = pm_type_global_gravity_5->create_instance(vec(0.0f, 0.0f, 400.0f));

		particle_modifier_type* pm_type_geometry_collide_5 = ps.add_particle_modifier_type("geometry_collide_5", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide_5 = pm_type_geometry_collide_5->create_instance();
		pm_inst_geometry_collide_5->attributes["elasticity"] = 0.8f;

		particle_emitter_type* pe_type_ball_satellite = ps.add_particle_emitter_type("ball_satellite_emitter", "satellite", mass, density, lifetime, rate, "satellite_emitter");
		pe_type_ball_satellite->attributes["grid_size_x"] = 5.0f;
		pe_type_ball_satellite->attributes["grid_size_y"] = 5.0f;
		pe_type_ball_satellite->attributes["grid_size_z"] = 1.0f;
		pe_type_ball_satellite->attributes["grid_dist"] = 50.0f;
		particle_emitter_instance* pe_inst_ball_satellite = pe_type_ball_satellite->create_instance(vec(768.0f, 768.0f, 514.0f), vec(0.0f, 0.0f, 150.0f));
		pe_inst_ball_satellite->add_modifier(pm_inst_velocity_transformation);
		pe_inst_ball_satellite->add_modifier(pm_inst_mass_spring_transformation);
		pe_inst_ball_satellite->add_modifier(pm_inst_gravity_point);
		pe_inst_ball_satellite->add_modifier(pm_inst_global_gravity_5);
		pe_inst_ball_satellite->add_modifier(pm_inst_geometry_collide_5);

		// noop emitter, just to enable
		particle_emitter_type* pe_type_noop_spring = ps.add_particle_emitter_type("noop_emitter", "spring_renderer_5", mass, density, 0, 0, "noop_emitter");
		particle_emitter_instance* pe_inst_noop_spring = pe_type_noop_spring->create_instance(vec(256.0f, 256.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
    }

	void setup6()
    {
		float mass = 1.0f;
		float density = 250.0f;
		int lifetime = 10000;
		int rate = 75;

		particle_renderer_type* pr_type_spring = ps.add_particle_renderer_type("spring_renderer_6", "packages/particles/flare.jpg", "shader", vec4(255.0f, 255.0f, 255.0f, 0.3f), "spring_renderer");
		particle_renderer_instance* pr_inst_spring = pr_type_spring->create_instance("spring6");
		particle_type* p_type_spring = ps.add_particle_type("spring6", "spring6");

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_mass_spring_transformation = ps.add_particle_modifier_type("mass_spring_transformation", "mass_spring_transformation");
		particle_modifier_instance* pm_inst_mass_spring_transformation = pm_type_mass_spring_transformation->create_instance();

		particle_modifier_type* pm_type_geometry_collide_6 = ps.add_particle_modifier_type("geometry_collide_6", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide_6 = pm_type_geometry_collide_6->create_instance();
		pm_inst_geometry_collide_6->attributes["elasticity"] = 0.8f;

		particle_emitter_type* pe_type_cloth_emitter = ps.add_particle_emitter_type("spring_cloth_emitter", "spring6", mass, density, lifetime, rate, "cloth_emitter");
		particle_emitter_instance* pe_inst_cloth_emitter = pe_type_cloth_emitter->create_instance(vec(0.0f, 100.0f, 1750.0f), vec(0.0f, 0.0f, -100.0f));
		pe_inst_cloth_emitter->add_modifier(pm_inst_velocity_transformation);
		pe_inst_cloth_emitter->add_modifier(pm_inst_mass_spring_transformation);
		pe_inst_cloth_emitter->add_modifier(pm_inst_geometry_collide_6);
    }

	void setup7()
    {
		float mass = 5.0f;
		float density = 250.0f;
		int lifetime = 5000;
		int rate = 10;

		particle_renderer_type* pr_type_fire_ball = ps.add_particle_renderer_type("fire_ball_7", "media/particle/shockwave01.png", "shader", vec4(255.0f, 255.0f, 0.0f, 0.1f), "billboard_renderer");
		pr_type_fire_ball->attributes["size"] = 45.0f;
		particle_renderer_instance* pr_inst_fire_ball = pr_type_fire_ball->create_instance("fire_ball_7");
		particle_type* p_type_fire_ball = ps.add_particle_type("fire_ball_7", "fire_ball_7");

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

/*
		particle_modifier_type* pm_type_global_gravity_7 = ps.add_particle_modifier_type("global_gravity_7", "global_gravity");
		pm_type_global_gravity_7->attributes["mass"] = 450.0f;
		pm_type_global_gravity_7->attributes["gravity"] = 3.0f;
		particle_modifier_instance* pm_inst_global_gravity_7 = pm_type_global_gravity_7->create_instance(vec(0.0f, 0.0f, 400.0f));
*/
		particle_modifier_type* pm_type_simple_gravity = ps.add_particle_modifier_type("global_gravity_10", "simple_gravity");
		particle_modifier_instance* pm_inst_simple_gravity = pm_type_simple_gravity->create_instance(vec(0.0f, 0.0f, 0.0f));

		particle_modifier_type* pm_type_geometry_collide_7 = ps.add_particle_modifier_type("geometry_collide_7", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide_7 = pm_type_geometry_collide_7->create_instance();
		pm_inst_geometry_collide_7->attributes["elasticity"] = 0.8f;

		particle_modifier_type* pm_type_randomv_7 = ps.add_particle_modifier_type("randomv_7", "randomv");
		particle_modifier_instance* pm_inst_randomv_7 = pm_type_randomv_7->create_instance();

		particle_emitter_type* pe_type_fire_ball_7 = ps.add_particle_emitter_type("fire_ball_emitter_7", "fire_ball_7", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_fire_ball_7 = pe_type_fire_ball_7->create_instance(vec(512.0f, 512.0f, 400.0f), vec(1.0f, 1.0f, 3.0f));
		pe_inst_fire_ball_7->add_modifier(pm_inst_velocity_transformation);
		pe_inst_fire_ball_7->add_modifier(pm_inst_simple_gravity);
		pe_inst_fire_ball_7->add_modifier(pm_inst_geometry_collide_7);
		pe_inst_fire_ball_7->add_modifier(pm_inst_randomv_7);
    }

	void setup8()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime2 = 10000;
		int rate2 = 10;
		particle_renderer_type* pr_type_cube = ps.add_particle_renderer_type("cube_renderer", "packages/particles/flare.jpg", "shader", vec4(255.0f, 255.0f, 255.0f, 0.9f), "cube_renderer");
		particle_renderer_instance* pr_inst_cube = pr_type_cube->create_instance("cube");
		pr_inst_cube->color.g = 100.0f;
		particle_type* p_type_cube = ps.add_particle_type("cube", "cube");
		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_randomv = ps.add_particle_modifier_type("randomv", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();
		particle_modifier_type* pm_type_geometry_collide_7 = ps.add_particle_modifier_type("geometry_collide_7", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide_7 = pm_type_geometry_collide_7->create_instance();
		pm_inst_geometry_collide_7->attributes["elasticity"] = 0.8f;
		particle_emitter_type* pe_point_poison_type = ps.add_particle_emitter_type("cube_field_emitter", "cube", mass, density, lifetime2, rate2, "point_emitter");
		particle_emitter_instance* pe_inst_point_3 = pe_point_poison_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(40.0f, 0.0f, 0.0f));
		pe_inst_point_3->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_3->add_modifier(pm_inst_randomv);
		pe_inst_point_3->add_modifier(pm_inst_geometry_collide_7);
    }

	void setup9()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 30000;
		int rate = 10;

		particle_renderer_type* pr_type_snow = ps.add_particle_renderer_type("snow_renderer_9", "packages/particles/smoke.png", "shader", vec4(255.0f, 255.0f, 255.0f, 0.3f), "billboard_renderer");
		pr_type_snow->attributes["size"] = 30.0f;
		particle_renderer_instance* pr_inst_snow = pr_type_snow->create_instance("snow_9");
		particle_type* p_type_snow = ps.add_particle_type("snow_9", "snow_9");
		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_randomv = ps.add_particle_modifier_type("randomv_9", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();
		particle_modifier_type* pm_type_velocity_damper = ps.add_particle_modifier_type("velocity_damper_9", "velocity_damper");
		particle_modifier_instance* pm_inst_velocity_damper = pm_type_velocity_damper->create_instance(vec(0.01f, 0.02f, 0.1f));
		particle_modifier_type* pm_type_wind = ps.add_particle_modifier_type("wind_9", "wind");
		particle_modifier_instance* pm_inst_wind = pm_type_wind->create_instance();
		pm_inst_wind->vel = vec(0.8f, 0.4f, 0.0f);
		particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_9", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
		pm_inst_geometry_collide->attributes["elasticity"] = 0.8f;
		particle_modifier_type* pm_type_gravity_point = ps.add_particle_modifier_type("gravity_point_9", "gravity_point");
		pm_type_gravity_point->attributes["mass"] = 5000.0f;
		pm_type_gravity_point->attributes["gravity"] = -30.0f;
		particle_modifier_instance* pm_inst_gravity_point = pm_type_gravity_point->create_instance(vec(1024.0f, 1024.0f, 550.0f));

		particle_emitter_type* pe_box_snow_type = ps.add_particle_emitter_type("box_emitter_9", "snow_9", mass, density, lifetime, rate, "box_emitter");
		pe_box_snow_type->density = 600.0f;
		particle_emitter_instance* pe_inst_box_snow = pe_box_snow_type->create_instance(vec(1024.0f, 1024.0f, 800.0f), vec(0.0f, 0.0f, -25.0f));
		pe_inst_box_snow->add_modifier(pm_inst_velocity_transformation);
		pe_inst_box_snow->add_modifier(pm_inst_velocity_damper);
		pe_inst_box_snow->add_modifier(pm_inst_wind);
		pe_inst_box_snow->add_modifier(pm_inst_geometry_collide);
		pe_inst_box_snow->add_modifier(pm_inst_gravity_point);
    }

	void setup10()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 10000;
		int rate = 100;

		float mass_fog = 0.5f;
		float density_fog = 1.0f;
		int lifetime_fog = 10000;
		int rate_fog = 5;
		float size_fog = 15.0f;

		particle_renderer_type* pr_type_grendade = ps.add_particle_renderer_type("grenade_renderer", "projectiles/grenade", "shader", vec4(0.0f, 0.0f, 0.0f, 0.0f), "model_renderer");
		particle_renderer_instance* pr_inst_snow = pr_type_grendade->create_instance("grendade_10");
		particle_type* p_type_grendade = ps.add_particle_type("grendade_10", "grendade_10");

		particle_renderer_type* pr_type_smoke = ps.add_particle_renderer_type("smoke_renderer", "<grey>packages/particles/smoke.png", "shader", vec4(220.0f, 220.0f, 128.0f, 0.2f), "billboard_renderer");
		pr_type_smoke->attributes["size"] = size_fog;
		particle_renderer_instance* pr_inst_smoke = pr_type_smoke->create_instance("smoke_10");
		particle_type* p_type_smoke = ps.add_particle_type("smoke_10", "smoke_10");


		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		// particle_modifier_type* pm_type_velocity_damper = ps.add_particle_modifier_type("velocity_damper_10", "velocity_damper");
		// particle_modifier_instance* pm_inst_velocity_damper = pm_type_velocity_damper->create_instance(vec(0.01f, 0.02f, 0.1f));
		particle_modifier_type* pm_type_wind = ps.add_particle_modifier_type("wind_10", "wind");
		particle_modifier_instance* pm_inst_wind = pm_type_wind->create_instance();
		pm_inst_wind->vel = vec(30.0f, 40.0f, 0.0f);
		particle_modifier_type* pm_type_simple_gravity = ps.add_particle_modifier_type("global_gravity_10", "simple_gravity");
		particle_modifier_instance* pm_inst_simple_gravity = pm_type_simple_gravity->create_instance(vec(0.0f, 0.0f, 0.0f));

		particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_10", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
		pm_inst_geometry_collide->attributes["elasticity"] = 0.75f;

		particle_modifier_type* pm_type_geometry_culling = ps.add_particle_modifier_type("geometry_culling_10", "geometry_culling");
		particle_modifier_instance* pm_inst_geometry_culling = pm_type_geometry_culling->create_instance();

		particle_modifier_type* pm_type_rolling = ps.add_particle_modifier_type("rolling_10", "rolling");
		particle_modifier_instance* pm_inst_rolling = pm_type_rolling->create_instance();

		particle_emitter_type* pe_type_box_grenade = ps.add_particle_emitter_type("box_grenade_emitter_10", "grendade_10", mass, density, lifetime, rate, "box_emitter");
		pe_type_box_grenade->density = 600.0f;
		particle_emitter_instance* pe_inst_box_grenade = pe_type_box_grenade->create_instance(vec(1024.0f, 1024.0f, 520.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_box_grenade->add_modifier(pm_inst_velocity_transformation);
		pe_inst_box_grenade->add_modifier(pm_inst_wind);
		pe_inst_box_grenade->add_modifier(pm_inst_simple_gravity);
		pe_inst_box_grenade->add_modifier(pm_inst_geometry_collide);
		pe_inst_box_grenade->add_modifier(pm_inst_rolling);

		particle_emitter_type* pe_type_box_fog = ps.add_particle_emitter_type("box_fog_emitter_10", "smoke_10", mass_fog, density_fog, lifetime_fog, rate_fog, "box_emitter");
		pe_type_box_fog->density = 600.0f;
		particle_emitter_instance* pe_inst_box_fog = pe_type_box_fog->create_instance(vec(1024.0f, 1024.0f, 520.0f), vec(0.0f, 0.0f, -20.0f));
		pe_inst_box_fog->add_modifier(pm_inst_velocity_transformation);
		pe_inst_box_fog->add_modifier(pm_inst_wind);
		pe_inst_box_fog->add_modifier(pm_inst_simple_gravity);
		pe_inst_box_fog->add_modifier(pm_inst_geometry_culling);
		// pe_inst_box_fog->add_modifier(pm_inst_geometry_collide);

    }

	void setup11()
    {
		float mass = 5.0f;
		float density = 1.0f;
		int lifetime = 20000;
		int rate = 50;

		particle_renderer_type* pr_type_grenade = ps.add_particle_renderer_type("grenade_renderer", "projectiles/grenade", "shader", vec4(0.0f, 0.0f, 0.0f, 0.0f), "model_renderer");
		particle_renderer_instance* pr_inst_grenade = pr_type_grenade->create_instance("grendade_11");
		pr_inst_grenade->offset = vec(0.0f, 0.0f, 2.0f);
		particle_type* p_type_grendade = ps.add_particle_type("grendade_11", "grendade_11");

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_wind = ps.add_particle_modifier_type("wind_11", "wind");
		particle_modifier_instance* pm_inst_wind = pm_type_wind->create_instance();
		pm_inst_wind->vel = vec(30.0f, 40.0f, 0.0f);

		particle_modifier_type* pm_type_simple_gravity = ps.add_particle_modifier_type("global_gravity_11", "simple_gravity");
		particle_modifier_instance* pm_inst_simple_gravity = pm_type_simple_gravity->create_instance(vec(0.0f, 0.0f, 0.0f));

		particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_11", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
		pm_inst_geometry_collide->attributes["elasticity"] = 0.75f;

		particle_modifier_type* pm_type_rolling = ps.add_particle_modifier_type("rolling_11", "rolling");
		particle_modifier_instance* pm_inst_rolling = pm_type_rolling->create_instance();

		particle_emitter_type* pe_type_box_grenade = ps.add_particle_emitter_type("box_grenade_emitter_11", "grendade_11", mass, density, lifetime, rate, "box_emitter");
		pe_type_box_grenade->density = 600.0f;

		particle_emitter_instance* pe_inst_box_grenade = pe_type_box_grenade->create_instance(vec(100.0f, 100.0f, 520.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_box_grenade->add_modifier(pm_inst_velocity_transformation);
		pe_inst_box_grenade->add_modifier(pm_inst_wind);
		pe_inst_box_grenade->add_modifier(pm_inst_simple_gravity);
		pe_inst_box_grenade->add_modifier(pm_inst_geometry_collide);
		pe_inst_box_grenade->add_modifier(pm_inst_rolling);
    }

	void setup12()
    {
		float mass = 5.0f;
		float density = 1.0f;
		int lifetime = 20000;
		int rate = 10;

		particle_renderer_type* pr_type_grenade = ps.add_particle_renderer_type("grenade_renderer", "projectiles/rocket", "shader", vec4(0.0f, 0.0f, 0.0f, 0.0f), "model_renderer");
		particle_renderer_instance* pr_inst_grenade = pr_type_grenade->create_instance("grendade_12");
		pr_inst_grenade->offset = vec(0.0f, 0.0f, 2.0f);
		particle_type* p_type_grendade = ps.add_particle_type("grendade_12", "grendade_12");

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_12", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
		pm_inst_geometry_collide->attributes["elasticity"] = 0.75f;

		particle_modifier_type* pm_type_rolling = ps.add_particle_modifier_type("rolling_12", "rolling");
		particle_modifier_instance* pm_inst_rolling = pm_type_rolling->create_instance();

		particle_modifier_type* pm_type_gravity_point_a = ps.add_particle_modifier_type("gravity_point_12a", "pulsar");
		pm_type_gravity_point_a->attributes["mass"] = 1000.0f;
		pm_type_gravity_point_a->attributes["gravity"] = 5.0f;
		particle_modifier_instance* pm_inst_gravity_point_a = pm_type_gravity_point_a->create_instance(vec(256.0f, 512.0f, 390.0f));

		particle_modifier_type* pm_type_gravity_point_b = ps.add_particle_modifier_type("gravity_point_12b", "pulsar");
		pm_type_gravity_point_b->attributes["mass"] = 1000.0f;
		pm_type_gravity_point_b->attributes["gravity"] = 5.0f;
		particle_modifier_instance* pm_inst_gravity_point_b = pm_type_gravity_point_b->create_instance(vec(768.0f, 512.0f, 390.0f));

		particle_modifier_type* pm_type_gravity_point_c = ps.add_particle_modifier_type("gravity_point_12c", "pulsar");
		pm_type_gravity_point_c->attributes["mass"] = 1000.0f;
		pm_type_gravity_point_c->attributes["gravity"] = 5.0f;
		particle_modifier_instance* pm_inst_gravity_point_c = pm_type_gravity_point_c->create_instance(vec(512.0f, 256.0f, 390.0f));

		particle_modifier_type* pm_type_gravity_point_d = ps.add_particle_modifier_type("gravity_point_12d", "pulsar");
		pm_type_gravity_point_d->attributes["mass"] = 1000.0f;
		pm_type_gravity_point_d->attributes["gravity"] = 5.0f;
		particle_modifier_instance* pm_inst_gravity_point_d = pm_type_gravity_point_d->create_instance(vec(512.0f, 768.0f, 390.0f));

		particle_modifier_type* pm_type_gravity_point_e = ps.add_particle_modifier_type("gravity_point_12e", "pulsar");
		pm_type_gravity_point_e->attributes["mass"] = 1000.0f;
		pm_type_gravity_point_e->attributes["gravity"] = -5.0f;
		particle_modifier_instance* pm_inst_gravity_point_e = pm_type_gravity_point_e->create_instance(vec(512.0f, 512.0f, 134.0f));

		particle_modifier_type* pm_type_gravity_point_f = ps.add_particle_modifier_type("gravity_point_12f", "pulsar");
		pm_type_gravity_point_f->attributes["mass"] = 1000.0f;
		pm_type_gravity_point_f->attributes["gravity"] = -5.0f;
		particle_modifier_instance* pm_inst_gravity_point_f = pm_type_gravity_point_f->create_instance(vec(512.0f, 512.0f, 646.0f));


		particle_modifier_type* pm_type_randomv = ps.add_particle_modifier_type("randomv_12", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();


		particle_emitter_type* pe_type_sphere_grenade = ps.add_particle_emitter_type("sphere_grenade_emitter_12", "grendade_12", mass, density, lifetime, rate, "sphere_emitter");

		particle_emitter_instance* pe_inst_sphere_grenade = pe_type_sphere_grenade->create_instance(vec(512.0f, 512.0f, 390.0f), vec(10.0f, 10.0f, 0.0f));
		pe_inst_sphere_grenade->add_modifier(pm_inst_velocity_transformation);
		pe_inst_sphere_grenade->add_modifier(pm_inst_gravity_point_a);
		pe_inst_sphere_grenade->add_modifier(pm_inst_gravity_point_b);
		pe_inst_sphere_grenade->add_modifier(pm_inst_gravity_point_c);
		pe_inst_sphere_grenade->add_modifier(pm_inst_gravity_point_d);
		pe_inst_sphere_grenade->add_modifier(pm_inst_geometry_collide);
		pe_inst_sphere_grenade->add_modifier(pm_inst_rolling);
		pe_inst_sphere_grenade->add_modifier(pm_inst_randomv);
    }

	void setup13()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 30000;
		int rate = 200;

		particle_renderer_type* pr_type_plasma = ps.add_particle_renderer_type("ball_renderer", "packages/particles/plasma.png", "shader", vec4(128.0f, 128.0f, 255.0f, 0.3f), "billboard_renderer");
		pr_type_plasma->attributes["size"] = 40.0f;
		particle_renderer_instance* pr_inst_plasma = pr_type_plasma->create_instance("plasma_13");
		particle_type* p_type_plasma = ps.add_particle_type("plasma_13", "plasma_13");
		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_13", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_13", "random_velocity");
		particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();
		particle_emitter_type* pe_type_point_plasma = ps.add_particle_emitter_type("plasma_point_emitter_13", "plasma_13", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_plasma = pe_type_point_plasma->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_plasma->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_plasma->add_initializer(pi_inst_random_velocity);
    }

};

ptest *ptest_inst = new ptest();

ICOMMAND(ptest, "i", (int *setup), ptest_inst->setup(*setup));
