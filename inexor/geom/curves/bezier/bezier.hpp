/// @file BezierCurve.h
/// @brief Bezier curve engine
/// @author Johannes "Hanni" Schneider
/// 
/// IN HONOR OF
/// Pierre Etienne BEZIER       (September 1, 1910 - November 25, 1999)  French mathematician and engineer at Renault
/// Paul de CASTELJAU           (November 19, 1930),                     French mathematician, physicist, and engineer ar Citroen
/// Sergei Natanovich BERNSTEIN (March 5, 1880 - October 26, 1968)       Russian mathematician
/// Charles HERMITE             (December 24, 1822 - January 14, 1901)   French mathematician
/// Leonardo FIBONACCI          (~1170, ~1240)                           Italian mathematician
///
/// TODO: Is DeCasteljau too dangerous because it is recursive?
/// TODO: Maybe generate a random curve?
/// TODO: Use generic types (templates)
/// TODO: Create a curve chain manager (CBezierCurveManager)

#ifndef INEXOR_GEOM_BEZIER_CURVE_HEADER
#define INEXOR_GEOM_BEZIER_CURVE_HEADER

#include <string>
#include <vector>

#include "inexor/geom/curves/curvebase.hpp"

namespace inexor {
namespace geom {

    /// @brief algorithm type enumeration
    enum BEZIER_ALGORITHM
    {
	    ALGORITHM_BERNSTEIN_POLYNOM,
	    ALGORITHM_DECASTELJAU
    };


    /// A bezier curve (named after french mathematician PIERRE ETIENNE BEZIER) is a parametric curve
    /// whose only purpose is to look soft and smooth. Bezier curves are all about their elegance.
    /// Those curves can be used to represent the position of anything you want.
    /// Bezier curves are fast, flexible, beautiful and easy to compute.
    /// Bezier curves are essential in the field of computer graphics and data/image processing.
    /// A collection of useful links and documentations:
    /// http://pomax.github.io/bezierinfo/
    /// http://en.wikipedia.org/wiki/B%C3%A9zier_curve
    /// http://mathworld.wolfram.com/BezierCurve.html
    /// http://theagsc.com/community/tutorials/so-whats-the-big-deal-with-horizontal-vertical-bezier-handles-anyway#comment-1351842776
    /// http://learn.scannerlicker.net/2014/04/16/bezier-curves-and-type-design-a-tutorial/
    /// https://geom.ivd.kit.edu/downloads/pubs/pub-boehm-prautzsch_2002_preview.pdf
    /// https://www.clear.rice.edu/comp360/lectures/BezSubd.pdf
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
    
            /// every curve class needs to implement this virtual function
            void ComputeCache();

            SCustomOutputPoint CalcRealtimePoint(float curvepos);

    };

};
};

#endif
