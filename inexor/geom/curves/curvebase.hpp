/// @file curvebase.h
/// @author Johannes "Hanni" Schneider
/// @date 30.08.2015
/// @brief This header file defines the base class for all curve computing classes.

/// TODO: Keep parameter points up to date without clearing and reinitialising all parameter points?
/// TODO: Calculate the length of the curve
/// TODO: Get point's distance from curve


#ifndef INEXOR_GEOM_CURVE_BASE_HEADER
#define INEXOR_GEOM_CURVE_BASE_HEADER

#include <vector>
#include "inexor/engine/engine.hpp"

#define INEXOR_VSCRIPT_STD_CALC_PRECISION 100
#define INEXOR_VSCRIPT_STD_MAX_PARAM_POINTS 10


namespace inexor {
namespace geom {

    struct SCustomInputPoint 
    {
        vec pos;

        SCustomInputPoint(vec p = vec(0,0,0)) {
            pos = p;
        }
        SCustomInputPoint(float x, float y, float z) {
            pos = vec(x,y,z);
        }
    };


    /// @brief Output points have normal and tangent vectors.
    struct SCustomOutputPoint : public SCustomInputPoint 
    {
        vec tangent;
        /// A normal vector can be rotated around the curve in any angle!
        vec normal;

        SCustomOutputPoint(vec p = vec(0,0,0))
        {
            pos = p;
            tangent = vec(0,0,0);
            normal = vec(0,0,0);
        }
        SCustomOutputPoint(float x, float y, float z)
        {
            pos = vec(x,y,z);
            tangent = vec(0,0,0);
            normal = vec(0,0,0);
        }
        SCustomOutputPoint(SCustomInputPoint p) 
        {
            pos = p.pos;
            tangent = vec(0,0,0);
            normal = vec(0,0,0);
        }
        SCustomOutputPoint(SCustomInputPoint o, vec t, vec n) 
        {
            pos = o.pos;
            tangent = t;
            normal = n;
        }

        // TODO: overload +-*/ operators
    };


    class CCurveBase 
    {
        protected:

            std::vector<SCustomInputPoint>  m_vInputPoints;
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

            /// realtime computation
            virtual SCustomOutputPoint CalcRealtimePoint(float) = 0;

            /// cached computation
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
