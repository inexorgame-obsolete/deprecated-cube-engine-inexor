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
			case 11: setup11(); break;
			case 12: setup12(); break;
			case 13: setup13(); break;
			case 14: setup14(); break;
			case 15: setup15(); break;
			case 16: setup16(); break;
			case 17: position_trace_modifier_test(); break;
			case 18: vector_field_test(); break;
			case 19: spring_weaver_test(); break;
		}
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

		particle_renderer_type* pr_type_sparkle = ps.add_particle_renderer_type("sparkle_renderer_11", "media/particle/flash01.png", "shader", vec4(0.0f, 128.0f, 196.0f, 0.3f), "billboard_renderer");
		pr_type_sparkle->attributes["size"] = 20.0f;
		particle_renderer_instance* pr_inst_sparkle = pr_type_sparkle->create_instance("sparkle_11");
		particle_type* p_type_sparkle = ps.add_particle_type("sparkle_11", pr_inst_sparkle);

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

		particle_modifier_type* pm_type_sub_emitter = ps.add_particle_modifier_type("sub_emitter_11", "sub_emitter");
		particle_modifier_instance* pm_inst_sub_emitter = pm_type_sub_emitter->create_instance();

		particle_initializer_type* pi_type_random_velocity_sub = ps.add_particle_initializer_type("random_velocity_17_sub", "random_velocity");
		pi_type_random_velocity_sub->attributes["osx"] = 100.0f;
		pi_type_random_velocity_sub->attributes["osy"] = 100.0f;
		pi_type_random_velocity_sub->attributes["osz"] = 100.0f;
		pi_type_random_velocity_sub->attributes["isx"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isy"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity_sub = pi_type_random_velocity_sub->create_instance();

		particle_emitter_type* pe_type_box_grenade = ps.add_particle_emitter_type("box_grenade_emitter_11", "grendade_11", mass, density, lifetime, rate, "cubic_emitter");
		pe_type_box_grenade->attributes["size_x"] = 1024.0f;
		pe_type_box_grenade->attributes["size_y"] = 1024.0f;
		pe_type_box_grenade->attributes["size_z"] = 0.0f;

		particle_emitter_instance* pe_inst_box_grenade = pe_type_box_grenade->create_instance(vec(0.0f, 0.0f, 1024.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_box_grenade->add_modifier(pm_inst_velocity_transformation);
		pe_inst_box_grenade->add_modifier(pm_inst_wind);
		pe_inst_box_grenade->add_modifier(pm_inst_simple_gravity);
		pe_inst_box_grenade->add_modifier(pm_inst_geometry_collide);
		pe_inst_box_grenade->add_modifier(pm_inst_rolling);
		pe_inst_box_grenade->add_modifier(pm_inst_sub_emitter);

		particle_emitter_type* pe_type_point_sub_sparkle = ps.add_particle_emitter_type("sub_sparkle_point_emitter_11", p_type_sparkle, mass, density, 200, 30, "point_emitter");
		particle_emitter_instance* pe_inst_point_sub_sparkle = pe_type_point_sub_sparkle->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_sub_sparkle->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_sub_sparkle->add_initializer(pi_inst_random_velocity_sub);

		pm_inst_sub_emitter->pointers["sub_emitter"] = pe_inst_point_sub_sparkle;

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
		particle_type* p_type_grendade = ps.add_particle_type("grendade_12", pr_inst_grenade);

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
		int lifetime = 10000;
		int rate = 50;

		particle_renderer_type* pr_type_shockwave = ps.add_particle_renderer_type("plasma_renderer_13", "media/particle/shockwave01.png", "shader", vec4(128.0f, 128.0f, 255.0f, 0.3f), "billboard_renderer");
		pr_type_shockwave->attributes["size"] = 40.0f;
		particle_renderer_instance* pr_inst_shockwave_1 = pr_type_shockwave->create_instance("shockwave_1");
		pr_inst_shockwave_1->color = vec4(0.0f, 192.0f, 255.0f, 0.1f);
		pr_inst_shockwave_1->attributes["size"] = 80.0f;
		particle_renderer_instance* pr_inst_shockwave_2 = pr_type_shockwave->create_instance("shockwave_2");
		pr_inst_shockwave_2->color = vec4(255.0f, 192.0f, 0.0f, 0.1f);
		pr_inst_shockwave_2->attributes["size"] = 40.0f;
		particle_renderer_instance* pr_inst_shockwave_3 = pr_type_shockwave->create_instance("shockwave_3");
		pr_inst_shockwave_3->color = vec4(192.0f, 255.0f, 0.0f, 0.1f);
		pr_inst_shockwave_3->attributes["size"] = 20.0f;
		particle_renderer_instance* pr_inst_shockwave_4 = pr_type_shockwave->create_instance("shockwave_4");
		pr_inst_shockwave_4->color = vec4(192.0f, 0.0f, 255.0f, 0.1f);
		pr_inst_shockwave_4->attributes["size"] = 60.0f;
		particle_renderer_instance* pr_inst_shockwave_5 = pr_type_shockwave->create_instance("shockwave_5");
		pr_inst_shockwave_5->color = vec4(0.0f, 0.0f, 255.0f, 0.1f);
		pr_inst_shockwave_5->attributes["size"] = 100.0f;

		particle_type* p_type_shockwave_1 = ps.add_particle_type("shockwave_13_1", pr_inst_shockwave_1);
		particle_type* p_type_shockwave_2 = ps.add_particle_type("shockwave_13_2", pr_inst_shockwave_2);
		particle_type* p_type_shockwave_3 = ps.add_particle_type("shockwave_13_3", pr_inst_shockwave_3);
		particle_type* p_type_shockwave_4 = ps.add_particle_type("shockwave_13_4", pr_inst_shockwave_4);
		particle_type* p_type_shockwave_5 = ps.add_particle_type("shockwave_13_5", pr_inst_shockwave_5);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_13", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_13", "random_velocity");
		pi_type_random_velocity->attributes["osx"] = 40.0f;
		pi_type_random_velocity->attributes["osy"] = 0.0f;
		pi_type_random_velocity->attributes["osz"] = 40.0f;
		pi_type_random_velocity->attributes["isx"] = 20.0f;
		pi_type_random_velocity->attributes["isy"] = 0.0f;
		pi_type_random_velocity->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();

		particle_initializer_type* pi_type_random_particle_type = ps.add_particle_initializer_type("random_particle_type_15", "random_particle_type");
		particle_initializer_instance* pi_inst_random_particle_type = pi_type_random_particle_type->create_instance();
		pi_inst_random_particle_type->particle_types.push_back(p_type_shockwave_1);
		pi_inst_random_particle_type->particle_types.push_back(p_type_shockwave_2);
		pi_inst_random_particle_type->particle_types.push_back(p_type_shockwave_3);
		pi_inst_random_particle_type->particle_types.push_back(p_type_shockwave_4);
		pi_inst_random_particle_type->particle_types.push_back(p_type_shockwave_5);

		particle_emitter_type* pe_type_point_plasma = ps.add_particle_emitter_type("plasma_point_emitter_13", "plasma_13", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_plasma = pe_type_point_plasma->create_instance(vec(512.0f, 512.0f, 350.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_plasma->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_plasma->add_initializer(pi_inst_random_velocity);
		pe_inst_point_plasma->add_initializer(pi_inst_random_particle_type);
    }

	void setup14()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 1000;
		int rate = 5;

		particle_renderer_type* pr_type_sparkle = ps.add_particle_renderer_type("sparkle_renderer_14", "media/particle/spark01.png", "shader", vec4(128.0f, 128.0f, 255.0f, 0.3f), "billboard_renderer");
		pr_type_sparkle->attributes["size"] = 60.0f;
		particle_renderer_instance* pr_inst_sparkle = pr_type_sparkle->create_instance("sparkle_14");

		particle_type* p_type_sparkle = ps.add_particle_type("sparkle_14", pr_inst_sparkle);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_14", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_geometry_culling = ps.add_particle_modifier_type("geometry_culling_14", "geometry_culling");
		particle_modifier_instance* pm_inst_geometry_culling = pm_type_geometry_culling->create_instance();

		particle_initializer_type* pi_type_random_position = ps.add_particle_initializer_type("random_position_14", "random_position");
		pi_type_random_position->attributes["osx"] = 0.0f;
		pi_type_random_position->attributes["osy"] = 0.0f;
		pi_type_random_position->attributes["osz"] = 50.0f;
		pi_type_random_position->attributes["isx"] = 0.0f;
		pi_type_random_position->attributes["isy"] = 0.0f;
		pi_type_random_position->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_position = pi_type_random_position->create_instance();
		particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_14", "random_velocity");
		pi_type_random_velocity->attributes["osx"] = 40.0f;
		pi_type_random_velocity->attributes["osy"] = 40.0f;
		pi_type_random_velocity->attributes["osz"] = 0.0f;
		pi_type_random_velocity->attributes["isx"] = 20.0f;
		pi_type_random_velocity->attributes["isy"] = 20.0f;
		pi_type_random_velocity->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();

		particle_emitter_type* pe_type_point_sparkle = ps.add_particle_emitter_type("sparkle_point_emitter_14", "sparkle_14", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_plasma = pe_type_point_sparkle->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_plasma->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_plasma->add_modifier(pm_inst_geometry_culling);
		pe_inst_point_plasma->add_initializer(pi_inst_random_position);
		pe_inst_point_plasma->add_initializer(pi_inst_random_velocity);
    }

	void setup15()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 1000;
		int rate = 10;

		particle_renderer_type* pr_type_flash = ps.add_particle_renderer_type("flash_renderer_15", "media/particle/flash01.png", "shader", vec4(255.0f, 0.0f, 0.0f, 0.2f), "billboard_renderer");
		pr_type_flash->attributes["size"] = 45.0f;
		particle_renderer_instance* pr_inst_flash_1 = pr_type_flash->create_instance("flash_15_1");
		particle_renderer_instance* pr_inst_flash_2 = pr_type_flash->create_instance("flash_15_2");
		pr_inst_flash_2->color = vec4(255.0f, 192.0f, 0.0f, 0.1f);

		particle_type* p_type_flash_1 = ps.add_particle_type("flash_15_1", pr_inst_flash_1);
		particle_type* p_type_flash_2 = ps.add_particle_type("flash_15_2", pr_inst_flash_2);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_15", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_geometry_culling = ps.add_particle_modifier_type("geometry_culling_15", "geometry_culling");
		particle_modifier_instance* pm_inst_geometry_culling = pm_type_geometry_culling->create_instance();

		particle_initializer_type* pi_type_random_position = ps.add_particle_initializer_type("random_position_15", "random_position");
		pi_type_random_position->attributes["osx"] = 10.0f;
		pi_type_random_position->attributes["osy"] = 10.0f;
		pi_type_random_position->attributes["osz"] = 0.0f;
		pi_type_random_position->attributes["isx"] = 5.0f;
		pi_type_random_position->attributes["isy"] = 5.0f;
		pi_type_random_position->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_position = pi_type_random_position->create_instance();
		particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_15", "random_velocity");
		pi_type_random_velocity->attributes["osx"] = 0.0f;
		pi_type_random_velocity->attributes["osy"] = 0.0f;
		pi_type_random_velocity->attributes["osz"] = 40.0f;
		pi_type_random_velocity->attributes["isx"] = 0.0f;
		pi_type_random_velocity->attributes["isy"] = 0.0f;
		pi_type_random_velocity->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();

		particle_initializer_type* pi_type_random_particle_type = ps.add_particle_initializer_type("random_particle_type_15", "random_particle_type");
		particle_initializer_instance* pi_inst_random_particle_type = pi_type_random_particle_type->create_instance();
		pi_inst_random_particle_type->particle_types.push_back(p_type_flash_1);
		pi_inst_random_particle_type->particle_types.push_back(p_type_flash_2);

		particle_emitter_type* pe_type_field_flash = ps.add_particle_emitter_type("flash_field_emitter_15", "flash_15_1", mass, density, lifetime, rate, "field_emitter");
		pe_type_field_flash->batch_size = 1;
		pe_type_field_flash->attributes["grid_size_x"] = 3.0f;
		pe_type_field_flash->attributes["grid_size_y"] = 3.0f;
		pe_type_field_flash->attributes["grid_size_z"] = 3.0f;
		pe_type_field_flash->attributes["grid_dist"] = 50.0f;

		particle_emitter_instance* pe_inst_field_flash = pe_type_field_flash->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_field_flash->add_modifier(pm_inst_velocity_transformation);
		pe_inst_field_flash->add_modifier(pm_inst_geometry_culling);
		pe_inst_field_flash->add_initializer(pi_inst_random_position);
		pe_inst_field_flash->add_initializer(pi_inst_random_velocity);
		pe_inst_field_flash->add_initializer(pi_inst_random_particle_type);
    }

	void setup16()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 3000;
		int rate = 10;

		particle_renderer_type* pr_type_base = ps.add_particle_renderer_type("base_renderer_16", "media/particle/base.png", "shader", vec4(255.0f, 0.0f, 255.0f, 0.4f), "billboard_renderer");
		pr_type_base->attributes["size"] = 120.0f;
		particle_renderer_instance* pr_inst_base_1 = pr_type_base->create_instance("base_16_1");

		particle_renderer_type* pr_type_blob = ps.add_particle_renderer_type("blob_renderer_16", "media/particle/blob.png", "shader", vec4(0.0f, 255.0f, 0.0f, 0.4f), "billboard_renderer");
		pr_type_blob->attributes["size"] = 60.0f;
		particle_renderer_instance* pr_inst_blob_1 = pr_type_blob->create_instance("blob_16_1");

		particle_type* p_type_base_1 = ps.add_particle_type("base_16_1", pr_inst_base_1);
		particle_type* p_type_blob_1 = ps.add_particle_type("blob_16_1", pr_inst_blob_1);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_16", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_geometry_culling = ps.add_particle_modifier_type("geometry_culling_16", "geometry_culling");
		particle_modifier_instance* pm_inst_geometry_culling = pm_type_geometry_culling->create_instance();

		particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_16", "random_velocity");
		pi_type_random_velocity->attributes["osx"] = 400.0f;
		pi_type_random_velocity->attributes["osy"] = 100.0f;
		pi_type_random_velocity->attributes["osz"] = 600.0f;
		pi_type_random_velocity->attributes["isx"] = 200.0f;
		pi_type_random_velocity->attributes["isy"] = 50.0f;
		pi_type_random_velocity->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();

		particle_initializer_type* pi_type_random_particle_type = ps.add_particle_initializer_type("random_particle_type_16", "random_particle_type");
		particle_initializer_instance* pi_inst_random_particle_type = pi_type_random_particle_type->create_instance();
		pi_inst_random_particle_type->particle_types.push_back(p_type_base_1);
		pi_inst_random_particle_type->particle_types.push_back(p_type_blob_1);

		particle_emitter_type* pe_type_box_dust = ps.add_particle_emitter_type("dust_cubic_emitter_16", p_type_base_1, mass, density, lifetime, rate, "cubic_emitter");
		pe_type_box_dust->attributes["size_x"] = 1024.0f;
		pe_type_box_dust->attributes["size_y"] = 1024.0f;
		pe_type_box_dust->attributes["size_z"] = 1.0f;

		particle_emitter_instance* pe_inst_box_dust = pe_type_box_dust->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_box_dust->add_modifier(pm_inst_velocity_transformation);
		pe_inst_box_dust->add_initializer(pi_inst_random_velocity);
		pe_inst_box_dust->add_initializer(pi_inst_random_particle_type);
    }

	void position_trace_modifier_test()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 1000;
		int rate = 5;

		particle_renderer_type* pr_type_sparkle = ps.add_particle_renderer_type("sparkle_renderer_17", "media/particle/flash01.png", "shader", vec4(128.0f, 128.0f, 0.0f, 0.3f), "billboard_renderer");
		pr_type_sparkle->attributes["size"] = 60.0f;
		particle_renderer_instance* pr_inst_sparkle_0 = pr_type_sparkle->create_instance("sparkle_17_0");
		pr_inst_sparkle_0->color = vec4(255.0f, 0.0f, 0.0f, 0.5f);
		pr_inst_sparkle_0->attributes["size"] = 30.0f;
		particle_renderer_instance* pr_inst_sparkle_1 = pr_type_sparkle->create_instance("sparkle_17_1");
		pr_inst_sparkle_1->color = vec4(0.0f, 128.0f, 255.0f, 0.6f);
		pr_inst_sparkle_1->attributes["size"] = 30.0f;
		particle_renderer_instance* pr_inst_sparkle_2 = pr_type_sparkle->create_instance("sparkle_17_2");
		pr_inst_sparkle_2->color = vec4(128.0f, 128.0f, 255.0f, 0.3f);
		pr_inst_sparkle_2->attributes["size"] = 40.0f;
		particle_renderer_instance* pr_inst_sparkle_3 = pr_type_sparkle->create_instance("sparkle_17_3");
		pr_inst_sparkle_3->color = vec4(128.0f, 0.0f, 255.0f, 0.9f);
		pr_inst_sparkle_3->attributes["size"] = 50.0f;

		particle_type* p_type_sparkle_0 = ps.add_particle_type("sparkle_17_0", pr_inst_sparkle_0);
		particle_type* p_type_sparkle_1 = ps.add_particle_type("sparkle_17_1", pr_inst_sparkle_1);
		particle_type* p_type_sparkle_2 = ps.add_particle_type("sparkle_17_2", pr_inst_sparkle_2);
		particle_type* p_type_sparkle_3 = ps.add_particle_type("sparkle_17_3", pr_inst_sparkle_3);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_17", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
		particle_modifier_type* pm_type_geometry_culling = ps.add_particle_modifier_type("geometry_culling_17", "geometry_culling");
		particle_modifier_instance* pm_inst_geometry_culling = pm_type_geometry_culling->create_instance();
		particle_modifier_type* pm_type_position_trace = ps.add_particle_modifier_type("position_trace_17", "position_trace");
		particle_modifier_instance* pm_inst_position_trace = pm_type_position_trace->create_instance();
		pm_inst_position_trace->attributes["rate"] = 25;
		pm_inst_position_trace->attributes["lifetime"] = 750;

		particle_modifier_type* pm_type_sub_emitter = ps.add_particle_modifier_type("sub_emitter_17", "sub_emitter");
		particle_modifier_instance* pm_inst_sub_emitter = pm_type_sub_emitter->create_instance();

		particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_17", "random_velocity");
		pi_type_random_velocity->attributes["osx"] = 100.0f;
		pi_type_random_velocity->attributes["osy"] = 100.0f;
		pi_type_random_velocity->attributes["osz"] = 50.0f;
		pi_type_random_velocity->attributes["isx"] = 50.0f;
		pi_type_random_velocity->attributes["isy"] = 50.0f;
		pi_type_random_velocity->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();

		particle_initializer_type* pi_type_random_velocity_sub = ps.add_particle_initializer_type("random_velocity_17_sub", "random_velocity");
		pi_type_random_velocity_sub->attributes["osx"] = 30.0f;
		pi_type_random_velocity_sub->attributes["osy"] = 30.0f;
		pi_type_random_velocity_sub->attributes["osz"] = 30.0f;
		pi_type_random_velocity_sub->attributes["isx"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isy"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity_sub = pi_type_random_velocity_sub->create_instance();

		particle_initializer_type* pi_type_random_particle_type = ps.add_particle_initializer_type("random_particle_type_17", "random_particle_type");
		particle_initializer_instance* pi_inst_random_particle_type = pi_type_random_particle_type->create_instance();
		pi_inst_random_particle_type->particle_types.push_back(p_type_sparkle_1);
		pi_inst_random_particle_type->particle_types.push_back(p_type_sparkle_2);
		pi_inst_random_particle_type->particle_types.push_back(p_type_sparkle_3);

		particle_emitter_type* pe_type_point_sparkle = ps.add_particle_emitter_type("sparkle_point_emitter_17", "sparkle_17_0", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_sparkle = pe_type_point_sparkle->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_sparkle->add_modifier(pm_inst_velocity_transformation);
		// pe_inst_point_sparkle->add_modifier(pm_inst_geometry_culling);
		// pe_inst_point_sparkle->add_modifier(pm_inst_position_trace);
		pe_inst_point_sparkle->add_modifier(pm_inst_sub_emitter);
		pe_inst_point_sparkle->add_initializer(pi_inst_random_velocity);
		// pe_inst_point_sparkle->add_initializer(pi_inst_random_particle_type);

		particle_emitter_type* pe_type_point_sub_sparkle = ps.add_particle_emitter_type("sub_sparkle_point_emitter_17", "sparkle_17_3", mass, density, 50, 10, "point_emitter");
		particle_emitter_instance* pe_inst_point_sub_sparkle = pe_type_point_sub_sparkle->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_sub_sparkle->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_sub_sparkle->add_initializer(pi_inst_random_velocity_sub);
		pe_inst_point_sub_sparkle->add_initializer(pi_inst_random_particle_type);

		pm_inst_sub_emitter->pointers["sub_emitter"] = pe_inst_point_sub_sparkle;

    }

	void vector_field_test()
    {
		float mass = 1.0f;
		float density = 1.0f;
		int lifetime = 5000;
		int rate = 30;

		particle_renderer_type* pr_type_sparkle = ps.add_particle_renderer_type("sparkle_renderer_18", "media/particle/flash01.png", "shader", vec4(128.0f, 128.0f, 0.0f, 0.3f), "billboard_renderer");
		pr_type_sparkle->attributes["size"] = 60.0f;

		particle_renderer_instance* pr_inst_sparkle_0 = pr_type_sparkle->create_instance("sparkle_18_0");
		pr_inst_sparkle_0->color = vec4(255.0f, 0.0f, 128.0f, 0.5f);
		pr_inst_sparkle_0->attributes["size"] = 40.0f;
		particle_renderer_instance* pr_inst_sparkle_1 = pr_type_sparkle->create_instance("sparkle_18_1");
		pr_inst_sparkle_1->color = vec4(128.0f, 255.0f, 0.0f, 0.3f);
		pr_inst_sparkle_1->attributes["size"] = 30.0f;
		particle_renderer_instance* pr_inst_sparkle_2 = pr_type_sparkle->create_instance("sparkle_18_2");
		pr_inst_sparkle_2->color = vec4(0.0f, 128.0f, 255.0f, 0.5f);
		pr_inst_sparkle_2->attributes["size"] = 50.0f;

		particle_type* p_type_sparkle_0 = ps.add_particle_type("sparkle_18_0", pr_inst_sparkle_0);
		particle_type* p_type_sparkle_1 = ps.add_particle_type("sparkle_18_1", pr_inst_sparkle_1);
		particle_type* p_type_sparkle_2 = ps.add_particle_type("sparkle_18_2", pr_inst_sparkle_2);

		particle_renderer_type* pr_type_ball = ps.add_particle_renderer_type("ball_renderer_18", "media/particle/shockwave01.png", "shader", vec4(128.0f, 128.0f, 0.0f, 0.3f), "billboard_renderer");
		pr_type_ball->attributes["size"] = 40.0f;

		particle_renderer_instance* pr_inst_ball_0 = pr_type_ball->create_instance("ball_18_0");
		pr_inst_ball_0->color = vec4(128.0f, 0.0f, 255.0f, 0.5f);
		pr_inst_ball_0->attributes["size"] = 40.0f;
		particle_renderer_instance* pr_inst_ball_1 = pr_type_ball->create_instance("ball_18_1");
		pr_inst_ball_1->color = vec4(0.0f, 255.0f, 128.0f, 0.3f);
		pr_inst_ball_1->attributes["size"] = 30.0f;
		particle_renderer_instance* pr_inst_ball_2 = pr_type_ball->create_instance("ball_18_2");
		pr_inst_ball_2->color = vec4(255.0f, 128.0f, 0.0f, 0.5f);
		pr_inst_ball_2->attributes["size"] = 50.0f;

		particle_type* p_type_ball_0 = ps.add_particle_type("ball_18_0", pr_inst_ball_0);
		particle_type* p_type_ball_1 = ps.add_particle_type("ball_18_1", pr_inst_ball_1);
		particle_type* p_type_ball_2 = ps.add_particle_type("ball_18_2", pr_inst_ball_2);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_18", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_vector_field = ps.add_particle_modifier_type("vector_field_18", "vector_field");
		particle_modifier_instance* pm_inst_vector_field = pm_type_vector_field->create_instance(vec(512.0f, 512.0f, 512.0f));

		/*
		particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_18", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
		pm_inst_geometry_collide->attributes["elasticity"] = 0.75f;
		*/

		particle_modifier_type* pm_type_rolling = ps.add_particle_modifier_type("rolling_18", "rolling");
		particle_modifier_instance* pm_inst_rolling = pm_type_rolling->create_instance();

		particle_initializer_type* pi_type_random_position = ps.add_particle_initializer_type("random_position_18", "random_position");
		pi_type_random_position->attributes["osx"] = 50.0f;
		pi_type_random_position->attributes["osy"] = 50.0f;
		pi_type_random_position->attributes["osz"] = 0.0f;
		pi_type_random_position->attributes["isx"] = 25.0f;
		pi_type_random_position->attributes["isy"] = 25.0f;
		pi_type_random_position->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_position = pi_type_random_position->create_instance();

		particle_initializer_type* pi_type_random_particle_type = ps.add_particle_initializer_type("random_particle_type_17", "random_particle_type");
		particle_initializer_instance* pi_inst_random_particle_type = pi_type_random_particle_type->create_instance();
		pi_inst_random_particle_type->particle_types.push_back(p_type_sparkle_0);
		pi_inst_random_particle_type->particle_types.push_back(p_type_sparkle_1);
		pi_inst_random_particle_type->particle_types.push_back(p_type_sparkle_2);
		pi_inst_random_particle_type->particle_types.push_back(p_type_ball_0);
		pi_inst_random_particle_type->particle_types.push_back(p_type_ball_1);
		pi_inst_random_particle_type->particle_types.push_back(p_type_ball_2);

		particle_emitter_type* pe_type_point_sparkle = ps.add_particle_emitter_type("sparkle_point_emitter_18", "sparkle_18", mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_sparkle = pe_type_point_sparkle->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_point_sparkle->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_sparkle->add_modifier(pm_inst_vector_field);
		// pe_inst_point_sparkle->add_modifier(pm_inst_geometry_collide);
		pe_inst_point_sparkle->add_modifier(pm_inst_rolling);
		pe_inst_point_sparkle->add_initializer(pi_inst_random_position);
		pe_inst_point_sparkle->add_initializer(pi_inst_random_particle_type);
    }

	void spring_weaver_test()
    {
		float mass = 5.0f;
		float density = 1.0f;
		int lifetime = 1000;
		int rate = 250;

		particle_renderer_type* pr_type_flash = ps.add_particle_renderer_type("flash_renderer_19", "media/particle/flash01.png", "shader", vec4(128.0f, 128.0f, 0.0f, 0.3f), "billboard_renderer");
		pr_type_flash->attributes["size"] = 60.0f;
		particle_renderer_instance* pr_inst_flash = pr_type_flash->create_instance("flash_19");
		particle_type* p_type_flash = ps.add_particle_type("flash_19", pr_inst_flash);

		particle_renderer_type* pr_type_sparkle = ps.add_particle_renderer_type("sparkle_renderer_19", "media/particle/sparkle01.png", "shader", vec4(0.0f, 128.0f, 128.0f, 0.3f), "billboard_renderer");
		pr_type_sparkle->attributes["size"] = 20.0f;
		particle_renderer_instance* pr_inst_sparkle = pr_type_sparkle->create_instance("sparkle_19");
		particle_type* p_type_sparkle = ps.add_particle_type("sparkle_19", pr_inst_sparkle);

		particle_renderer_type* pr_type_spring = ps.add_particle_renderer_type("spring_renderer_19", "media/particle/sparkle01.png", "shader", vec4(0.0f, 128.0f, 128.0f, 0.3f), "spring_renderer");
		particle_renderer_instance* pr_inst_spring = pr_type_spring->create_instance("spring_19");
		particle_type* p_type_spring = ps.add_particle_type("spring_19", pr_inst_spring);

		particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation_19", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_velocity_damper = ps.add_particle_modifier_type("velocity_damper_19", "velocity_damper");
		pm_type_velocity_damper->attributes["damper"] = 0.90f;
		particle_modifier_instance* pm_inst_velocity_damper = pm_type_velocity_damper->create_instance();

		particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_19", "geometry_collide");
		particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
		pm_inst_geometry_collide->attributes["elasticity"] = 0.25f;

		particle_modifier_type* pm_type_sub_emitter = ps.add_particle_modifier_type("sub_emitter_19", "sub_emitter");
		particle_modifier_instance* pm_inst_sub_emitter = pm_type_sub_emitter->create_instance();

		particle_modifier_type* pm_type_mass_spring_transformation = ps.add_particle_modifier_type("mass_spring_transformation_19", "mass_spring_transformation");
		particle_modifier_instance* pm_inst_mass_spring_transformation = pm_type_mass_spring_transformation->create_instance();

		particle_modifier_type* pm_type_simple_gravity = ps.add_particle_modifier_type("global_gravity_19", "simple_gravity");
		particle_modifier_instance* pm_inst_simple_gravity = pm_type_simple_gravity->create_instance(vec(0.0f, 0.0f, 0.0f));

		particle_initializer_type* pi_type_spring_weaver = ps.add_particle_initializer_type("spring_weaver_19", "spring_weaver");
		pi_type_spring_weaver->attributes["spring_constant"] = 0.9999f;
		pi_type_spring_weaver->attributes["spring_friction"] = 0.99f;
		pi_type_spring_weaver->attributes["size_x"] = 50.0f;
		pi_type_spring_weaver->attributes["size_y"] = 50.0f;
		pi_type_spring_weaver->attributes["spring_length_x"] = 6.0f;
		pi_type_spring_weaver->attributes["spring_length_y"] = 6.0f;
		particle_initializer_instance* pi_inst_spring_weaver = pi_type_spring_weaver->create_instance();

		ps.spring_transformation_rules["stretch_x"] = ivec(1, 0, 0);
		ps.spring_transformation_rules["stretch_y"] = ivec(0, 1, 0);
		ps.spring_transformation_rules["sheer_p"] = ivec(1, 1, 0);
		ps.spring_transformation_rules["sheer_n"] = ivec(-1, 1, 0);
		ps.spring_transformation_rules["bend_x"] = ivec(2, 0, 0);
		ps.spring_transformation_rules["bend_y"] = ivec(0, 2, 0);
		std::vector<std::string> *rules = new std::vector<std::string>;
		rules->push_back("stretch_x");
		rules->push_back("stretch_y");
		rules->push_back("sheer_p");
		rules->push_back("sheer_n");
		rules->push_back("bend_x");
		rules->push_back("bend_y");
		pi_inst_spring_weaver->pointers["rules"] = rules;

		particle_initializer_type* pi_type_random_velocity_sub = ps.add_particle_initializer_type("random_velocity_19_sub", "random_velocity");
		pi_type_random_velocity_sub->attributes["osx"] = 100.0f;
		pi_type_random_velocity_sub->attributes["osy"] = 0.0f;
		pi_type_random_velocity_sub->attributes["osz"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isx"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isy"] = 0.0f;
		pi_type_random_velocity_sub->attributes["isz"] = 0.0f;
		particle_initializer_instance* pi_inst_random_velocity_sub = pi_type_random_velocity_sub->create_instance();

		particle_emitter_type* pe_type_point_flash = ps.add_particle_emitter_type("flash_emitter_19", p_type_flash, mass, density, lifetime, rate, "point_emitter");
		particle_emitter_instance* pe_inst_point_flash = pe_type_point_flash->create_instance(vec(512.0f, 512.0f, 812.0f), vec(30.0f, 0.0f, 30.0f));
		pe_inst_point_flash->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_flash->add_modifier(pm_inst_sub_emitter);
		pe_inst_point_flash->add_modifier(pm_inst_geometry_collide);

		// particle_emitter_type* pe_type_sub_sparkle = ps.add_particle_emitter_type("sub_sparkle_point_emitter_19", p_type_sparkle, mass, density, 10000, 10000, "point_emitter");
		// pe_type_sub_sparkle->batch_size = 100;

		particle_emitter_type* pe_type_sub_sparkle = ps.add_particle_emitter_type("sub_sparkle_point_emitter_19", p_type_sparkle, mass, density, 20000, 45000, "field_emitter");
		pe_type_sub_sparkle->attributes["grid_size_x"] = 50.0f;
		pe_type_sub_sparkle->attributes["grid_size_y"] = 50.0f;
		pe_type_sub_sparkle->attributes["grid_size_z"] = 1.0f;
		pe_type_sub_sparkle->attributes["grid_dist"] = 5.0f;

		particle_emitter_instance* pe_inst_sub_sparkle = pe_type_sub_sparkle->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));
		pe_inst_sub_sparkle->add_modifier(pm_inst_velocity_transformation);
		pe_inst_sub_sparkle->add_modifier(pm_inst_mass_spring_transformation);
		// pe_inst_sub_sparkle->add_modifier(pm_inst_simple_gravity);
		pe_inst_sub_sparkle->add_modifier(pm_inst_geometry_collide);
		// pe_inst_sub_sparkle->add_modifier(pm_inst_velocity_damper);
		// pe_inst_sub_sparkle->add_initializer(pi_inst_random_velocity_sub);
		pe_inst_sub_sparkle->add_initializer(pi_inst_spring_weaver);

		pm_inst_sub_emitter->pointers["sub_emitter"] = pe_inst_sub_sparkle;

		particle_emitter_type* pe_type_noop = ps.add_particle_emitter_type("noop_emitter_19", p_type_spring, mass, density, 0, 1000000, "noop_emitter");
		particle_emitter_instance* pe_inst_noop = pe_type_noop->create_instance(vec(1024.0f, 1024.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));

    }

};

ptest *ptest_inst = new ptest();

ICOMMAND(ptest, "i", (int *setup), ptest_inst->setup(*setup));
