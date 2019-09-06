// Curve.cpp: implementation of the CCurve class.
//
//////////////////////////////////////////////////////////////////////



#include "Curve.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Curve::Curve()
{
	cReversed = false;
	geomType = CCURVE;
}

Curve::~Curve()
{

}

CurveType Curve::Type() const
{
	return cType;
}

bool Curve::IsOfType(const CurveType& type) const
{
	CurveType typ = type;
	bool b = (cType == typ);
	return b;
}

