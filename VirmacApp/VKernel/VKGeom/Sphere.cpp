// Sphere.cpp: implementation of the CSphere class.
//
//////////////////////////////////////////////////////////////////////



#include "Sphere.h"
#include "GeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//
Sphere::Sphere()
{
    sType = SPHERE;
    itsLocation = AxisSystem(Point3D(0,0,0), Vector3D(0,0,1));
    itsRadius = 10.0;
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = -PI/2;
    itsLastVParameter = PI/2;
}

Sphere::Sphere(const AxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd) : itsRadius(rad)
{
    sType = SPHERE;
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = vStart;
    itsLastVParameter = vEnd;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
        cout << "Invalid U Range .... CSphere::CSphere(const CAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
        throw GeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
        cout << "Invalid U Range .... CSphere::CSphere(const CAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
        throw GeomException(InvalidRange);
    }
    if(itsFirstVParameter < -PI/2 || itsFirstVParameter > PI/2)
    {
        cout << "Invalid V Range .... CSphere::CSphere(const CAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
        throw GeomException(InvalidRange);
    }
    if(itsLastVParameter < -PI/2 || itsLastVParameter > PI/2)
    {
        cout << "Invalid V Range .... CSphere::CSphere(const CAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
        throw GeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
        cout << "Invalid Range .... CSphere::CSphere(const CAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
        throw GeomException(InvalidRange);
    }
    if(itsLastVParameter <  itsFirstVParameter)
    {
        cout << "Invalid Range .... CSphere::CSphere(const CAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
        throw GeomException(InvalidRange);
    }
}

Sphere::~Sphere()
{

}

Point3D Sphere::PointAtPara(const double uPar, const double vPar)
{
    Vector3D P, O, XDir, YDir, ZDir;
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    double cv = cos(vPar);
    double sv = sin(vPar);
    P = O + (XDir*cu + YDir*su)*itsRadius*cv + ZDir*itsRadius*sv;
    return P.Point();
}

Vector3D Sphere::NormalAt(const double uPar, const double vPar)
{
    Point3D O = itsLocation.GetPosition();
    Point3D P = PointAtPara(uPar, vPar);
    Vector3D N(O, P);
    N.Normalize();
    return N;
}

bool Sphere::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
        return true;
    return false;
}

bool Sphere::IsVClosed() const
{
    if(itsFirstVParameter == -PI/2 && itsLastVParameter == PI/2)
        return true;
    return false;
}

Surface* Sphere::Copy() const
{
    Sphere* S = new Sphere(itsLocation, itsRadius, itsFirstUParameter, itsLastUParameter, itsFirstVParameter, itsLastVParameter);
    return S;
}

void Sphere::Translate(const OneAxis& Ax, const double& amt)
{
    Geometry::Translate(Ax, amt);
}

void Sphere::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void Sphere::Translate(const Vector3D& V)
{
    itsLocation.Translate(V);
}

void Sphere::Translate(const Point3D& P1, const Point3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void Sphere::Rotate(const OneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void Sphere::Scale(const Point3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void Sphere::Mirror(const Point3D& P)
{
    itsLocation.Mirror(P);
}

void Sphere::Mirror(const OneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void Sphere::Mirror(const Plane& Pln)
{
    itsLocation.Mirror(Pln);
}

