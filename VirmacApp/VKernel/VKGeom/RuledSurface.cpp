// RuledSurface.cpp: implementation of the CRuledSurface class.
//
//////////////////////////////////////////////////////////////////////




#include "RuledSurface.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RuledSurface::RuledSurface(const Curve* C1, const Curve* C2)
{
	sType = RULED;
	baseCurve = C1->Copy();
	secondRail = C2->Copy();
}

RuledSurface::~RuledSurface()
{
	if(baseCurve)
		delete baseCurve;
	if(secondRail)
		delete secondRail;
}

Curve* RuledSurface::RailCurve1() const
{
	return baseCurve;
}

Curve* RuledSurface::RailCurve2() const
{
	return secondRail;
}

#include "Line3D.h"
Point3D RuledSurface::PointAtPara(const double uPar, const double vPar)
{
	double uParR1 = baseCurve->FirstParameter() + 
		((baseCurve->LastParameter() - baseCurve->FirstParameter())*uPar);
	double uParR2 = secondRail->FirstParameter() +
		((secondRail->LastParameter() - secondRail->FirstParameter())*uPar);

	Point3D P1 = baseCurve->PointAtPara(uParR1);
	Point3D P2 = secondRail->PointAtPara(uParR2);
	CLine3D L(P1, P2);
	Point3D P = L.PointAtPara(vPar);
	return P;
}

Vector3D RuledSurface::NormalAt(const double uPar, const double vPar)
{
	Point3D Po, Pu, Pv;
	Vector3D N;

	if(uPar == 1 && vPar == 1)
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar-0.001);
		Vector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vu^Vv;
		return N;
	}
	else if(uPar == 1 && vPar != 1)
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar+0.001);
		Vector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vv^Vu;
		return N;
	}
	else if(uPar != 1 && vPar == 1)
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

double RuledSurface::FirstUParameter() const
{
	return 0;
}

double RuledSurface::LastUParameter() const
{
	return 1;
}

double RuledSurface::FirstVParameter() const
{
	return 0;
}

double RuledSurface::LastVParameter() const
{
	return 1;
}

bool RuledSurface::IsUClosed() const
{
	return false;
}

bool RuledSurface::IsVClosed() const
{
	return false;
}

Surface* RuledSurface::Copy() const
{
	RuledSurface* R = new RuledSurface(baseCurve, secondRail);
	return R;
}

void RuledSurface::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void RuledSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
	secondRail->Translate(dx,dy,dz);
}

void RuledSurface::Translate(const Vector3D& V)
{
	baseCurve->Translate(V);
	secondRail->Translate(V);
}

void RuledSurface::Translate(const Point3D& P1, const Point3D& P2)
{
	baseCurve->Translate(P1, P2);
	secondRail->Translate(P1, P2);
}

void RuledSurface::Rotate(const OneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
	secondRail->Rotate(Ax, ang);
}

void RuledSurface::Scale(const Point3D& P, double fact)
{
	baseCurve->Scale(P, fact);
	secondRail->Scale(P, fact);
}

void RuledSurface::Mirror(const Point3D& P)
{
	baseCurve->Mirror(P);
	secondRail->Mirror(P);
}

void RuledSurface::Mirror(const OneAxis& Ax)
{
	baseCurve->Mirror(Ax);
	secondRail->Mirror(Ax);
}

void RuledSurface::Mirror(const Plane& Pln)
{
	baseCurve->Mirror(Pln);
	secondRail->Mirror(Pln);
}

