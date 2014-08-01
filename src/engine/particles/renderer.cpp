#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_renderer_type> particle_renderer_types;

// implementations - the concrete implementations
vector<particle_renderer_implementation *> particle_renderer_implementations;

// concrete instances refers to the abstract definitions
vector<particle_renderer_instance> particle_renderer_instances;

void render_particles()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glPointSize(5.0f);
	glDepthMask(false);
	glColor4f(0.8f, 0.5f, 0.0f, 0.3f);
	glBegin(GL_POINTS);
	loopv(alive_pool[current_alive_pool])
    {
        particle_renderer_types[particle_types[alive_pool[current_alive_pool][i].type].renderer_type].impl->render(&alive_pool[current_alive_pool][i]);
    }
	glEnd();
	glDepthMask(true);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	glPopMatrix();
}

int add_particle_renderer_type(std::string name, std::string shader, std::string impl)
{
	particle_renderer_types.add();
	int pr_type_id = particle_renderer_types.length() - 1;
	particle_renderer_types[pr_type_id].name = name;
	particle_renderer_types[pr_type_id].shader = shader;
	int impl_id = get_particle_renderer_implementation(impl);
	particle_renderer_types[pr_type_id].impl = particle_renderer_implementations[impl_id];

	conoutf("Added particle renderer type \"%s\" (id: %d shader: %s) of implementation \"%s\" (id: %d) [%d:%d:%d]", name.c_str(), pr_type_id, shader.c_str(), impl.c_str(), impl_id, particle_renderer_instances.length(), particle_renderer_types.length(), particle_renderer_implementations.length());
	return pr_type_id;
}

int get_particle_renderer_type(std::string name)
{
	conoutf("get prt | %s", name.c_str());
	loopv(particle_renderer_types)
	{
		if (particle_renderer_types[i].name.compare(name) == 0) {
			conoutf("found prt | %s | %s", particle_renderer_types[i].name.c_str(), name.c_str());
			return i;
		}
	}
	conoutf("prt not found");
	return -1;
}

int get_particle_renderer_implementation(std::string name)
{
	loopv(particle_renderer_implementations)
	{
		if (particle_renderer_implementations[i]->name.compare(name) == 0) return i;
	}
	return -1;
}

ICOMMAND(add_particle_renderer_type, "ss", (char *name, char *shader, char *impl), intret(add_particle_renderer_type(name, shader, impl)));
ICOMMAND(get_particle_renderer_type, "s", (char *name), intret(get_particle_renderer_type(name)));
ICOMMAND(particle_renderer_types_num, "", (), intret(particle_renderer_types.length()));

ICOMMAND(ls_particle_renderer_types, "", (),
{
	loopv(particle_renderer_types) {
		conoutf("%i | %s | %s", i, particle_renderer_types[i].name.c_str(), particle_renderer_types[i].shader.c_str());
	}
});
