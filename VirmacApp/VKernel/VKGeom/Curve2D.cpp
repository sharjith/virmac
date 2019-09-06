// Curve.cpp: implementation of the CCurve class.
//
//////////////////////////////////////////////////////////////////////



#include "Curve2D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Curve2D::Curve2D()
{
	cReversed = false;
	geomType = CCURVE2D;
}

Curve2D::~Curve2D()
{

}

Curve2DType Curve2D::Type() const
{
	return cType;
}

bool Curve2D::IsOfType(const Curve2DType& type) const
{
	Curve2DType typ = type;
	bool b = (cType == typ);
	return b;
}

