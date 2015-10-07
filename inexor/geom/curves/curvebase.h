/// @file curvebase.h
/// @author Johannes "Hanni" Schneider
/// @date 30.08.2015
/// @brief this header file defines the base class for all curve computing classes

/// TODO: Hot to keep parameter points up to date without clearing and repassing all parameter points?

#ifndef INEXOR_GEOM_CURVE_BASE_HEADER
#define INEXOR_GEOM_CURVE_BASE_HEADER

/// vector dependency
#include "inexor/engine/engine.h"
/// vector container class from std lib
#include <vector>


/// security namespaces
namespace inexor {
namespace geom {


/// the input data
struct SCustomInputPoint 
{
    vec pos;

    /// overloaded constructor I
    SCustomInputPoint(vec p = vec(0,0,0)) {
        pos = p;
    }

    /// overloaded constructor II
    SCustomInputPoint(float x, float y, float z) {
        pos = vec(x,y,z);
    }
};


/// the output data
struct SCustomOutputPoint : public SCustomInputPoint 
{
    /// additional data that describes points on this curve
    vec tangent;
    vec normal;

    /// please note that 3D curve's normal/tangent vectors
    /// can be rotated in any angle.

    /// overloaded constructor I
    SCustomOutputPoint(vec p = vec(0,0,0))
    {
        pos = p;
        tangent = vec(0,0,0);
        normal = vec(0,0,0);
    }

    /// overloaded constructor II
    SCustomOutputPoint(float x, float y, float z)
    {
        pos = vec(x,y,z);
        tangent = vec(0,0,0);
        normal = vec(0,0,0);
    }

    /// overloaded constructor III
    SCustomOutputPoint(SCustomInputPoint t) 
    {
        pos = t.pos;
        tangent = vec(0,0,0);
        normal = vec(0,0,0);
    }
};


/// @brief the standard amount of intepolation steps for curve calculation
#define INEXOR_VSCRIPT_STD_CALC_PRECISION 40
/// @brief the maximum number of parameter points which can be passed to the engine
#define INEXOR_VSCRIPT_STD_MAX_PARAM_POINTS 30


/// @brief the curve base class defines input, output and computation functions
class CCurveBase 
{
    protected:

    // the curve input data
    std::vector<SCustomInputPoint> m_vInputPoints;
    // the curve output data
    std::vector<SCustomOutputPoint> m_vOutputPoints;

    // the calculation precision
    float m_fComputationPrecision = INEXOR_VSCRIPT_STD_CALC_PRECISION;

    // maximum number of parameter points
    unsigned int m_uiMaxParameterPoints = INEXOR_VSCRIPT_STD_MAX_PARAM_POINTS;

    // curve computed?
    bool m_bCacheComputed = false;

    // additional base members?

    public:

    // constructor
    //CCurveBase();
    // destructor
    //~CCurveBase();

    /// set the maximum of parameter points
    void SetParameterPointLimit(unsigned int limit);

    /// @brief add an input point
    void AddParameterPoint(vec p);
    void AddParameterPoint(float x, float y, float z);

    /// @brief set the computation precision
    void SetCurvePrecision(float precision);    

    // realtime computation

    /// @brief Compute a point in realtime
    /// @warning depending on the calculation precision this may take longer than caching points!
    /// the amount of curves which will be computed in realtime also increases calculation time!
    SCustomOutputPoint CalcRealtimePos(float t);


    /// cached computation

    /// @brief Compute the input data to output data
    void ComputeCache(void);

    /// @brief Has the input data changed?
    void IsCurveComputed(void);

    /// @brief Get a point from the computed curve cache
    SCustomOutputPoint GetCachePoint(float t);

    /// @warning make sure not to flood m_vInputPoints 
    /// by adding parameter points in a game loop e.g.


    /// @brief deleting methods
    void ClearAllPoints();
    void ClearParamPoints();
    void ClearCachePoints();
};

};
};

#endif INEXOR_GEOM_CURVE_BASE_HEADER