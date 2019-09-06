// Hyperbola3D.cpp: implementation of the CHyperbola3D class.
//
//////////////////////////////////////////////////////////////////////

#include "Hyperbola3D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Hyperbola3D::Hyperbola3D()
{
	cType = HYPERBOLA;
}

Hyperbola3D::Hyperbola3D(const AxisSystem& Ax, const double& maj, const double& min) : majorRadius(maj), minorRadius(min)
{
	itsLocation = Ax;
	cType = HYPERBOLA;
}

Hyperbola3D::~Hyperbola3D()
{

}

void Hyperbola3D::Reverse()
{
	cReversed = !cReversed;
}

Hyperbola3D Hyperbola3D::Reversed() const
{
	Hyperbola3D H = (*this);
	H.Reverse();
	return H;
}

double Hyperbola3D::Eccentricity() const
{
	return (sqrt(majorRadius*majorRadius + minorRadius*minorRadius))/majorRadius;
}

Point3D Hyperbola3D::PointAtPara(const double& Par)
{
	Vector3D V;
	double par = Par;

	if(cReversed)
		par = -par;

	double ch = cosh(par);
	double sh = sinh(par);
	V = itsLocation.GetOrigin() + itsLocation.GetXDirection()*majorRadius*ch + itsLocation.GetYDirection()*minorRadius*sh;
	return V.Point();
}

double Hyperbola3D::FirstParameter() const
{
	return -2*PI;
}

double Hyperbola3D::LastParameter() const
{
	return 2*PI;
}

bool Hyperbola3D::IsClosed() const
{
	return false;
}

bool Hyperbola3D::operator == (const Hyperbola3D& L) const
{
	bool b = (itsLocation == L.GetLocation() &&	majorRadius == L.GetMajorRadius()
			&& minorRadius == L.GetMinorRadius());
	return b;
}

void Hyperbola3D::operator = (const Hyperbola3D& L)
{
	itsLocation = L.GetLocation();
	majorRadius = L.GetMajorRadius();
	minorRadius = L.GetMinorRadius();
}

void Hyperbola3D::SetMinorRadius(const double& rad)
{
	minorRadius = rad;
}

void Hyperbola3D::SetMajorRadius(const double& rad)
{
	majorRadius = rad;
}

double Hyperbola3D::GetMinorRadius() const
{
	return minorRadius;
}

double Hyperbola3D::GetMajorRadius() const
{
	return majorRadius;
}

Hyperbola3D Hyperbola3D::GetConjugateBranch1() const
{
	Vector3D Dir = itsLocation.GetYDirection();
	AxisSystem Ax(itsLocation.GetPosition(), itsLocation.GetDirection(), Dir);
	Hyperbola3D H(Ax, minorRadius, majorRadius);
	return H;
}

Hyperbola3D Hyperbola3D::GetConjugateBranch2() const
{
	Vector3D Dir = itsLocation.GetYDirection();
	Dir.Reverse();
	AxisSystem Ax(itsLocation.GetPosition(), itsLocation.GetDirection(), Dir);
	Hyperbola3D H(Ax, minorRadius, majorRadius);
	return H;
}

Hyperbola3D Hyperbola3D::GetOtherBranch() const
{
	Vector3D Dir = itsLocation.GetXDirection();
	Dir.Reverse();
	AxisSystem Ax(itsLocation.GetPosition(), itsLocation.GetDirection(), Dir);
	Hyperbola3D H(Ax, majorRadius, minorRadius);
	return H;
}

void Hyperbola3D::SetLocation(const AxisSystem& ax)
{
	itsLocation = ax;
}

AxisSystem Hyperbola3D::GetLocation() const
{
	return itsLocation;
}

double Hyperbola3D::FocalLength() const
{
	return 2.0 * sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
}

Curve* Hyperbola3D::Copy() const
{
	Hyperbola3D* H = new Hyperbola3D(itsLocation, majorRadius, minorRadius);
	return H;
}

void Hyperbola3D::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void Hyperbola3D::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx,dy,dz);
}

void Hyperbola3D::Translate(const Vector3D& V)
{
	itsLocation.Translate(V);
}

void Hyperbola3D::Translate(const Point3D& P1, const Point3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void Hyperbola3D::Rotate(const OneAxis& Ax, double fact)
{
	itsLocation.Rotate(Ax, fact);
}

void Hyperbola3D::Scale(const Point3D& P, double fact)
{
	itsLocation.Scale(P, fact);
	majorRadius *= fact;
	minorRadius *= fact;
	if(majorRadius < 0)
		majorRadius = -majorRadius;
	if(minorRadius < 0)
		minorRadius = -minorRadius;
}

void Hyperbola3D::Mirror(const Point3D& P)
{
	itsLocation.Mirror(P);
}

void Hyperbola3D::Mirror(const OneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void Hyperbola3D::Mirror(const Plane& Pln)
{
	itsLocation.Mirror(Pln);
}
