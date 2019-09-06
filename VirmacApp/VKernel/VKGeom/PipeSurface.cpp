// PipeSurface.cpp: implementation of the CPipeSurface class.
//
//////////////////////////////////////////////////////////////////////



#include "PipeSurface.h"
#include "Point3D.h"
#include "Circle3D.h"
#include "Ellipse3D.h"
#include "OneAxis.h"
#include "AxisSystem.h"
#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PipeSurface::PipeSurface()
{
	sType = PIPE;
}

PipeSurface::PipeSurface(const Curve* C, const double& radius) : itsRadius(radius)
{
	sType = PIPE;
	circular = true;
	baseCurve = C->Copy();
}

PipeSurface::PipeSurface(const Curve* C, const double& majrad, const double& minrad) : itsRadius(minrad), 
																						itsMajorRadius(majrad)
{
	sType = PIPE;
	circular = false;
	baseCurve = C->Copy();
}

PipeSurface::~PipeSurface()
{
	if(baseCurve)
		delete baseCurve;
}

Point3D PipeSurface::PointAtPara(const double uPar, const double vPar)
{
	Point3D P;
	Point3D O = baseCurve->PointAtPara(uPar);
	Point3D D;
	Vector3D Dir;
	if(uPar == 1)
	{
		D = baseCurve->PointAtPara(uPar-0.001);
		Dir = Vector3D(O, D);
	}
	else
	{
		D = baseCurve->PointAtPara(uPar+0.001);
		Dir = Vector3D(D, O);
	}
	Point3D fp = baseCurve->PointAtPara(baseCurve->FirstParameter());
	Point3D dfp = baseCurve->PointAtPara(baseCurve->FirstParameter()+0.001);
	Vector3D Z(fp, dfp);
	AxisSystem Ax(O, Z);
		
	if(circular)
	{
		Circle3D C(Ax, itsRadius);
		if(uPar == baseCurve->FirstParameter())
			C.Reverse();
		P = C.PointAtPara(vPar);
	}
	else
	{
		Ellipse3D C(Ax, itsMajorRadius, itsRadius);
		if(uPar == baseCurve->FirstParameter())
			C.Reverse();
		P = C.PointAtPara(vPar);
	}

	Vector3D Ref = Dir^Z;
	double ang = Dir.Angle(Z, Ref);

	P.Translate(Ax.GetPosition(), O);
	P.Rotate(OneAxis(O, Ref), -ang);

	return P;
}

Vector3D PipeSurface::NormalAt(const double uPar, const double vPar)
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
double PipeSurface::FirstUParameter() const
{
	return baseCurve->FirstParameter();
}

double PipeSurface::LastUParameter() const
{
	return baseCurve->LastParameter();
}

double PipeSurface::FirstVParameter() const
{
	return 0;
}

double PipeSurface::LastVParameter() const
{
	return 2*PI;
}

bool PipeSurface::IsUClosed() const
{
	return false;
}

bool PipeSurface::IsVClosed() const
{
	return false;
}

Surface* PipeSurface::Copy() const
{
	PipeSurface* P;
	if(circular)
		P = new PipeSurface(baseCurve, itsRadius);
	else
		P = new PipeSurface(baseCurve, itsMajorRadius, itsRadius);
	return P;
}

void PipeSurface::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void PipeSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
}

void PipeSurface::Translate(const Vector3D& V)
{
	baseCurve->Translate(V);
}

void PipeSurface::Translate(const Point3D& P1, const Point3D& P2)
{
	baseCurve->Translate(P1, P2);
}

void PipeSurface::Rotate(const OneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
}

void PipeSurface::Scale(const Point3D& P, double fact)
{
	baseCurve->Scale(P, fact);
}

void PipeSurface::Mirror(const Point3D& P)
{
	baseCurve->Mirror(P);
}

void PipeSurface::Mirror(const OneAxis& Ax)
{
	baseCurve->Mirror(Ax);
}

void PipeSurface::Mirror(const Plane& Pln)
{
	baseCurve->Mirror(Pln);
}
