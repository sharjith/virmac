// RevolvedSurface.cpp: implementation of the CRevolvedSurface class.
//
//////////////////////////////////////////////////////////////////////





#include "RevolvedSurface.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Line3D.h"
#include "AxisSystem.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RevolvedSurface::RevolvedSurface(const Curve* C, const OneAxis& Ax, const double& st, const double& en) : itsAxisOfRevol(Ax), startAngle(st), endAngle(en)
{
	sType = REVOLVED;
	baseCurve = C->Copy();
}

RevolvedSurface::~RevolvedSurface()
{
	if(baseCurve)
		delete baseCurve;
}

Point3D RevolvedSurface::PointAtPara(const double uPar, const double vPar)
{
	Point3D P;
	Point3D CP = baseCurve->PointAtPara(uPar);
	OneAxis ax = itsAxisOfRevol;
	CP.Rotate(ax, vPar);
	P = CP;
	return P;
}

Vector3D RevolvedSurface::NormalAt(const double uPar, const double vPar)
{
	Point3D Po, Pu, Pv;
	Vector3D N;

	if(uPar == LastUParameter() && vPar == LastVParameter())
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar-0.001);
		Vector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vu^Vv;
		return N;
	}
	else if(uPar == LastUParameter() && vPar != LastVParameter())
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar+0.001);
		Vector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vv^Vu;
		return N;
	}
	else if(uPar != LastUParameter() && vPar == LastVParameter())
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar+0.001, vPar);
		Pv = PointAtPara(uPar, vPar-0.001);
		Vector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vv^Vu;
		return N;
	}
	else
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar+0.001, vPar);
		Pv = PointAtPara(uPar, vPar+0.001);
		Vector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vu^Vv;
		return N;
	}
}

double RevolvedSurface::FirstUParameter() const
{
	return baseCurve->FirstParameter();
}

double RevolvedSurface::LastUParameter() const
{
	return baseCurve->LastParameter();
}

double RevolvedSurface::FirstVParameter() const
{
	return startAngle;
}

double RevolvedSurface::LastVParameter() const
{
	return endAngle;
}

bool RevolvedSurface::IsUClosed() const
{
	return false;
}

bool RevolvedSurface::IsVClosed() const
{
	bool b = ((endAngle - startAngle) - (2 * PI) == 0.0);
	return b;
}

Surface* RevolvedSurface::Copy() const
{
	RevolvedSurface* R = new RevolvedSurface(baseCurve, itsAxisOfRevol, startAngle, endAngle);
	return R;
}

void RevolvedSurface::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void RevolvedSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
	itsAxisOfRevol.Translate(dx,dy,dz);
}

void RevolvedSurface::Translate(const Vector3D& V)
{
	baseCurve->Translate(V);
	itsAxisOfRevol.Translate(V);
}

void RevolvedSurface::Translate(const Point3D& P1, const Point3D& P2)
{
	baseCurve->Translate(P1, P2);
	itsAxisOfRevol.Translate(P1, P2);
}

void RevolvedSurface::Rotate(const OneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
	itsAxisOfRevol.Rotate(Ax, ang);
}

void RevolvedSurface::Scale(const Point3D& P, double fact)
{
	baseCurve->Scale(P, fact);
	itsAxisOfRevol.Scale(P, fact);
}

void RevolvedSurface::Mirror(const Point3D& P)
{
	baseCurve->Mirror(P);
	itsAxisOfRevol.Mirror(P);
}

void RevolvedSurface::Mirror(const OneAxis& Ax)
{
	baseCurve->Mirror(Ax);
	itsAxisOfRevol.Mirror(Ax);
}

void RevolvedSurface::Mirror(const Plane& Pln)
{
	baseCurve->Mirror(Pln);
	itsAxisOfRevol.Mirror(Pln);
}
