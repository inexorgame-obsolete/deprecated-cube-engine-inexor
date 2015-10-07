/// @file BezierCurve.h
/// @brief Bezier curve generator engine
/// @author Johannes "Hanni" Schneider
/// 
/// IN HONOR OF
/// 
/// Pierre Etienne BEZIER       (September 1, 1910 - November 25, 1999), French mathematician and engineer at Renault
/// Paul de CASTELJAU           (November 19, 1930), French mathematician and physicist  and engineer ar Citroen
/// Sergei Natanovich BERNSTEIN (March 5, 1880 - October 26, 1968), Russian mathematician
/// Charles HERMITE             (December 24, 1822 - January 14, 1901), French mathematician
/// Leonardo FIBONACCI          (~1170, ~1240), Italian mathematician
///
/// A collection of useful links and documentations:
/// http://pomax.github.io/bezierinfo/
/// http://en.wikipedia.org/wiki/B%C3%A9zier_curve
/// http://mathworld.wolfram.com/BezierCurve.html
/// http://theagsc.com/community/tutorials/so-whats-the-big-deal-with-horizontal-vertical-bezier-handles-anyway#comment-1351842776
/// http://learn.scannerlicker.net/2014/04/16/bezier-curves-and-type-design-a-tutorial/
/// https://geom.ivd.kit.edu/downloads/pubs/pub-boehm-prautzsch_2002_preview.pdf
/// https://www.clear.rice.edu/comp360/lectures/BezSubd.pdf


/// TODO: Is DeCasteljau dangerous because it is recursive?
/// TODO: Better access for control/parameter points
/// TODO: Generate a random curve?
/// TODO: use generic types (templates)
/// TODO: Create a curve chain manager (CBezierCurveManager)


// include guard protects this file from being included twice
#ifndef INEXOR_GEOM_BEZIER_CURVE_HEADER
#define INEXOR_GEOM_BEZIER_CURVE_HEADER

/// C++ standard libraries
#include <string>
#include <vector>

/// include the base class for curves
#include "inexor/geom/curves/curvebase.h"


/// inexor security namespace
namespace inexor {
namespace geom {


/// @brief algorithm type enumeration
/// There are two ways to generate a bezier curves from a group of [n] points. Both ways will be implemented in this engine.
/// 
/// ALGORITHM_BERNSTEIN_POLYNOM (Bernstein Polynomials)
/// -not recursive
/// -will automaticly compute and norm the tangent and normal vectors for every computed point
/// 
/// ALGORITHM_DECASTELJAU (De-Casteljau-Algorithm)
/// -recursive! use with caution!
/// -possibly needs a lot more memory for every sub-call (?)
/// -proven to be a little faster than the other algorithm
enum BEZIER_ALGORITHM
{
	ALGORITHM_BERNSTEIN_POLYNOM,
	ALGORITHM_DECASTELJAU
};


/// A bezier curve (named after french mathematician PIERRE ETIENNE BEZIER) is a parametric curve
/// whose only purpose is to look soft and smooth. Bezier curves are all about their elegance.
/// Those curves can be used to represent everything you can imagine: particles, cameras, mapmodels and much more.
/// Bezier curves are fast, flexible, beautiful and easy to compute. You just pass a bunch of parameter points to
/// this engine and the final curve will be computed. Because every complex curve can be represented with a 
/// chain of smaller curves, it is recommended to create a chain of curves. See CBezierCurveManager.
/// Bezier curves are ESSENTIAL AND FUNDAMENTAL in the field of computer graphics and data/image processing.
/// They can also be used for approximation, interpolation and more.
class CBezierCurve : public CCurveBase
{
    protected:

    /// binomial coefficient (n over k)
    unsigned int BinomialCoefficient(unsigned int n, const unsigned int k);

    /// Calculate using Bernstein polynoms (not recursive)
    void CalculateCurveCacheWithBernsteinPolynoms();
  
    /// Calculare using recursion 
    /// @warning It is not clear in how far this produces memory leaks or overhead!
    void CalculateCurveCacheWithDeCasteljau();

    /// de Casteljau algorithm (recursive)
    /// this function has type vector because it may returns computed points
    /// and parameter points as well!
    SCustomOutputPoint calculate_de_casteljau_coordinate(int index, int nextindex, float t);
    /// bernstein-bezier algorithm (not recursive)
    SCustomOutputPoint calculate_bernstein_coordinates(float position);

    public:

    // constructor
    //CBezierCurve();
    // destructor
    //~CCurveBase();


    /// set the maximum of parameter points
    void SetParameterPointLimit(unsigned int limit);

    /// Add a parameter point I
    /// @brief adds a parameter point to the curve pool which is used to compute points either in realtime or cached!
    /// @param p paramter point's vector
    void AddParameterPoint(vec p);

    /// Add a parameter point II
    /// @brief adds a parameter point to the curve pool which is used to compute points either in realtime or cached!
    /// @param x x-position of the paramter point
    /// @param y x-position of the paramter point
    /// @param z x-position of the paramter point
    void AddParameterPoint(float x, float y, float z);


    /// @brief set the computation precision
    void SetCurvePrecision(float precision);
    /// @brief set the computation precision for the cached curve
    void SetCachedCurvePrecision(float precision);
    
    // realtime computation

    /// @brief Compute a point in realtime
    /// @warning depending on the calculation precision this may take longer than caching points!
    /// the amount of curves which will be computed in realtime also increases calculation time!
    /// curve points which will be computed in realtime do NOT depend on curve precision because they depent on the value you pass to them!
    SCustomOutputPoint CalcRealtimePos(float curvepos, BEZIER_ALGORITHM algorithm);

    /// cached computation

    /// @brief Has the input data changed?
    bool IsCurveComputed();

    /// @brief Compute the input data to output data
    void ComputeCache();

    /// @brief Get a point from the computed curve cache
    SCustomOutputPoint GetPointFromCache(float curvepos);

    /// @warning make sure not to flood m_vInputPoints 
    /// by adding parameter points in a game loop e.g.


    /// @brief delete both parameter points and cached points
    void ClearAllPoints();
    /// @brief delete only parameter points
    void ClearParamPoints();
    /// @brief delete only computed points
    void ClearCachePoints();

    /// Precompute curve to cache
    /// Precomputes curve with the precision mentioned above and writes computed points to m_ComputedPoints
    /// @param algo the algorithm which will be used to precompute the curve (standard value: ALGORITHM_BERNSTEIN_POLYNOM)
    /// @see m_ComputedPoints
    void PreComputeCache(BEZIER_ALGORITHM algorithm = ALGORITHM_BERNSTEIN_POLYNOM);

};

}; // Namespace "geom"
}; // Namespace "inexor"

#endif // INEXOR_GEOM_BEZIER_CURVE_HEADER
