/// @file BezierCurve.h
/// @author Johannes "Hanni" Schneider
/// @brief Bezier curve generator engine

// TODO: Do we need the fWeight coefficients? 
// TODO: Derivation (tangent/normal vector) for deCasteljau?
// TODO: Is DeCasteljau dangerous because it is recursive?
// TODO: Better access for control/parameter points
// TODO: Generate a random curve?
// TODO: Should we move these structures into the class
// TODO: use generic types (templates)

#ifndef INEXOR_GEOM_BEZIER_CURVE_HEADER
#define INEXOR_GEOM_BEZIER_CURVE_HEADER

#include "engine.h"

#include <string>
#include <vector>

namespace inexor {
namespace geom {



/// custom inherited point structures to store additional data
/// all vector members have float as type, double precision is not neccesary!
struct SPointStructure : public vec
{
	/// maybe we should give different points more/less weight!
	float weight;

	/// Reser coordinates in constructor!
	SPointStructure() : vec(0.0f,0.0f,0.0f) /// initialise inherited members in constructor list
	{
		// customize constructor here
		weight = 1.0f;
	}
};

/// structure to describe pre-computed (cached) points
/// cached points remain static and will have to be updated (recomputed)
/// after (at least) one parameter point has changed significantly!
struct SPreComputedPointStructure : public SPointStructure
{
	/// normal vector stands 90� to the curve's current position
	vec normal;

	/// tangent vector leaves the curve in point p tangentially
	/// it is computed using the curve's 1st derivation
	vec tangent;

	/// constructor
	SPreComputedPointStructure()
	{
		normal  = vec(0.0f,0.0f,0.0f);
		tangent = vec(0.0f,0.0f,0.0f);
	}
};


/// algorithm type enumeration
enum BEZIER_ALGORITHM
{
	ALGORITHM_BERNSTEIN_POLYNOM,
	ALGORITHM_DECASTELJAU
};

/// Single Bezier curve manger
///
/// INTRODUCTION
/// A bezier curve (named after french mathematician PIERRE ETIENNE BEZIER) is a parametric curve
/// whose only purpose is to look soft and smooth. Bezier curves are all about elegance!
/// Those curves can be used to represent the path of a everything (imagina a moving camera for example).
///
/// Bezier curves are fast, flexible, beautiful and easy to compute. You just pass a bunch of parameter points to
/// your code and the final curve will be computed. Because every complex curve can be represented with a 
/// chain of smaller curves, it is recommended to create a chain of curves.
/// Bezier curves are ESSENTIAL AND FUNDAMENTAL in the field of computer graphics and image processing. Also can
/// they be used for approximation, interpolation and more.
///
/// COMPUTING
/// There are two ways to generate a bezier curves from a group of [n] points.
/// You can either write a code that uses recursion to solve the problem or use Bernstein Polynoms.
/// Both ways will be implemented in this engine.
///
/// 	Method 1: Bernstein Polynoms ***HIGHLY RECOMMENDED***
/// 	-uses brilliant math to resolve the recursion and turn all the problems into more or less simple terms.
/// 	Method 1: De-Casteljau-Algorithm (recursive!)
/// 	-possibly needs a lot of memory for every sub-call (not sure)
/// 	-possibly violates the theory of an algorithm (because is has to end somewhere)
///
/// IN HONOR OF
/// Pierre Etienne BEZIER       (September 1, 1910 - November 25, 1999), French mathematician and engineer at RENAULT
/// Paul de CASTELJAU           (November 19, 1930), French mathematician and physicist and engineer at Citroen
/// Sergei Natanovich BERNSTEIN (March 5, 1880 - October 26, 1968), Russian mathematician
/// Charles HERMITE             (December 24, 1822 - January 14, 1901), French mathematician
/// Leonardo FIBONACCI          (~1170, ~1240), Italian mathematician
///
/// http://pomax.github.io/bezierinfo/
/// http://en.wikipedia.org/wiki/B%C3%A9zier_curve
/// http://mathworld.wolfram.com/BezierCurve.html
/// http://theagsc.com/community/tutorials/so-whats-the-big-deal-with-horizontal-vertical-bezier-handles-anyway#comment-1351842776
/// http://learn.scannerlicker.net/2014/04/16/bezier-curves-and-type-design-a-tutorial/
/// https://geom.ivd.kit.edu/downloads/pubs/pub-boehm-prautzsch_2002_preview.pdf
/// https://www.clear.rice.edu/comp360/lectures/BezSubd.pdf
///
class CBezierCurve
{
public:

  /// a std::vector which contains all parameter points passed to the engine
  std::vector<SPointStructure> m_ParameterPoints;

  /// precomputed points are used to cache the processed curve
  /// which can be faster than computing every point on it in realtime
  std::vector<SPreComputedPointStructure> m_ComputedPoints;
      

  /// please note: start and end point are just parameter points as well!


  /// set the limit of parameter points
  /// @param limit the maximal amount of parameter points which can be passed to the engine
  void SetParamPointLimit(unsigned int input_point_limit) {
    m_uiParamLimit = input_point_limit;
  }

  /// set the precision of the precomputed points
  /// @param precision the precision level. Higher values mean higher precision.
  void SetCachedCurvePrecision(float precision) {
    m_fCalcPrecision = precision;
  }


  /// curve points which will be computed in realtime do NOT depend on curve precision
  /// because they depent on the value you pass to them!


  /// Add a parameter point
  /// @brief adds a parameter point to the curve pool which is used to compute points either in realtime or cached!
  /// @param x x-position of the paramter point
  /// @param y x-position of the paramter point
  /// @param z x-position of the paramter point
  /// @param weight relative weight of this point (standard value: 1.0f)
  void AddParamPoint(float x, float y, float z, float weight = 1.0f);



  /// Add a parameter point (function overload: vector as parameter)
  /// @brief adds a parameter point to the curve pool which is used to compute points either in realtime or cached!
  /// @param point paramter point's vector
  /// @param weight relative weight of this point (standard value: 1.0f)
  void AddParamPoint(vec point, float weight = 1.0f);

  

  /// Delete both parameter points and cached points 
  void ClearAllPoints(void);

  /// Delete only parameter points
  void ClearParameterPoints(void);

  /// Delete only computed points
  void ClearComputedPoints(void);

  // PRECOMPUTE AND ACCESS CURVE POINT BUFFER (NO REALTIME)

  /// is curve already computed?
  bool IsCurveComputed(void);

  /// Precompute curve to cache
  /// Precomputes curve with the precision mentioned above and writes computed points to m_ComputedPoints
  /// @param algo the algorithm which will be used to precompute the curve (standard value: ALGORITHM_BERNSTEIN_POLYNOM)
  /// @see m_ComputedPoints
  void PreComputeCache(BEZIER_ALGORITHM algorithm = ALGORITHM_BERNSTEIN_POLYNOM);

  /// Get a vector from the cached data
  vec GetPointFromCache(float curvepos);

  /// Returns the index of the nearest point available for this float value
  /// @param curvepos float value for curve interpolation (between 0.0f and 1.0f)
  //unsigned int GetCachedPointIndex(float curvepos);
  

  // REALTIME GENERATION OF A POINT USING THE ALGORITHMS

  /// Generate a point on the curve from the parameter points with a specified algorithm
  /// This point will be computed in REALTIME!
  vec CalcRealtimePos(float curveposition, BEZIER_ALGORITHM algorithm);


protected:

  /// Maximal amount of parameter points
  unsigned int m_uiParamLimit = 4;
  /// The precision with which the curve point cache will be computed
  float m_fCalcPrecision = 50;
  /// Is the curve point cache already precomputed?
  bool m_bComputed = false;


  /// Binomial coefficient
  unsigned int BinomialCoefficient(unsigned int n, const unsigned int k)
  {
    unsigned int r = 1;
    if(k > n) return 0;
    for(unsigned int d=1; d<=k; d++) 
    {
      r *= n--;
      r /= d;
    }
    return r;
  }


  /// Calculate using Bernstein polynoms (not recursive)
  void CalculateCurveCacheWithBernsteinPolynoms(void);
  
  /// Calculare using recursion 
  /// @warning It is not clear in how far this produces overhead!
  void CalculateCurveCacheWithDeCasteljau(void);


  /// de Casteljau algorithm (recursive)
  /// this function has type vector because it may returns computed points
  /// and parameter points as well!
  vec calculate_de_casteljau_coordinate(int index, int nextindex, float t);

  /// bernstein-bezier algorithm (not recursive)
  SPreComputedPointStructure calculate_bernstein_coordinates(float position);
};


}; // Namespace "geom"
}; // Namespace "inexor"

#endif // INEXOR_GEOM_BEZIER_CURVE_HEADER
