// Parabola3D.cpp: implementation of the CParabola3D class.
//
//////////////////////////////////////////////////////////////////////




#include "Parabola3D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Parabola3D::Parabola3D()

{
	cType = PARABOLA;
}

Parabola3D::Parabola3D(const AxisSystem& Ax, const double fLen)
{

	itsLocation = Ax;
	focalLength = fLen;
	cType = PARABOLA;
	rangeSet = false;
}

Parabola3D::~Parabola3D()
{

}

void Parabola3D::Reverse()
{
	cReversed = !cReversed;
}

Parabola3D Parabola3D::Reversed() const
{
	Parabola3D P = (*this);
	P.Reverse();
	return P;
}

double Parabola3D::Eccentricity() const
{
	return 1;
}

Point3D Parabola3D::PointAtPara(const double& Par)
{

	Vector3D V;
	double par = Par;

	if(cReversed)
		par = -par;

	V = itsLocation.GetOrigin() + itsLocation.GetXDirection()*par*par/(4.*focalLength) + itsLocation.GetYDirection()*par;
	return V.Point();
}

double Parabola3D::FirstParameter() const
{
	if(!rangeSet)
	{
		return -INFINITY;
	}
	else
		return lowerRange/2*focalLength;
}

double Parabola3D::LastParameter() const
{
	if(!rangeSet)
	{
		return INFINITY;
	}
	else
		return upperRange/2*focalLength;
}

bool Parabola3D::IsClosed() const
{
	return false;
}

bool Parabola3D::operator == (const Parabola3D& L) const
{
	bool b = (itsLocation == L.GetLocation() && focalLength == L.GetFocalLength() 
		&& lowerRange == L.GetLowerRange() && upperRange == L.GetUpperRange());
	return b;
}

void Parabola3D::operator = (const Parabola3D& L)
{
	itsLocation = L.GetLocation();
	focalLength = L.GetFocalLength();
	lowerRange = L.GetLowerRange();
	upperRange = L.GetUpperRange();
}

void Parabola3D::SetLocation(const AxisSystem& Ax)
{
	itsLocation = Ax;
}

AxisSystem Parabola3D::GetLocation() const
{
	return itsLocation;
}

void Parabola3D::SetFocalLength(const double& fLen)
{
	focalLength = fLen;
}

double Parabola3D::GetFocalLength() const
{
	return focalLength;
}

void Parabola3D::SetYRange(const double& lower, const double& upper)
{
	lowerRange = lower;
	upperRange = upper;
	rangeSet = true;
}

double Parabola3D::GetLowerRange() const
{
	return lowerRange;
}

double Parabola3D::GetUpperRange() const
{
	return upperRange;
}

Curve* Parabola3D::Copy() const
{
	Parabola3D* P = new Parabola3D(itsLocation, focalLength);
	P->SetYRange(lowerRange, upperRange);
	return P;
}

void Parabola3D::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void Parabola3D::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx,dy,dz);
}

void Parabola3D::Translate(const Vector3D& V)
{
	itsLocation.Translate(V);
}

void Parabola3D::Translate(const Point3D& P1, const Point3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void Parabola3D::Rotate(const OneAxis& Ax, double fact)
{
	itsLocation.Rotate(Ax, fact);
}

void Parabola3D::Scale(const Point3D& P, double fact)
{
	itsLocation.Scale(P, fact);
	focalLength *= fact;
	lowerRange *= fact;
	upperRange *= fact;
	if(focalLength < 0)
		focalLength = -focalLength;
}

void Parabola3D::Mirror(const Point3D& P)
{
	itsLocation.Mirror(P);
}

void Parabola3D::Mirror(const OneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void Parabola3D::Mirror(const Plane& Pln)
{
	itsLocation.Mirror(Pln);
}
