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
    loopv(alive_pool[current_alive_pool])
    {
        particle_instance p_inst = alive_pool[current_alive_pool][i];
        particle_type p_type = particle_types[p_inst.type];
        particle_renderer_type pr_type = particle_renderer_types[p_type.renderer_type];
        pr_type.impl->render(p_inst);
        // conoutf("rendered");
    }
}

int add_particle_renderer_type(const char *name, const char *shader, const char *impl)
{
	particle_renderer_types.add();
	int pr_type_id = particle_renderer_types.length() - 1;
	copystring(particle_renderer_types[pr_type_id].name, name);
	copystring(particle_renderer_types[pr_type_id].shader, shader);
	impl = newstring(impl);
	int impl_id = get_particle_renderer_implementation(impl);
	particle_renderer_types[pr_type_id].impl = particle_renderer_implementations[impl_id];

	conoutf("Added particle renderer type \"%s\" (id: %d shader: %s) of implementation \"%s\" (id: %d) [%d:%d:%d]", name, pr_type_id, shader, impl, impl_id, particle_renderer_instances.length(), particle_renderer_types.length(), particle_renderer_implementations.length());
	return pr_type_id;
}

// bug: we must not change the indexes (vector.remove), because they are referenced
void remove_particle_renderer_type(const char *name)
{
	int renderer_type = get_particle_renderer_type(name);
	if (renderer_type >= 0) particle_renderer_types.remove(renderer_type);
}

int get_particle_renderer_type(const char *name)
{
	conoutf("get prt | %s", name);
	loopv(particle_renderer_types)
	{
		conoutf("  | %s | %s | %i", particle_renderer_types[i].name, name, strcmp(particle_renderer_types[i].name, name));
		if (strcmp(particle_renderer_types[i].name, name) == 0) {
			conoutf("found prt | %s | %s", particle_renderer_types[i].name, name);
			return i;
		}
	}
	conoutf("prt not found");
	return -1;
}

int get_particle_renderer_implementation(const char *name)
{
	loopv(particle_renderer_implementations)
	{
		if (strcmp(particle_renderer_implementations[i]->name, name) == 0) return i;
	}
	return -1;
}

ICOMMAND(add_particle_renderer_type, "ss", (char *name, char *shader, char *impl), intret(add_particle_renderer_type(name, shader, impl)));
COMMAND(remove_particle_renderer_type, "s");
ICOMMAND(get_particle_renderer_type, "s", (char *name), intret(get_particle_renderer_type(name)));
ICOMMAND(particle_renderer_types_num, "", (), intret(particle_renderer_types.length()));

ICOMMAND(ls_particle_renderer_types, "", (),
{
	loopv(particle_renderer_types) {
		conoutf("%i | %s | %s", i, particle_renderer_types[i].name, particle_renderer_types[i].shader);
	}
});
