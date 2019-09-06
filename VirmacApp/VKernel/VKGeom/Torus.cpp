// Torus.cpp: implementation of the CTorus class.
//
//////////////////////////////////////////////////////////////////////



#include "Torus.h"
#include "Circle3D.h"
#include "GeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Torus::Torus()
{
    sType = TORUS;
    itsLocation = AxisSystem(Point3D(0,0,0), Vector3D(0,0,1));
    majorRadius = 10.0;
    minorRadius = 5.0;
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = 0;
    itsLastVParameter = 2*PI;
}

Torus::Torus(const AxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd) : majorRadius(maj), minorRadius(min)
{

    sType = TORUS;
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = vStart;
    itsLastVParameter = vEnd;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid U Range .... CTorus::CTorus(const CAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid U Range .... CTorus::CTorus(const CAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsFirstVParameter < 0 || itsFirstVParameter > 2*PI)
    {
	cout << "Invalid V Range .... CTorus::CTorus(const CAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastVParameter < 0 || itsLastVParameter > 2*PI)
    {
	cout << "Invalid V Range .... CTorus::CTorus(const CAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... CTorus::CTorus(const CAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw GeomException(InvalidRange);
    }
    if(itsLastVParameter <  itsFirstVParameter)
    {
	cout << "Invalid Range .... CTorus::CTorus(const CAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw GeomException(InvalidRange);
    }
}

Torus::~Torus()
{

}

Point3D Torus::PointAtPara(const double uPar, const double vPar)
{
    Vector3D P, O, XDir, YDir, ZDir;
    double r = minorRadius, R = majorRadius;
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    double cv = cos(vPar);
    double sv = sin(vPar);
    P = O + (((XDir*cu + YDir*su) * (R + r*cv)) ) + ZDir*r*sv;
    return P.Point();
}

Vector3D Torus::NormalAt(const double uPar, const double vPar)
{
    Circle3D C(itsLocation, majorRadius);
    Point3D O = C.PointAtPara(uPar);
    Point3D P = PointAtPara(uPar, vPar);
    Vector3D N(O, P);
    return N;
}

bool Torus::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
	return true;
    return false;
}

bool Torus::IsVClosed() const
{
    if(itsFirstVParameter == 0 && itsLastVParameter == 2*PI)
	return true;
    return false;
}

Surface* Torus::Copy() const
{
    Torus* T = new Torus(itsLocation, majorRadius, minorRadius, itsFirstUParameter, itsLastUParameter, itsFirstVParameter, itsLastVParameter);
    return T;
}

void Torus::Translate(const OneAxis& Ax, const double& amt)
{
    Geometry::Translate(Ax, amt);
}

void Torus::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void Torus::Translate(const Vector3D& V)
{
    itsLocation.Translate(V);
}

void Torus::Translate(const Point3D& P1, const Point3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void Torus::Rotate(const OneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void Torus::Scale(const Point3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void Torus::Mirror(const Point3D& P)
{
    itsLocation.Mirror(P);
}

void Torus::Mirror(const OneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void Torus::Mirror(const Plane& Pln)
{
    itsLocation.Mirror(Pln);
}
