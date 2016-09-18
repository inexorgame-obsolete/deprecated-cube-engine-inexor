#include <vector>

#include "inexor/math/curves/curvebase.hpp"

namespace inexor {
namespace math {
namespace curves {

    CCurveBase::CCurveBase()
    {
    }


    CCurveBase::~CCurveBase()
    {
    }


    void CCurveBase::SetParameterPointLimit(unsigned int limit)
    {
        m_uiMaxParameterPoints = limit;
    }


    void CCurveBase::AddParameterPoint(vec p)
    {
        // check if parameter point limit was reached or not
        if(m_vInputPoints.size() < m_uiMaxParameterPoints)
        {
            SCustomInputPoint t(p);
            m_vInputPoints.push_back(p);
        }
    }
    void CCurveBase::AddParameterPoint(float x, float y, float z)
    {
        AddParameterPoint(vec(x,y,z));
    }


    void CCurveBase::SetCurvePrecision(float precision)
    {
        m_fComputationPrecision = precision;
    }
    

    bool CCurveBase::IsCurveComputed(void)
    {
        return m_bCacheComputed;
    }


    const unsigned int CCurveBase::GetCachedPointsSize()
    {
        return m_vOutputPoints.size();
    }


    const unsigned int CCurveBase::GetIndex_ByInterpolationPos(float curvepos)
    {
        return ceil((float)curvepos * m_vOutputPoints.size());
    }


    SCustomOutputPoint CCurveBase::GetPoint_ByInterpolationPos(float curvepos)
    {
        assert(IsCurveComputed());

        /// @warning This is NOT tested on any other platform than MS Windows
        return m_vOutputPoints[GetIndex_ByInterpolationPos(curvepos)];
    }


    SCustomOutputPoint CCurveBase::GetPoint_ByIndex(unsigned int index)
    {
        assert(IsCurveComputed());
        assert(index < m_vOutputPoints.size());
        return m_vOutputPoints[index];
    }


    void CCurveBase::ClearAllPoints()
    {
        ClearParamPoints();
        ClearCachePoints();
    }


    void CCurveBase::ClearParamPoints()
    {
        m_vInputPoints.clear();
    }
    

    void CCurveBase::ClearCachePoints()
    {
        m_vOutputPoints.clear();
        m_bCacheComputed = false;
    }

};
};
};
