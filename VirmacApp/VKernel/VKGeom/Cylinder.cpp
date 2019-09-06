// Cylinder.cpp: implementation of the CCylinder class.
//
//////////////////////////////////////////////////////////////////////

#include "Cylinder.h"
#include "Circle3D.h"
#include "AxisSystem.h"
#include "MMath.h"
#include "GeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cylinder::Cylinder(const Circle3D& C, const double& ht) : itsHeight(ht)
{
    sType = CYLINDER;
    itsLocation = C.GetLocation();
    itsRadius = C.GetRadius();
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
}

Cylinder::Cylinder(const AxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd) : itsHeight(ht), itsRadius(rad)
{
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid Range .... CCylinder::CCylinder(const CAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid Range .... CCylinder::CCylinder(const CAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... CCylinder::CCylinder(const CAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd)\n";
	throw GeomException(InvalidRange);
    }
}

Cylinder::~Cylinder()
{

}

Point3D Cylinder::PointAtPara(const double uPar, const double vPar)
{
    Vector3D P, O, XDir, YDir, ZDir;
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    P = O + (XDir*cu + YDir*su)*itsRadius + ZDir*vPar;
    return P.Point();
}

bool Cylinder::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
		return true;
    return false;
}

bool Cylinder::IsVClosed() const
{
    return false;
}

Surface* Cylinder::Copy() const
{
    Cylinder* R = new Cylinder(itsLocation, itsHeight, itsRadius, itsFirstUParameter, itsLastUParameter);
    return R;
}

void Cylinder::Translate(const OneAxis& Ax, const double& amt)
{
    Geometry::Translate(Ax, amt);
}

void Cylinder::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void Cylinder::Translate(const Vector3D& V)
{
    itsLocation.Translate(V);
}

void Cylinder::Translate(const Point3D& P1, const Point3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void Cylinder::Rotate(const OneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void Cylinder::Scale(const Point3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void Cylinder::Mirror(const Point3D& P)
{
    itsLocation.Mirror(P);
}

void Cylinder::Mirror(const OneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void Cylinder::Mirror(const Plane& Pln)
{
    itsLocation.Mirror(Pln);
}
