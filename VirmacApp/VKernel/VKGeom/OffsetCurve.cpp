// OffsetCurve.cpp: implementation of the COffsetCurve class.
//
//////////////////////////////////////////////////////////////////////




#include "OffsetCurve.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COffsetCurve::COffsetCurve(const Curve& aCurve, const double& offset, const Plane& refPlane, const bool& sense)
{
	itsCurve = aCurve.Copy();
	itsOffset = offset;
	itsPlane = refPlane;
	itsSense = sense;
}

COffsetCurve::~COffsetCurve()
{
	if(itsCurve)
		delete itsCurve;
}

void COffsetCurve::Reverse()
{
	itsCurve->Reverse();
}

Point3D COffsetCurve::PointAtPara(const double& para)
{
	Vector3D dir = itsPlane.GetDirection();
	Vector3D tangent(itsCurve->PointAtPara(para), itsCurve->PointAtPara(para+0.001));
	Vector3D normal = dir^tangent;
	normal.Normalize();
	if(!itsSense)
		normal = normal * -1.0;
	Point3D P = itsCurve->PointAtPara(para);
	P = P + normal * itsOffset;
	return P;
}

double COffsetCurve::FirstParameter() const
{
	return itsCurve->FirstParameter();
}

double COffsetCurve::LastParameter() const
{
	return itsCurve->LastParameter();
}

bool COffsetCurve::IsClosed() const
{
	return itsCurve->IsClosed();
}

bool COffsetCurve::IsOfType(const CurveType& type) const
{
	bool b = (type == OFFSETCURVE);
	return b;

}

Curve* COffsetCurve::Copy() const
{
	COffsetCurve* myCurve = new COffsetCurve(*itsCurve, itsOffset, itsPlane, itsSense);
	return myCurve;
}

void COffsetCurve::Translate(double dx, double dy, double dz)
{
    itsCurve->Translate(dx, dy, dz);
}

void COffsetCurve::Translate(const Vector3D& V)
{
    itsCurve->Translate(V);
}

void COffsetCurve::Translate(const Point3D& fro, const Point3D& to)
{
    itsCurve->Translate(fro, to);
}

void COffsetCurve::Rotate(const OneAxis& axis, double angle)
{
    itsCurve->Rotate(axis, angle);
}

void COffsetCurve::Scale(const Point3D& point, double fact)
{
    itsCurve->Scale(point, fact);
}

void COffsetCurve::Mirror(const Point3D& point)
{
    itsCurve->Mirror(point );
}

void COffsetCurve::Mirror(const OneAxis& axis)
{
    itsCurve->Mirror(axis);
}

void COffsetCurve::Mirror(const Plane& plane)
{
    itsCurve->Mirror(plane);
}

