// ExtrudedSurface.cpp: implementation of the CExtrudedSurface class.
//
//////////////////////////////////////////////////////////////////////


#include "ExtrudedSurface.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExtrudedSurface::ExtrudedSurface(const Curve* C, const Vector3D& Dir, const double& s, const double& e) : startLimit(s), endLimit(e)
{
	sType = EXTRUDED;
	baseCurve = C->Copy();
	itsDirection = Dir;
}

ExtrudedSurface::~ExtrudedSurface()
{
	if(baseCurve)
		delete baseCurve;
}

Point3D ExtrudedSurface::PointAtPara(const double uPar, const double vPar)
{
	Vector3D P;
	Vector3D G(baseCurve->PointAtPara(uPar));
	Vector3D Dir = itsDirection*vPar;
	P = G+Dir;
	return P.Point();
}

double ExtrudedSurface::FirstUParameter() const
{
	return baseCurve->FirstParameter();
}

double ExtrudedSurface::LastUParameter() const
{
	return baseCurve->LastParameter();
}

double ExtrudedSurface::FirstVParameter() const
{
	return startLimit;
}

double ExtrudedSurface::LastVParameter() const
{
	return endLimit;
}

bool ExtrudedSurface::IsUClosed() const
{
	return baseCurve->IsClosed();
}

bool ExtrudedSurface::IsVClosed() const
{
	return false;
}

Surface* ExtrudedSurface::Copy() const
{
	ExtrudedSurface* R = new ExtrudedSurface(baseCurve, itsDirection, startLimit, endLimit);
	return R;
}

void ExtrudedSurface::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void ExtrudedSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
}

void ExtrudedSurface::Translate(const Vector3D& V)
{
	baseCurve->Translate(V);
}

void ExtrudedSurface::Translate(const Point3D& P1, const Point3D& P2)
{
	baseCurve->Translate(P1, P2);
}

void ExtrudedSurface::Rotate(const OneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
}

void ExtrudedSurface::Scale(const Point3D& P, double fact)
{
	baseCurve->Scale(P, fact);
}

void ExtrudedSurface::Mirror(const Point3D& P)
{
	baseCurve->Mirror(P);
}

void ExtrudedSurface::Mirror(const OneAxis& Ax)
{
	baseCurve->Mirror(Ax);
}

void ExtrudedSurface::Mirror(const Plane& Pln)
{
	baseCurve->Mirror(Pln);
}
