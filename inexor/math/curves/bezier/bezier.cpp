#include "bezier.hpp"

namespace inexor {
namespace math {
namespace curves {

    CBezierCurve::CBezierCurve()
    {
        SetAlgorithm(ALGORITHM_BERNSTEIN_POLYNOM);
    }

    CBezierCurve::~CBezierCurve()
    {
    }

    
    void CBezierCurve::SetAlgorithm(BEZIER_ALGORITHM algorithm)
    {
        engine_algorithm = algorithm;
    }


    void CBezierCurve::ComputeCache()
    {
        switch (engine_algorithm)
        {
            case ALGORITHM_BERNSTEIN_POLYNOM:
                CalculateCurveCacheWithBernsteinPolynoms();
                break;

            case ALGORITHM_DECASTELJAU:
                CalculateCurveCacheWithDeCasteljau();
                break;
        }
    }
    

    SCustomOutputPoint CBezierCurve::CalcRealtimePoint(float curvepos)
    {
        SCustomOutputPoint output;
        switch(engine_algorithm)
        {
            case ALGORITHM_BERNSTEIN_POLYNOM:
                output = calculate_bernstein_coordinates(curvepos);
                break;

            case ALGORITHM_DECASTELJAU:
                output = calculate_de_casteljau_coordinate(0, m_vInputPoints.size(), curvepos / m_fComputationPrecision);
                break;
        }
        return output;
    }

    
    const unsigned int CBezierCurve::BinomialCoefficient(unsigned int n, const unsigned int k)
    {
        unsigned int r = 1;
        if(k > n) return 0;
        for(unsigned int d=1; d<=k; d++) {
            r *= n--;
            r /= d;
        }
        return r;
    }


    SCustomOutputPoint CBezierCurve::calculate_de_casteljau_coordinate(int index, int nextindex, float curvepos)
    {
        // if index is the first index, stop computing
        if (0 == index) return m_vInputPoints[nextindex]; // return the first parameter
        // calculate position. tangent and normal vectors will be computed separatedly later on.
        SCustomOutputPoint ret;
        ret.pos = calculate_de_casteljau_coordinate(index - 1, nextindex, curvepos).pos * (1 - curvepos) + calculate_de_casteljau_coordinate(index - 1, nextindex + 1, curvepos).pos * curvepos;
        return ret;
    }


    void CBezierCurve::CalculateCurveCacheWithDeCasteljau(void)
    {
        if(m_vInputPoints.size() < 2) return;

        for(float curvepos = 0.0f; curvepos <= 1.0f; curvepos += 1.0f / m_fComputationPrecision)
        {
            int end_number = 0;
            int begin_number = m_vInputPoints.size() - 1;
            SCustomOutputPoint out(calculate_de_casteljau_coordinate(begin_number, end_number, curvepos));
            m_vOutputPoints.push_back(out);
        }
    }


    SCustomOutputPoint CBezierCurve::calculate_bernstein_coordinates(float t)
    {
        SCustomOutputPoint p;
        int n = m_vInputPoints.size() - 1;

        /// calculate coordinates
        /// @warning if i is UNsigned, pow() function is ambiguous (cast?)
        for (int i = 0; i < m_vInputPoints.size(); i++)
        {
            SCustomOutputPoint cur(m_vInputPoints[i]);
            // compute bezier coordinates using bernstein polynoms
            p.pos.x += BinomialCoefficient(n, i) * pow(t, i) * pow(1 - t, n - i) * cur.pos.x;
            p.pos.y += BinomialCoefficient(n, i) * pow(t, i) * pow(1 - t, n - i) * cur.pos.y;
            p.pos.z += BinomialCoefficient(n, i) * pow(t, i) * pow(1 - t, n - i) * cur.pos.z;
        }

        // Calculate derivatives of bezier curves according to
        // https://www.rose-hulman.edu/~finn/CCLI/Notes/day13.pdf

        // Comment on simplification:
        // An easier way would be to take the vector to the next point on the curve and calculate the difference.
        // This would lead to a direction vector with satisfying precision. But this would implicate that the
        // precision of the derivation depends on the curve precision!
        // With this technique, we can have precise derivations even if we have a precision of only 10.0f units!
        for (int i = 0; i < n; i++)
        {
            SCustomInputPoint cur = m_vInputPoints[i];
            SCustomInputPoint next = m_vInputPoints[i + 1];

            /// calculate coordinates
            p.tangent.x += BinomialCoefficient(n - 1, i) * pow(t, i) * pow(1 - t, n - 1 - i) * cur.pos.x;
            p.tangent.y += BinomialCoefficient(n - 1, i) * pow(t, i) * pow(1 - t, n - 1 - i) * cur.pos.y;
            p.tangent.z += BinomialCoefficient(n - 1, i) * pow(t, i) * pow(1 - t, n - 1 - i) * cur.pos.z;
        }

        // subtract point position from tangent vector
        // so the tangent vector is relative
        p.tangent = p.tangent.sub(p.pos);

        // NOTE: There is more than -one- normal vector to another vector!

        // calculate relative normal vector
        float len = p.tangent.magnitude();
        p.normal = vec(-p.tangent.y / len, p.tangent.x / len, 0);

        // NOTE: Do -NOT- normalize tangent vector before you have copied the normal vector! They will be incorrect!

        // normalise vector: divide by length
        // so vector length is 1 (all have the same length)
        p.normal.normalize();
        p.tangent.normalize();

        // NOTE: use vector.rescale(floatval); to change the length according to your wish!
        //p.tangent.rescale(100.0f);
        //p.normal.rescale(100.0f);

        // return finished point for interpolation value t
        return p;
    }

    void CBezierCurve::CalculateCurveCacheWithBernsteinPolynoms(void)
    {
        if(m_vInputPoints.size() < 2) return;

        /// calculate step value using curve precision coefficient
        float fStep = 1.0f / m_fComputationPrecision;

        // go along our curve in fPos steps
        for (float fPos = 0.0f; fPos <= 1.0f; fPos += fStep)
        {
            SCustomOutputPoint ComputedPoint(calculate_bernstein_coordinates(fPos));
            m_vOutputPoints.push_back(ComputedPoint);
        }
        m_bCacheComputed = true;
    }

};
};
};
