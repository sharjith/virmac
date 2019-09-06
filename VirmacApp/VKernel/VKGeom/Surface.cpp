// Surface.cpp: implementation of the CSurface class.
//
//////////////////////////////////////////////////////////////////////



#include "Surface.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Surface::Surface()
{
	geomType = CSURFACE;
}

Surface::~Surface()
{

}

SurfaceType Surface::Type() const
{
	return sType;
}

Vector3D Surface::NormalAt(const double uPar, const double vPar)
{
	Point3D Po = PointAtPara(uPar, vPar);
	Point3D Pu = PointAtPara(uPar+0.000001, vPar);
	Point3D Pv = PointAtPara(uPar+0.000001, vPar+0.000001);
	Vector3D Vu(Po, Pu);
	Vector3D Vv(Po, Pv);
	Vector3D N = Vu^Vv;
	N.Normalize();
	return N;
}

bool Surface::IsOfType(const SurfaceType& type) const
{
	SurfaceType typ = type;
	bool b = (sType == typ);
	return b;
}
