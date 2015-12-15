/// @file curvebase.h
/// @author Johannes "Hanni" Schneider
/// @date 30.08.2015
/// @review #5: 14.10.2015
/// @brief This header file defines the base class for all curve computing classes.

/// TODO: Keep parameter points up to date without clearing and reinitialising all parameter points?
///       must implement some kind of pass_param_point_vector and bool haschanged = false; method..
/// TODO: Calculate the length of the curve? (auto precision)


#ifndef INEXOR_GEOM_CURVE_BASE_HEADER
#define INEXOR_GEOM_CURVE_BASE_HEADER

#include <vector>
#include "inexor/engine/engine.h"

#define INEXOR_VSCRIPT_STD_CALC_PRECISION 50
#define INEXOR_VSCRIPT_STD_MAX_PARAM_POINTS 30


namespace inexor {
namespace geom {

    struct SCustomInputPoint 
    {
        vec pos;

        /// Please note: there is no standard constructor for this structure
        SCustomInputPoint(vec p = vec(0,0,0)) {
            pos = p;
        }
        SCustomInputPoint(float x, float y, float z) {
            pos = vec(x,y,z);
        }
    };


    struct SCustomOutputPoint : public SCustomInputPoint 
    {
        vec tangent;
        vec normal;

        /// Please note: a normal vector can be rotated around the curve in any angle
        /// Please note: there is no stanard constructor for this structure

        SCustomOutputPoint(vec _point = vec(0,0,0))
        {
            pos = _point;
            tangent = vec(0,0,0);
            normal = vec(0,0,0);
        }
        SCustomOutputPoint(float x, float y, float z)
        {
            pos = vec(x,y,z);
            tangent = vec(0,0,0);
            normal = vec(0,0,0);
        }
        SCustomOutputPoint(SCustomInputPoint _point) 
        {
            pos = _point.pos;
            tangent = vec(0,0,0);
            normal = vec(0,0,0);
        }
        SCustomOutputPoint(SCustomInputPoint t, vec _tangent, vec _normal) 
        {
            pos = t.pos;
            tangent = _tangent;
            normal = _normal;
        }

        // TODO: overload +-*/ operators
    };


    class CCurveBase 
    {
        protected:

            std::vector<SCustomInputPoint> m_vInputPoints;

            std::vector<SCustomOutputPoint> m_vOutputPoints;

            float m_fComputationPrecision = INEXOR_VSCRIPT_STD_CALC_PRECISION;

            unsigned int m_uiMaxParameterPoints = INEXOR_VSCRIPT_STD_MAX_PARAM_POINTS;

            bool m_bCacheComputed = false;

        public:

            CCurveBase();
            ~CCurveBase();

            void SetParameterPointLimit(unsigned int);
            void SetCurvePrecision(float);


            void AddParameterPoint(vec);
            void AddParameterPoint(float, float, float);


            virtual SCustomOutputPoint CalcRealtimePoint(float) = 0;

            virtual void ComputeCache() = 0;

            bool IsCurveComputed();

            const unsigned int GetCachedPointsSize();
            const unsigned int GetIndex_ByInterpolationPos(float);

            SCustomOutputPoint GetPoint_ByInterpolationPos(float);
            SCustomOutputPoint GetPoint_ByIndex(unsigned int);

            void ClearAllPoints();
            void ClearParamPoints();
            void ClearCachePoints();
    };

};
};

#endif
