#include "engine.h"
#include "faces.h"

void particle_system::render_faces()
{
	for(std::vector<face_type*>::iterator ft_it = face_types.begin(); ft_it != face_types.end(); ++ft_it)
	{
		face_type* ft = (*ft_it);
		if (ft->instances.size() > 0)
		{
			// conoutf("face type: %s (%d)", ft->name.c_str(), (int) ft->instances.size());
			// face type:
			// - bool cull_face
			// - string texture
			// - int clamp texture
			// - bool blend
			// - int blend_func
			// - color
			glPushMatrix();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			defaultshader->set();
			glEnable(GL_CULL_FACE);
			// glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			Texture* tex = textureload(ft->texture.c_str(), 0);
			glBindTexture(GL_TEXTURE_2D, tex->id);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
			// glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
			// glColor4f(1.0f, 0.4f, 0.0f, 0.3f);
			glBegin(GL_QUADS);
			// int r = 0;
			std::list<face_instance*>::iterator fi_it = (*ft_it)->instances.begin();
			while (fi_it != (*ft_it)->instances.end())
			{
				face_instance* f_inst = (*fi_it);
				if (f_inst->p[0]->remaining > 0 && f_inst->p[1]->remaining > 0 && f_inst->p[2]->remaining > 0 && f_inst->p[3]->remaining > 0) {
					// if (r == 0) {
					// 	conoutf("face %d: p0(%2.2f, %2.2f, %2.2f) p1(%2.2f, %2.2f, %2.2f) p2(%2.2f, %2.2f, %2.2f) p3(%2.2f, %2.2f, %2.2f)", r, f_inst->p[0]->pos->o.x, f_inst->p[0]->pos->o.y, f_inst->p[0]->pos->o.z, f_inst->p[1]->pos->o.x, f_inst->p[1]->pos->o.y, f_inst->p[1]->pos->o.z, f_inst->p[2]->pos->o.x, f_inst->p[2]->pos->o.y, f_inst->p[2]->pos->o.z, f_inst->p[3]->pos->o.x, f_inst->p[3]->pos->o.y, f_inst->p[3]->pos->o.z);
					// }
					// glColor4f(0.8f, 0.5f, 0.8f, 0.3f);
					glColor4f(f_inst->color.r, f_inst->color.g, f_inst->color.b, f_inst->color.a);
					glNormal3d(0, 0, 1);
					glTexCoord2f(0, 0);
					glVertex3d(f_inst->p[0]->pos->o.x, f_inst->p[0]->pos->o.y, f_inst->p[0]->pos->o.z);
					glTexCoord2f(1, 0);
					glVertex3d(f_inst->p[1]->pos->o.x, f_inst->p[1]->pos->o.y, f_inst->p[1]->pos->o.z);
					glTexCoord2f(1, 1);
					glVertex3d(f_inst->p[2]->pos->o.x, f_inst->p[2]->pos->o.y, f_inst->p[2]->pos->o.z);
					glTexCoord2f(0, 1);
					glVertex3d(f_inst->p[3]->pos->o.x, f_inst->p[3]->pos->o.y, f_inst->p[3]->pos->o.z);
					++fi_it;
				} else {
					// remove face
					fi_it = (*ft_it)->instances.erase(fi_it);
				}
				// r++;
			}
			glEnd();

			if (editmode)
			{
				lineshader->set();
				glLineWidth(2);
				glEnable(GL_LINE_SMOOTH);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				std::list<face_instance*>::iterator fi_it = (*ft_it)->instances.begin();
				while (fi_it != (*ft_it)->instances.end())
				{
					face_instance* f_inst = (*fi_it);
					if (f_inst->p[0]->remaining > 0 && f_inst->p[1]->remaining > 0 && f_inst->p[2]->remaining > 0 && f_inst->p[3]->remaining > 0) {
						glBegin(GL_LINE_LOOP);
						glVertex3d(f_inst->p[0]->pos->o.x, f_inst->p[0]->pos->o.y, f_inst->p[0]->pos->o.z);
						glVertex3d(f_inst->p[1]->pos->o.x, f_inst->p[1]->pos->o.y, f_inst->p[1]->pos->o.z);
						glVertex3d(f_inst->p[2]->pos->o.x, f_inst->p[2]->pos->o.y, f_inst->p[2]->pos->o.z);
						glVertex3d(f_inst->p[3]->pos->o.x, f_inst->p[3]->pos->o.y, f_inst->p[3]->pos->o.z);
						glEnd();
						++fi_it;
					} else {
						// remove face
						fi_it = (*ft_it)->instances.erase(fi_it);
					}
				}
				glLineWidth(1);
				glDisable(GL_LINE_SMOOTH);
			}

			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_TEXTURE_2D);
			// glDisable(GL_CULL_FACE);
			glPopMatrix();
		}
	}
	printOpenGLError();
}

face_type* particle_system::add_face_type(std::string name, std::string texture)
{
	if (!face_types_map.count(name))
	{
		face_type* f_type = new face_type;
		f_type->name = name;
		f_type->texture = texture;
		face_types.push_back(f_type);
		face_types_map[name] = f_type;
		ps.count_face_types++;
		conoutf("Added face type \"%s\"", name.c_str());
		return f_type;
	} else {
		conoutf("Face type %s already exists!", name.c_str());
		return face_types_map[name];
	}
}

face_instance* face_type::create_instance(particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3)
{
	return create_instance(p0, p1, p2, p3, vec4(1.0f, 1.0f, 1.0f, 0.5f));
}

face_instance* face_type::create_instance(particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3, vec4 color)
{
	face_instance* f_inst = new face_instance(p0, p1, p2, p3);
	f_inst->type = this;
	f_inst->color = vec4(color);
	f_inst->attributes.insert(attributes.begin(), attributes.end());
	instances.push_back(f_inst);
	ps.face_instances.push_back(f_inst);
	ps.count_face_instances++;
	return f_inst;
}

face_instance* particle_system::create_face_instance(face_type* f_type, particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3)
{
	return f_type->create_instance(p0, p1, p2, p3);
}

face_instance* particle_system::create_face_instance(std::string f_type, particle_instance* p0, particle_instance* p1, particle_instance* p2, particle_instance* p3)
{
	if (face_types_map.count(f_type))
	{
		return face_types_map[f_type]->create_instance(p0, p1, p2, p3);
	} else {
		conoutf("Face type %s not found!", f_type.c_str());
		return 0;
		// return noop_face_inst;
	}
}

void particle_system::remove_face_type(std::string name)
{
	if (face_types_map.count(name))
	{
		// TODO: iterate and remove face_instances from face_types
		/*
		for(std::vector<face_type*>::iterator ft_it = face_types.begin(); ft_it != face_types.end(); ++ft_it)
		{
			(*ft_it)->instances.clear();
		}
		*/
		face_types_map.erase(name);
		count_face_types--;
	} else {
		conoutf("Face type %s not found!", name.c_str());
	}
}

void particle_system::remove_all_face_types()
{
	// TODO: iterate and remove face_instances from face_types
	face_types_map.clear();
	face_types.clear();
	face_types.push_back(noop_face_type);
	face_types_map["noop"] = noop_face_type;
	count_face_types = 1;
}

void particle_system::remove_all_face_instances()
{
	face_instances.clear();
	// TODO: iterate and remove face_instances from face_types
	count_face_instances = 0;
}

/*
void particle_system::add_face_construction_rule(std::string name, ivec rule)
{
	ps.face_construction_rules[name] = rule;
}

void particle_system::add_face_construction_rule(std::string name, int x, int y, int z)
{
	ps.face_construction_rules[name] = ivec(x, y, z);
}
*/

/**
 * Some useful default rules for stretch, sheer and bend springs.
 */
/*
void particle_system::init_face_construction_rules()
{
}
*/
