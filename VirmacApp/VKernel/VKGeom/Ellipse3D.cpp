// Ellipse3D.cpp: implementation of the CEllipse3D class.
//
//////////////////////////////////////////////////////////////////////


#include "Ellipse3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ellipse3D::Ellipse3D()
{
	cType = ELLIPSE;
}

Ellipse3D::Ellipse3D(const Point3D& cp, const double min, const double maj) : minorRadius(min)
, majorRadius(maj)
{
	AxisSystem ax(cp, Vector3D(0,0,1), Vector3D(1,0,0));
	itsLocation = ax;
	cType = ELLIPSE;
}

Ellipse3D::Ellipse3D(const AxisSystem& Ax, double min, double maj) : minorRadius(min), majorRadius(maj)
{
	itsLocation = Ax;
	cType = ELLIPSE;
}

Ellipse3D::~Ellipse3D()
{
}

void Ellipse3D::Reverse()
{
	cReversed = !cReversed;
}

Ellipse3D Ellipse3D::Reversed() const
{
	Ellipse3D E = (*this);
	E.Reverse();
	return E;
}

double Ellipse3D::Eccentricity() const
{
	if(majorRadius == 0.0)
		return 0.0;
	else
		return sqrt(majorRadius * majorRadius - 
		minorRadius * minorRadius) / majorRadius;
}

Point3D Ellipse3D::PointAtPara(const double& Par)
{
	Vector3D V;
	double para = Par;

	if(cReversed)
		para = 2*PI - para;

	double c = cos(para);
	double s = sin(para);
	V = itsLocation.GetOrigin() + itsLocation.GetXDirection()*majorRadius*c
		+ itsLocation.GetYDirection()*minorRadius*s;

	return V.Point();
}

bool Ellipse3D::IsClosed() const
{
	return true;
}

bool Ellipse3D::operator == (const Ellipse3D& E) const
{
	bool eq = (itsLocation == E.GetLocation() && majorRadius == E.GetMajorRadius()
				&& minorRadius == E.GetMinorRadius());
	return eq;
}

void Ellipse3D::operator = (const Ellipse3D& E)
{
	itsLocation = E.GetLocation();
	majorRadius = E.GetMajorRadius();
	minorRadius = E.GetMinorRadius();
}

Curve* Ellipse3D::Copy() const
{
	Ellipse3D* E = new Ellipse3D(itsLocation, majorRadius, minorRadius);
	return E;
}

void Ellipse3D::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void Ellipse3D::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx,dy,dz);
}

void Ellipse3D::Translate(const Vector3D& V)
{
	itsLocation.Translate(V);
}

void Ellipse3D::Translate(const Point3D& P1, const Point3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void Ellipse3D::Rotate(const OneAxis& Ax, double fact)
{
	itsLocation.Rotate(Ax, fact);
}

void Ellipse3D::Scale(const Point3D& P, double fact)
{
	itsLocation.Scale(P, fact);
	majorRadius *= fact;
	minorRadius *= fact;
	if(majorRadius < 0)
		majorRadius = -majorRadius;
	if(minorRadius < 0)
		minorRadius = -minorRadius;
}

void Ellipse3D::Mirror(const Point3D& P)
{
	itsLocation.Mirror(P);
}

void Ellipse3D::Mirror(const OneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void Ellipse3D::Mirror(const Plane& Pln)
{
	itsLocation.Mirror(Pln);
}
