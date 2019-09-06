// Helix.cpp: implementation of the CHelix class.
//
//////////////////////////////////////////////////////////////////////


#include "Helix.h"

#include "Point3D.h"
#include "Vector3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Helix::Helix(const AxisSystem& Ax, const double& radius, const double& start, const double& end, const double lead) : itsLead(lead)
{
	itsLocation = Ax;
	itsRadius = radius;
	itsFirstParameter = start;
	itsLastParameter = end;
}

Helix::~Helix()
{

}

void Helix::Reverse()
{
}

Point3D Helix::PointAtPara(const double& Par)
{
	Point3D P; Vector3D V;
	double para = Par;

	double c = cos(para);
	double s = sin(para);
	double v = ((para-itsFirstParameter)/(PI*2))*itsLead;
	V = itsLocation.GetOrigin()+(itsLocation.GetXDirection()*c+itsLocation.GetYDirection()*s)
			*GetRadius()+itsLocation.GetDirection()*v;
	P.SetParam(V.GetX(), V.GetY(), V.GetZ());

	return P;
}

double Helix::FirstParameter() const
{
	return itsFirstParameter;
}

double Helix::LastParameter() const
{
	return itsLastParameter;
}

bool Helix::IsClosed() const
{
	return false;
}

CurveType Helix::Type() const
{
	return HELIX;
}

bool Helix::IsOfType(const CurveType& theType) const
{
	bool b = (theType == HELIX);
	return b;
}

Curve* Helix::Copy() const
{
	Helix* H = new Helix(itsLocation, itsRadius, itsFirstParameter, itsLastParameter, itsLead);
	return H;
}

void Helix::Translate(double /*dx*/, double /*dy*/, double /*dz*/)
{
}

void Helix::Translate(const Vector3D&)
{
}

void Helix::Translate(const Point3D&, const Point3D&)
{
}

void Helix::Rotate(const OneAxis&, double)
{
}

void Helix::Scale(const Point3D&, double)
{
}

void Helix::Mirror(const Point3D&)
{
}

void Helix::Mirror(const OneAxis&)
{
}

void Helix::Mirror(const Plane&)
{
}
