#include "inexor/engine/engine.h"
#include "inexor/flowgraph/editor/fl_enteditor.h"

#include "inexor/geom/curves/bezier/bezier.h"
#include "inexor/geom/curves/curvebase.h"


namespace inexor {
namespace vscript {


    CEntityManager::CEntityManager()
    {
        dragging_new_relation = false;
        dragging_node = false;
        selected_node = nullptr;
        hovered_node = nullptr;
    }


    CEntityManager::~CEntityManager()
    {
    }


    void CEntityManager::update_mouse(int key, bool isdown)
    {
        /// check if LEFT mouse button is down for dragging a new connection out of the node
        if(key == - SDL_BUTTON_LEFT)
        {
            if(old_isdown != isdown) 
            {
                //conoutf(CON_DEBUG, "%d left mouse changed", SDL_GetTicks());
                process_change(key, isdown);
                old_isdown = isdown;
            }
        }
        /// check if RIGHT mouse button is down for moving the entity
        if(key == - SDL_BUTTON_RIGHT)
        {
            if(old_isdown != isdown) 
            {
                //conoutf(CON_DEBUG, "%d right mouse changed", SDL_GetTicks());
                process_change(key, isdown);
                old_isdown = isdown;
            }
        }
    }


    void CEntityManager::render_temp_connection()
    {
        if(dragging_new_relation)
        {
            /// has the camera position changed?
            if(camera_last_pos != camera1->o) 
            {
                vec tmp = drag_pos_start;
                vec tmp2 = camera1->o - camera_offset_start;
                tmp.sub(tmp2);

                drag_pos_current = tmp;
                camera_last_pos = camera1->o;
            }

            /// TODO
            ///conoutf(CON_DEBUG, "%f %f %f", drag_pos_current.x, drag_pos_current.y, drag_pos_current.z);

            /// TODO: render a temporary dragging node
            inexor::geom::CBezierCurve curve;

            /// create additional interpolation data
            vec t = drag_pos_start;
            vec n = drag_pos_current;
            vec interpol1 = vec( (t.x+n.x)/2.0f, (t.y+n.y)/2.0f, (t.z+n.z)/2.0f - 30.0f);
            vec interpol2 = vec( (t.x+n.x)/2.0f, (t.y+n.y)/2.0f, (t.z+n.z)/2.0f + 30.0f);
            
            /// correct offset
            t.x += boxsize/2;
            t.y += boxsize/2;
            n.x += boxsize/2;
            n.y += boxsize/2;
            n.z += boxsize;

            /// add points
            curve.AddParameterPoint(t);
            curve.AddParameterPoint(interpol1);
            curve.AddParameterPoint(interpol2);
            curve.AddParameterPoint(n);

            /// compute!
            curve.ComputeCache();

            /// render curve as list of small lines
            glBegin(GL_LINES);

            gle::color(vec::hexcolor(VSCRIPT_COLOR_TRIGGERED));
            glLineWidth(10.0f);

            for(unsigned int h=0; h<curve.GetCachedPointsNumber() -1; h++)
            {
                inexor::geom::SCustomOutputPoint t = curve.GetPoint_ByIndex(h);
                inexor::geom::SCustomOutputPoint n = curve.GetPoint_ByIndex(h  +1);
                glVertex3f(t.pos.x, t.pos.y, t.pos.z);
                glVertex3f(n.pos.x, n.pos.y, n.pos.z);
            }
            /// reset line width
            glLineWidth(1.0f);
            glEnd();
        }
    }

};
};
