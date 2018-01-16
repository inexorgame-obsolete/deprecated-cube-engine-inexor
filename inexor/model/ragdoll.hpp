#pragma once

#include "inexor/physics/physics.hpp"

#include "inexor/shared/cube_loops.hpp"
#include "inexor/shared/cube_vector.hpp"
#include "inexor/shared/geom.hpp"

extern void moveragdoll(dynent *d);
extern void cleanragdoll(dynent *d);

struct ragdollskel
{
    struct vert
    {
        vec pos;
        float radius, weight;
    };

    struct tri
    {
        int vert[3];

        bool shareverts(const tri &t) const
        {
            loopi(3) loopj(3) if(vert[i] == t.vert[j]) return true;
            return false;
        }
    };

    struct distlimit
    {
        int vert[2];
        float mindist, maxdist;
    };

    struct rotlimit
    {
        int tri[2];
        float maxangle;
        matrix3 middle;
    };

    struct rotfriction
    {
        int tri[2];
        matrix3 middle;
    };

    struct joint
    {
        int bone, tri, vert[3];
        float weight;
        matrix4x3 orient;
    };

    struct reljoint
    {
        int bone, parent;
    };

    bool loaded, animjoints;
    int eye;
    vector<vert> verts;
    vector<tri> tris;
    vector<distlimit> distlimits;
    vector<rotlimit> rotlimits;
    vector<rotfriction> rotfrictions;
    vector<joint> joints;
    vector<reljoint> reljoints;

    ragdollskel() : loaded(false), animjoints(false), eye(-1) {}

    void setupjoints()
    {
        loopv(verts) verts[i].weight = 0;
        loopv(joints)
        {
            joint &j = joints[i];
            j.weight = 0;
            vec pos(0, 0, 0);
            loopk(3) if(j.vert[k]>=0)
            {
                pos.add(verts[j.vert[k]].pos);
                j.weight++;
                verts[j.vert[k]].weight++;
            }
            if(j.weight) j.weight = 1/j.weight;
            pos.mul(j.weight);

            tri &t = tris[j.tri];
            matrix4x3 &m = j.orient;
            const vec &v1 = verts[t.vert[0]].pos,
                      &v2 = verts[t.vert[1]].pos,
                      &v3 = verts[t.vert[2]].pos;
            m.a = vec(v2).sub(v1).normalize();
            m.c.cross(m.a, vec(v3).sub(v1)).normalize();
            m.b.cross(m.c, m.a);
            m.d = pos;
            m.transpose();
        }
        loopv(verts) if(verts[i].weight) verts[i].weight = 1/verts[i].weight;
        reljoints.shrink(0);
    }

    void setuprotfrictions()
    {
        rotfrictions.shrink(0);
        loopv(tris) for(int j = i+1; j < tris.length(); j++) if(tris[i].shareverts(tris[j]))
        {
            rotfriction &r = rotfrictions.add();
            r.tri[0] = i;
            r.tri[1] = j;
        }
    }

    void setup()
    {
        setupjoints();
        setuprotfrictions();

        loaded = true;
    }

    void addreljoint(int bone, int parent)
    {
        reljoint &r = reljoints.add();
        r.bone = bone;
        r.parent = parent;
    }
};

struct ragdolldata
{
    struct vert
    {
        vec oldpos, pos, newpos;
        float weight;
        bool collided, stuck;

        vert() : pos(0, 0, 0), newpos(0, 0, 0), weight(0), collided(false), stuck(true) {}
    };

    ragdollskel *skel;
    int millis, collidemillis, collisions, floating, lastmove, unsticks;
    vec offset, center;
    float radius, timestep, scale;
    vert *verts;
    matrix3 *tris;
    matrix4x3 *animjoints;
    dualquat *reljoints;

    ragdolldata(ragdollskel *skel, float scale = 1)
            : skel(skel),
              millis(lastmillis),
              collidemillis(0),
              collisions(0),
              floating(0),
              lastmove(lastmillis),
              unsticks(INT_MAX),
              radius(0),
              timestep(0),
              scale(scale),
              verts(new vert[skel->verts.length()]),
              tris(new matrix3[skel->tris.length()]),
              animjoints(!skel->animjoints || skel->joints.empty() ? nullptr : new matrix4x3[skel->joints.length()]),
              reljoints(skel->reljoints.empty() ? nullptr : new dualquat[skel->reljoints.length()])
    {
    }

    ~ragdolldata()
    {
        delete[] verts;
        delete[] tris;
        if(animjoints) delete[] animjoints;
        if(reljoints) delete[] reljoints;
    }

    void calcanimjoint(int i, const matrix4x3 &anim)
    {
        if(!animjoints) return;
        ragdollskel::joint &j = skel->joints[i];
        vec pos(0, 0, 0);
        loopk(3) if(j.vert[k]>=0) pos.add(verts[j.vert[k]].pos);
        pos.mul(j.weight);

        ragdollskel::tri &t = skel->tris[j.tri];
        matrix4x3 m;
        const vec &v1 = verts[t.vert[0]].pos,
                  &v2 = verts[t.vert[1]].pos,
                  &v3 = verts[t.vert[2]].pos;
        m.a = vec(v2).sub(v1).normalize();
        m.c.cross(m.a, vec(v3).sub(v1)).normalize();
        m.b.cross(m.c, m.a);
        m.d = pos;
        animjoints[i].transposemul(m, anim);
    }

    void calctris()
    {
        loopv(skel->tris)
        {
            ragdollskel::tri &t = skel->tris[i];
            matrix3 &m = tris[i];
            const vec &v1 = verts[t.vert[0]].pos,
                      &v2 = verts[t.vert[1]].pos,
                      &v3 = verts[t.vert[2]].pos;
            m.a = vec(v2).sub(v1).normalize();
            m.c.cross(m.a, vec(v3).sub(v1)).normalize();
            m.b.cross(m.c, m.a);
        }
    }

    void calcboundsphere()
    {
        center = vec(0, 0, 0);
        loopv(skel->verts) center.add(verts[i].pos);
        center.div(skel->verts.length());
        radius = 0;
        loopv(skel->verts) radius = max(radius, verts[i].pos.dist(center));
    }

    void init(dynent *d)
    {
        extern SharedVar<int> ragdolltimestepmin;
        float ts = ragdolltimestepmin/1000.0f;
        loopv(skel->verts) (verts[i].oldpos = verts[i].pos).sub(vec(d->vel).add(d->falling).mul(ts));
        timestep = ts;

        calctris();
        calcboundsphere();
        offset = d->o;
        offset.sub(skel->eye >= 0 ? verts[skel->eye].pos : center);
        offset.z += (d->eyeheight + d->aboveeye)/2;
    }

    void move(dynent *pl, float ts);
    void updatepos();
    void constrain();
    void constraindist();
    void applyrotlimit(ragdollskel::tri &t1, ragdollskel::tri &t2, float angle, const vec &axis);
    void constrainrot();
    void calcrotfriction();
    void applyrotfriction(float ts);
    void tryunstick(float speed);

    static inline bool collidevert(const vec &pos, const vec &dir, float radius)
    {
        static struct vertent : physent
        {
            vertent()
            {
                type = ENT_BOUNCE;
                radius = xradius = yradius = eyeheight = aboveeye = 1;
            }
        } v;
        v.o = pos;
        if(v.radius != radius) v.radius = v.xradius = v.yradius = v.eyeheight = v.aboveeye = radius;
        return collide(&v, dir, 0, false);
    }
};
