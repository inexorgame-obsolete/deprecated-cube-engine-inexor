/// @file curvebase.h
/// @author Johannes "Hanni" Schneider
/// @date 30.08.2015
/// @review #5: 14.10.2015
/// @brief This header file defines the base class for all curve computing classes.

/// TODO: Keep parameter points up to date without clearing and reinitialising all parameter points?
///       must implement some kind of pass_param_point_vector and bool haschanged = false; method..
/// TODO: Calculate the length of the curve? (auto precision)


/// Include guard
#ifndef INEXOR_GEOM_CURVE_BASE_HEADER
#define INEXOR_GEOM_CURVE_BASE_HEADER

/// (math) vector dependency
#include "inexor/engine/engine.h"
/// C++ standard library for dynamic arrays
#include <vector>

/// Inexor geom namespace
namespace inexor {
namespace geom {


/// @brief A structure for the input data
struct SCustomInputPoint 
{
    vec pos;
    /// TODO: ...

    /// Please note: there is no standard constructor for this structure

    /// overloaded constructor I
    SCustomInputPoint(vec p = vec(0,0,0)) {
        pos = p;
    }

    /// overloaded constructor II
    SCustomInputPoint(float x, float y, float z) {
        pos = vec(x,y,z);
    }
};


/// TODO: add derivates which inherit from SCustomInputPoint

/// @brief A structure for the computed data
/// @see SCustomInputPoint
struct SCustomOutputPoint : public SCustomInputPoint 
{
    /// additional data that describes curve derivates
    vec tangent;
    vec normal;

    /// Please note: a normal vector can be rotated around the curve in any angle
    /// Please note: there is no stanard constructor for this structure

    /// overloaded constructor I
    SCustomOutputPoint(vec _point = vec(0,0,0))
    {
        pos = _point;
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
    SCustomOutputPoint(SCustomInputPoint _point) 
    {
        pos = _point.pos;
        tangent = vec(0,0,0);
        normal = vec(0,0,0);
    }

    /// overloaded constructor IV
    SCustomOutputPoint(SCustomInputPoint t, vec _tangent, vec _normal) 
    {
        pos = t.pos;
        tangent = _tangent;
        normal = _normal;
    }

    /// Operators
    /*
    SCustomOutputPoint operator + (const SCustomOutputPoint b) {
    }
    SCustomOutputPoint operator - (const SCustomOutputPoint b) {
    }
    SCustomOutputPoint operator * (const SCustomOutputPoint b) {
    }
    SCustomOutputPoint operator / (const SCustomOutputPoint b) {
    }
    */
};


/// @brief the standard amount of intepolation steps for curve calculation
#define INEXOR_VSCRIPT_STD_CALC_PRECISION 50

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

    // is the curve already computed?
    bool m_bCacheComputed = false;

    /// TODO: additional protected base members

    public:

    CCurveBase();

    ~CCurveBase();


    /// @brief Set the maximum amount of parameter points
    void SetParameterPointLimit(unsigned int);

    /// @brief Set the computation precision
    void SetCurvePrecision(float);


    /// @brief Adds a parameter point to the curve pool which is used to compute points either in realtime or cached.
    /// @param p paramter point's vector
    void AddParameterPoint(vec);

    /// @brief Adds a parameter point to the curve pool which is used to compute points either in realtime or cached.
    /// @param x x-position of the paramter point
    /// @param y x-position of the paramter point
    /// @param z x-position of the paramter point
    void AddParameterPoint(float, float, float);


    /// ------------------------------------------------------------------------------------------------------------------------
    // REALTIME COMPUTATION

    /// @brief Compute a point in realtime
    /// @warning depending on the calculation precision this may take longer than caching points!
    /// the amount of curves which will be computed in realtime also increases calculation time!
    /// curve points which will be computed in realtime do NOT depend on curve precision because they depent on the value you pass to them!
    virtual SCustomOutputPoint CalcRealtimePoint(float) = 0;

    /// ------------------------------------------------------------------------------------------------------------------------
    /// CACHED COMPUTATION

    /// @warning make sure not to flood m_vInputPoints by adding parameter points in a game loop e.g. Always clear your input points before re-computing in a loop!

    /// Precomputes curve with the precision mentioned above and writes computed points to m_ComputedPoints
    /// @brief Compute the input data to output data
    /// @see m_ComputedPoints
    virtual void ComputeCache() = 0;

    /// @brief Has the input data changed?
    bool IsCurveComputed();

    /// @brief Get size of the computed points vector
    unsigned int GetCachedPointsNumber();
    
    /// @warning May returns wrong index!
    unsigned int GetIndex_ByInterpolationPos(float);

    /// @brief Get a point from the computed curve cache
    SCustomOutputPoint GetPoint_ByInterpolationPos(float);

    /// @brief Get a point from the computed curve cache BY INDEX
    SCustomOutputPoint GetPoint_ByIndex(unsigned int);

    /// @brief delete both parameter points and cached points
    void ClearAllPoints();

    /// @brief delete only parameter points
    void ClearParamPoints();
    
    /// @brief delete only computed points
    void ClearCachePoints();
};

/// end of namespace
};
};

#endif /// INEXOR_GEOM_CURVE_BASE_HEADER
