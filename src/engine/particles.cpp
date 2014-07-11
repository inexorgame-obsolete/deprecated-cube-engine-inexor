#include "cube.h"
#include "particles.h"

// abstract definitions - makes everything dynamic
vector<particle_type *> particle_types;
vector<particle_emitter_type *> particle_emitter_types;
vector<particle_renderer_type *> particle_renderer_types;
vector<particle_modifier_type *> particle_modifier_types;

// concrete instances refers to the abstract definitions
vector<particle_instance *> particles_instances;
vector<particle_emitter *> particle_emitters;
vector<particle_renderer *> particle_renderers;
vector<particle_modifier *> particle_modifiers;

// particle pools for performance reasons
vector<particle_instance *> alive_pool;
vector<particle_instance *> dead_pool;

void init_particles() {

};

void apply_particle_modifiers() {

};

void render_particles() {

};

void add_particle_type() {

};

void remove_particle_type() {

};

void add_particle_emitter() {

};

void remove_particle_emitter() {

};

void add_particle_renderer() {

};

void remove_particle_renderer() {

};

void add_particle_modifier() {

};

void remove_particle_modifier() {

};

void set_particle_type(int particle_id) {

};

void set_particle_emitter(int particle_id, int emitter_id) {

};
