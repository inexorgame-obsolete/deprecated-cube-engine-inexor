#include "engine.h"
#include "entities.h"

// extern void boxs3D(const vec &o, vec s, int g);

entity_system es;


entity_system::entity_system() {
	count_positions = 0;
	default_shader = lookupshaderbyname("default");
}

entity_system::~entity_system() {

}

/**
 * Apply renderers.
 */
void entity_system::update_entity_system()
{
	try
	{
	    render_entities();
	} catch (int e) {
		conoutf("update_entity_system e: %d", e);
	}
}

/**
 * Rendering of the entity instances.
 */
void entity_system::render_entities()
{
	/*
	if (editmode)
	{
		glPushMatrix();
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(false);
		glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
        glLineWidth(5);
        lineshader->set();
		// conoutf("render_entities: %d positions / %d count", (int) positions.size(), count_positions);
		int i = 0;
        default_shader->set();
		glBegin(GL_LINES);
		for(std::vector<position*>::iterator it = positions.begin(); it != positions.end(); ++it)
		{
			// conoutf("render_entity %d(%2.2f, %2.2f, %2.2f)", i, (*it)->o.x, (*it)->o.y, (*it)->o.z);
			vec eo = vec((*it)->o);
		    vec es = vec((*it)->o).add(25.0f);
			//vec eo = vec(492.0f, 492.0f, 492.0f);
		    //vec es = vec(532.0f, 532.0f, 532.0f);
			glVertex3d(eo.x, eo.y, eo.z);
			glVertex3d(eo.x, es.y, eo.z);
			glVertex3d(es.x, es.y, eo.z);
			glVertex3d(es.x, eo.y, eo.z);
			glVertex3d(eo.x, eo.y, es.z);
			glVertex3d(eo.x, es.y, es.z);
			glVertex3d(es.x, es.y, es.z);
			glVertex3d(es.x, eo.y, es.z);
		    // boxs3D(eo, es, 1);
		    ++it;
		}
		glEnd();
	    notextureshader->set();
		glDepthMask(true);
        glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
// 		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(1);
		glPopMatrix();
	}
	*/
}

/**
 * Creates a managed position.
 */
position* entity_system::create_position(const vec &o)
{
	conoutf("create_position %d(%2.2f, %2.2f, %2.2f)", count_positions, o.x, o.y, o.z);
	position* pos = new position(o);
	positions.push_back(pos);
	count_positions++;
	return pos;
}

void entity_system::remove_position(position* pos)
{
	positions.erase(std::remove(positions.begin(), positions.end(), pos), positions.end());
	count_positions--;
	delete pos;
}

void entity_system::cleanup() {

}

