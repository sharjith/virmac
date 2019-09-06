// Cone.cpp: implementation of the CCone class.
//
//////////////////////////////////////////////////////////////////////


#include "Cone.h"
#include "Circle3D.h"
#include "MMath.h"
#include "GeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cone::Cone(const Circle3D& C, const double& ht) : itsHeight(ht)
{
    sType = CONE;
    itsLocation = C.GetLocation();
    baseRadius = C.GetRadius();
    topRadius = 0;
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
}

Cone::Cone(const AxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd) : itsHeight(ht), baseRadius(rad1), topRadius(rad2)
{
    sType = CONE;
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid Range .... CCone::CCone(const CAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid Range .... CCone::CCone(const CAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... CCone::CCone(const CAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd)\n";
	throw GeomException(InvalidRange);
    }
}

Cone::~Cone()
{

}

Point3D Cone::PointAtPara(const double uPar, const double vPar)
{
    Vector3D P, O, XDir, YDir, ZDir;
    double Ang = atan((baseRadius-topRadius)/itsHeight);
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    P = O + (((XDir*cu + YDir*su) * (baseRadius - vPar*tan(Ang))) ) + ZDir*vPar;
    return P.Point();
}

bool Cone::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
	return true;
    return false;
}

bool Cone::IsVClosed() const
{
    return false;
}

Surface* Cone::Copy() const
{
    Cone* R = new Cone(itsLocation, itsHeight, baseRadius, topRadius, itsFirstUParameter, itsLastUParameter);;
    return R;
}

void Cone::Translate(const OneAxis& Ax, const double& amt)
{
    Geometry::Translate(Ax, amt);
}

void Cone::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void Cone::Translate(const Vector3D& V)
{
    itsLocation.Translate(V);
}

void Cone::Translate(const Point3D& P1, const Point3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void Cone::Rotate(const OneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void Cone::Scale(const Point3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void Cone::Mirror(const Point3D& P)
{
    itsLocation.Mirror(P);
}

void Cone::Mirror(const OneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void Cone::Mirror(const Plane& Pln)
{
    itsLocation.Mirror(Pln);
}
