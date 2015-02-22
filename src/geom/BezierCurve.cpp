void CBezierCurve::AddParamPoint(vec point, float weight)
{
	// check if parameter point limit was reached or not
	if(m_ParameterPoints.size() < m_uiParamLimit)
	{
		SPointStructure p;

		// I want to thank eihrul here for not overloading the damn =+/-*() operators...
		p.x = point.x;
		p.y = point.y;
		p.z = point.z;

		// apply weight
		p.weight = weight;

		// push back (= add) parameter point
		m_ParameterPoints.push_back( p );
	}
}

void CBezierCurve::AddParamPoint(float x, float y, float z, float weight)
{
	// check if parameter point limit was reached or not
	if(m_ParameterPoints.size() < m_uiParamLimit)
	{
		SPointStructure p;
		
		// copy point coordinates and weight
		p.x = x;
		p.y = y;
		p.z = z;
		p.weight = weight;

		// push back (= add) parameter point
		m_ParameterPoints.push_back(p);
	}
}

void CBezierCurve::ClearAllPoints(void)
{
	m_ParameterPoints.clear();
	m_ComputedPoints.clear();
}

void CBezierCurve::ClearComputedPoints(void)
{
	m_ComputedPoints.clear();
}

void CBezierCurve::ClearParameterPoints(void)
{
	m_ParameterPoints.clear();
}

bool CBezierCurve::IsCurveComputed(void)
{
	return m_bComputed;
}

void CBezierCurve::PreComputeCache(BEZIER_ALGORITHM algorithm)
{
	switch(algorithm)
	{
		case ALGORITHM_BERNSTEIN_POLYNOM:
			CalculateCurveCacheWithBernsteinPolynoms();
			break;
		
		case ALGORITHM_DECASTELJAU:
			CalculateCurveCacheWithDeCasteljau();
			break;
	}
}

vec CBezierCurve::GetPointFromCache(float curvepos)
{
	if(!IsCurveComputed()) return vec(0.0f,0.0f,0.0f);
	return m_ComputedPoints[ ceil((float)curvepos*m_ComputedPoints.size()) ];
}

vec CBezierCurve::CalcRealtimePos(
    float curveposition, BEZIER_ALGORITHM algorithm)
{
	vec output;
	switch(algorithm)
	{
		case ALGORITHM_BERNSTEIN_POLYNOM:
			output = calculate_bernstein_coordinates(curveposition);
			break;
		
		case ALGORITHM_DECASTELJAU:
			output = calculate_de_casteljau_coordinate(0, m_ParameterPoints.size(), curveposition/m_fCalcPrecision);
			break;
	}
	return output;
}




// DE CASTELJAU ALGORITHM

void CBezierCurve::CalculateCurveCacheWithDeCasteljau(void)
{
	if(m_ParameterPoints.size() < 2) return;

	SPreComputedPointStructure out;
	for(float curvepos=0.0f; curvepos<=1.0f; curvepos+= 1.0f / m_fCalcPrecision)
	{
		/// where to begin
		int end_number = 0;
		int begin_number = m_ParameterPoints.size()-1;
		
		/// calculate point
		vec p = calculate_de_casteljau_coordinate(begin_number, end_number, curvepos);

		/// copy coordiantes
		out.x = p.x;
		out.y = p.y;
		out.z = p.z;

		/// Add point to computed points list
		m_ComputedPoints.push_back(out);
	}
}

vec CBezierCurve::calculate_de_casteljau_coordinate(int index, int nextindex, float curvepos)
{
	// if index is the first index, stop computing
	if(0 == index) return m_ParameterPoints[nextindex]; // return the first parameter
		
	// return position
	return calculate_de_casteljau_coordinate(index -1, nextindex, curvepos) *(1 - curvepos) + calculate_de_casteljau_coordinate(index-1, nextindex+1, curvepos) * curvepos;
}


/// BERNSTEIN

void CBezierCurve::CalculateCurveCacheWithBernsteinPolynoms(void)
{
	if(m_ParameterPoints.size() < 2) return;

	/// calculate step value using curve precision coefficient
	float fStep = 1.0f / m_fCalcPrecision;

	// go along our curve in fPos steps
	for(float fPos=0.0f;  fPos <= 1.0f;  fPos+=fStep)
	{
		/// compute a new point on the curve
		SPreComputedPointStructure ComputedPoint =  calculate_bernstein_coordinates(fPos);
		/// add the cached point to the curve
		m_ComputedPoints.push_back(ComputedPoint);
	}
	m_bComputed = true;
}

SPreComputedPointStructure CBezierCurve::calculate_bernstein_coordinates(float t)
{
	SPreComputedPointStructure p;
	int n = m_ParameterPoints.size() - 1;

	/// calculate coordinates
	/// @warning if i is UNsigned, pow() function is ambiguous (cast?)
	for(int i=0; i<m_ParameterPoints.size(); i++)
	{
		SPointStructure cur = m_ParameterPoints[i];
		// relative weight coefficient of each point (standard value = 1.0f)
		//float fWeight = m_ParameterPoints[i].weight;

		// compute bezier coordinates using bernstein polynoms
		p.x += /*fWeight */ BinomialCoefficient(n, i) * pow(t, i) * pow(1-t, n-i) * cur.x;
		p.y += /*fWeight */ BinomialCoefficient(n, i) * pow(t, i) * pow(1-t, n-i) * cur.y;
		p.z += /*fWeight */ BinomialCoefficient(n, i) * pow(t, i) * pow(1-t, n-i) * cur.z;
	}

	// Calculate derivatives of bezier curves according to
	// https://www.rose-hulman.edu/~finn/CCLI/Notes/day13.pdf

	// Comment on simplification:
	// An easier way would be to take the vector to the next point on the curve and calculate the difference.
	// This would lead to a direction vector with satisfying precision. But this would implicate that the
	// precision of the derivation depends on the curve precision!
	// With this technique, we can have precise derivations even if we have a precision of only 10.0f units!
	for(int i=0; i<n; i++)
	{
		SPointStructure cur = m_ParameterPoints[i];
		SPointStructure next = m_ParameterPoints[i +1];

		// difference in weights
		//float fDeltaWeight = next.weight - cur.weight;

		/// calculate coordinates
		p.tangent.x += /*(fDeltaWeight) */ BinomialCoefficient(n -1, i) * pow(t, i) * pow(1-t, n -1 -i) * cur.x;
		p.tangent.y += /*(fDeltaWeight) */ BinomialCoefficient(n -1, i) * pow(t, i) * pow(1-t, n -1 -i) * cur.y;
		p.tangent.z += /*(fDeltaWeight) */ BinomialCoefficient(n -1, i) * pow(t, i) * pow(1-t, n -1 -i) * cur.z;
	}
	
	// subtract point position from tangent vector
	// so the tangent vector is relative
	p.tangent = p.tangent.sub(p);

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

