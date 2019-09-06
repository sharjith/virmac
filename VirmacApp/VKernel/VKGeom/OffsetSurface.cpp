// OffsetSurface.cpp: implementation of the COffsetSurface class.
//
//////////////////////////////////////////////////////////////////////




#include "OffsetSurface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COffsetSurface::COffsetSurface(const Surface& pSurf, const double& Offset, bool Sense) : itsOffset(Offset), dirSense(Sense)
{
	pSurface = pSurf.Copy();
}

COffsetSurface::~COffsetSurface()
{
	if(pSurface)
		delete pSurface;
}

Point3D COffsetSurface::PointAtPara(const double uPar, const double vPar)
{
	Vector3D V = pSurface->NormalAt(uPar, vPar);
	V.Normalize();
	if(!dirSense)
		V = V * -1.0;
	Point3D P = pSurface->PointAtPara(uPar, vPar);
	P = P+V*itsOffset;
	return P;
}

Vector3D COffsetSurface::NormalAt(const double uPar, const double vPar)
{
	Vector3D V = pSurface->NormalAt(uPar, vPar);
	return V;
}

double COffsetSurface::FirstUParameter() const
{
	return pSurface->FirstUParameter();
}

double COffsetSurface::LastUParameter() const
{
	return pSurface->LastUParameter();
}

double COffsetSurface::FirstVParameter() const
{
	return pSurface->FirstVParameter();
}

double COffsetSurface::LastVParameter() const
{
	return pSurface->LastVParameter();
}

bool COffsetSurface::IsUClosed() const
{
	return pSurface->IsUClosed();
}

bool COffsetSurface::IsVClosed() const
{
	return pSurface->IsVClosed();
}

SurfaceType COffsetSurface::Type() const
{
	return OFFSET;
}

bool COffsetSurface::IsOfType(const SurfaceType& O) const
{
	bool b = (O == OFFSET);
	return b;
}

Surface* COffsetSurface::Copy() const
{
	COffsetSurface* S = new COffsetSurface(*pSurface, itsOffset, dirSense);
	return S;
}

void COffsetSurface::Translate(double dx, double dy, double dz)
{
    pSurface->Translate(dx, dy, dz);
}

void COffsetSurface::Translate(const Vector3D& V)
{
    pSurface->Translate(V);
}

void COffsetSurface::Translate(const Point3D& fro, const Point3D& to)
{
    pSurface->Translate(fro, to);
}

void COffsetSurface::Rotate(const OneAxis& axis, double angle)
{
    pSurface->Rotate(axis, angle);
}

void COffsetSurface::Scale(const Point3D& P, double fact)
{
    pSurface->Scale(P, fact);
}

void COffsetSurface::Mirror(const Point3D& point)
{
    pSurface->Mirror(point);
}

void COffsetSurface::Mirror(const OneAxis& axis)
{
    pSurface->Mirror(axis);
}

void COffsetSurface::Mirror(const Plane& plane)
{
    pSurface->Mirror(plane);
}

