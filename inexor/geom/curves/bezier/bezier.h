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


/// TODO: Is DeCasteljau too dangerous because it is recursive?
/// TODO: Generate a random curve?
/// TODO: Use generic types (templates)
/// TODO: Create a curve chain manager (CBezierCurveManager)

#ifndef INEXOR_GEOM_BEZIER_CURVE_HEADER
#define INEXOR_GEOM_BEZIER_CURVE_HEADER

#include <string>
#include <vector>

#include "inexor/geom/curves/curvebase.h"

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
    
            BEZIER_ALGORITHM engine_algorithm;

            const unsigned int BinomialCoefficient(unsigned int n, const unsigned int k);

            void CalculateCurveCacheWithBernsteinPolynoms();
    
            void CalculateCurveCacheWithDeCasteljau();

            SCustomOutputPoint calculate_de_casteljau_coordinate(int index, int nextindex, float t);

            SCustomOutputPoint calculate_bernstein_coordinates(float position);

        public:

            CBezierCurve();

            ~CBezierCurve();

            void SetAlgorithm(BEZIER_ALGORITHM algorithm);
    
            void ComputeCache();

            SCustomOutputPoint CalcRealtimePoint(float curvepos);

    };

};
};

#endif
