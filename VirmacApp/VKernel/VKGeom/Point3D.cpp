// Point3D.cpp: implementation of the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////



#include "Point3D.h"
#include "Vector3D.h"
#include "OneAxis.h"
#include "Line3D.h"
#include "Plane.h"
#include "Matrix33.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Point3D::Point3D()
{
    SetParam(0,0,0);
    geomType = CPOINT;
}

Point3D::Point3D(double x, double y, double z)
{
    SetParam(x, y, z);
    geomType = CPOINT;
}

Point3D::~Point3D()
{

}

void Point3D::SetParam(double x, double y, double z)
{
    itsX=x;
    itsY=y;
    itsZ=z;
}

Point3D Point3D::operator+(const Point3D &newPoint)
{
    return Point3D(itsX+newPoint.GetX(),itsY+newPoint.GetY(),itsZ+newPoint.GetZ());
}

Point3D Point3D::operator+(const double & inc)
{
    return Point3D(itsX+inc,itsY+inc,itsZ+inc);
}

Point3D Point3D::operator-(const Point3D &newPoint)
{
    return Point3D(itsX-newPoint.GetX(),itsY-newPoint.GetY(),itsZ-newPoint.GetZ());
}

Point3D Point3D::operator-(const double & dec)
{
    return Point3D(itsX-dec,itsY-dec,itsZ-dec);
}

Point3D Point3D::operator*(const double scale)
{
    return Point3D(itsX*scale,itsY*scale,itsZ*scale);
}

Point3D Point3D::operator/(const double scale)
{
    return Point3D(itsX/scale,itsY/scale,itsZ/scale);
}

void Point3D::operator+=(const Point3D& P)
{
    (*this) = (*this) + P;
}

void Point3D::operator+=(const double& inc)
{
    (*this) = (*this) + inc;
}

void Point3D::operator-=(const Point3D& P)
{
    (*this) = (*this) - P;
}

void Point3D::operator-=(const double& dec)
{
    (*this) = (*this) - dec;
}

void Point3D::operator*=(const double scale)
{
    (*this) = (*this) * scale;
}

void Point3D::operator/=(const double scale)
{
    (*this) = (*this) / scale;
}

Point3D Point3D::operator = (const Point3D& p)
{
    if(this == &p)
    return *this;
    itsX = p.itsX;
    itsY = p.itsY;
    itsZ = p.itsZ;
    return *this;
}

bool Point3D::operator == (const Point3D& p) const
{
    return (itsX==p.GetX() && itsY==p.GetY() && itsZ==p.GetZ());
}

Point3D::operator Vector3D()
{
    Vector3D V((*this));
    return V;
}

double Point3D::Distance(const Point3D& P) const
{

    double sqad, root;
    double x,y,z,tx,ty,tz;
    x=P.GetX(); y=P.GetY(); z=P.GetZ();
    tx = fabs(this->GetX()-x);
    ty = fabs(this->GetY()-y);
    tz = fabs(this->GetZ()-z);
    sqad=((pow(tx,2))+(pow(ty,2))+(pow(tz,2)));
    root=sqrt(sqad);

    return root;
}

double Point3D::Distance(const Plane& P) const
{

    Point3D p = P.GetPosition();
    Point3D dp = (*this);
    Vector3D V1 = P.GetDirection();
    Vector3D V2(dp);
    double D = V1.Dot(V2) + P.GetConstant();
    return D;
}

double Point3D::PolarAngle(const Point3D& P) const
{
    double x = itsX - P.GetX();
    double y = itsY - P.GetY();
    if((x == 0.0) && (y == 0.0))
	return -1;
    if(x == 0.0)
	return ((y > 0.0) ? 90 : 270);
    double theta = atan(y / x);
    theta *= 360.0 / (2 * PI);
    if(x > 0.0)
	return ((y >= 0.0) ? theta : 360 + theta);
    else
	return (180.0 + theta);
}

void Point3D::Translate(const OneAxis& Ax, const double& amt)
{
    Geometry::Translate(Ax, amt);
}

void Point3D::Translate(double dx, double dy, double dz)
{
    itsX+=dx;
    itsY+=dy;
    itsZ+=dz;
}

void Point3D::Translate(const Vector3D& VDir)
{
    Vector3D V = VDir;
    itsX+=V.GetX();
    itsY+=V.GetY();
    itsZ+=V.GetZ();
}

void Point3D::Translate(const Point3D& P1, const Point3D& P2)
{
    Vector3D V(P1, P2);
    Translate(V);
}

void Point3D::Rotate(const OneAxis& Ax, double ang)
{
    OneAxis ax = Ax;
    Vector3D P1 = ax.GetOrigin();
    Vector3D V = ax.GetDirection();
    V.Normalize();
    CMatrix33 M; Vector3D PV(*this);
    M.SetRotation(V, ang);
    Vector3D RV = M*(PV-P1);
    RV = RV + P1;
    *this = RV.Point();
}

void Point3D::Scale(const Point3D& P, double fact)
{	
    Point3D p = P;
    p = p * (1.0 - fact);
    (*this) = (*this)*(fact);
    (*this) = (*this) + p;
}

void Point3D::Mirror(const Point3D& P)
{
    Point3D p = P;
    (*this) *= -1;
    p *= (2.0);
    (*this) += p;
}

void Point3D::Mirror(const OneAxis& Ax)
{
    Point3D P1 = Ax.GetPosition();
    Point3D P = (*this);
    Vector3D N = Ax.GetDirection();
    CLine3D L(P1, N);
    double D = L.Distance(P);
    Vector3D Q = L.NormalThrough(P) * D * (-2.0);
    Vector3D PV((*this));
    Vector3D R = PV + Q;
    this->SetParam(R.GetX(), R.GetY(), R.GetZ());
}

void Point3D::Mirror(const Plane& Pln)
{
    Plane pln = Pln;
    Point3D P = (*this);
    double D = P.Distance(pln);
    Vector3D N = pln.GetDirection().Unit();
    Vector3D Q = N * D * (-2.0);
    Point3D QP = Q.Point();
    (*this) = P + QP;
}

Point3D Point3D::Origin()
{
    return  Point3D(0,0,0);
}

std::istream &operator>>(std::istream& input, Point3D &p)
{
    input>>p.itsX>>p.itsY>>p.itsZ;
    return input;
}

std::ostream &operator<<(std::ostream& output, Point3D &p)
{
    output<< p.itsX << " " << p.itsY << " " << p.itsZ;
    return output;
}
