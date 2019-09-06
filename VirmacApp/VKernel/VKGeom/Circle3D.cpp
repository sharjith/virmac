// Circle3D.cpp: implementation of the CCircle3D class.
//
//////////////////////////////////////////////////////////////////////



#include "Circle3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Circle3D::Circle3D()
{
    cType = CIRCLE;
}

Circle3D::Circle3D(const Point3D& cp, const double rad) : itsRadius(rad)
{
    AxisSystem ax(cp, Vector3D(0,0,1), Vector3D(1,0,0));
    itsLocation = ax;
    cType = CIRCLE;
}

Circle3D::Circle3D(const AxisSystem& ax, const double rad) : itsRadius(rad)
{
    itsLocation = ax;
    cType = CIRCLE;
}

Circle3D::Circle3D(const Point3D& P1, const Point3D& P2, const Point3D& P3)
{
    Point3D p1=P1, p2=P2, p3=P3;
    double x1, x2, x3, y1, y2, y3, z1, z2, z3;
    x1 = p1.GetX(); y1 = p1.GetY(); z1 = p1.GetZ();
    x2 = p2.GetX(); y2 = p2.GetY(); z2 = p2.GetZ();
    x3 = p3.GetX(); y3 = p3.GetY(); z3 = p3.GetZ();

    Vector3D pv1(p1);
    Vector3D pv2(p2);
    Vector3D pv3(p3);

    Vector3D n1(pv1, pv2); 
    Vector3D n2(pv2, pv3);
    Vector3D n3(pv3, pv1);

    double Row1[3]={n1.GetX(), n1.GetY(), n1.GetZ()};
    double Row2[3]={n2.GetX(), n2.GetY(), n2.GetZ()};
    double Row3[3]={n3.GetX(), n3.GetY(), n3.GetZ()};

    double b1, b2, b3;
    b1 = ((p1.Distance(p2))/2) + (x1*n1.GetX() + y1*n1.GetY() + z1*n1.GetZ());
    b2 = ((p2.Distance(p3))/2) + (x2*n2.GetX() + y2*n2.GetY() + z2*n2.GetZ());
    b3 = ((p3.Distance(p1))/2) + (x3*n3.GetX() + y3*n3.GetY() + z3*n3.GetZ());

    Vector3D b(b1, b2, b3);
    CMatrix33 M(Row1, Row2, Row3);

    M.Invert();

    Vector3D cen = M*b;
    Vector3D dir = n1.Crossed(n2);
    Vector3D xdir = dir.Crossed(n1);

    AxisSystem ax(Point3D(cen.GetX(), cen.GetY(), cen.GetZ()), 
	    dir, xdir);
    itsLocation = ax;

    itsRadius = p1.Distance(cen.Point());

    cType = CIRCLE;
}

Circle3D::Circle3D(const Circle3D& C) : Conic()
{
    cType = CIRCLE;
    itsLocation = C.itsLocation;
    itsRadius = C.itsRadius;
}

Circle3D::~Circle3D()
{

}

void Circle3D::Reverse()
{
    cReversed = !cReversed;
}

Circle3D Circle3D::Reversed() const
{
    Circle3D C = (*this);
    C.Reverse();
    return C;
}

Point3D Circle3D::PointAtPara(const double& Par)
{
    Point3D P; Vector3D V;
    double para = Par;

    if(cReversed)
	para = 2*PI - para;

    double c = cos(para);
    double s = sin(para);
    V = itsLocation.GetOrigin()+(itsLocation.GetXDirection()*c+itsLocation.GetYDirection()*s)
	*GetRadius();
    P.SetParam(V.GetX(), V.GetY(), V.GetZ());

    return P;
}

bool Circle3D::IsClosed() const
{
    return true;
}

bool Circle3D::operator == (const Circle3D& C) const
{
    bool eq = (itsLocation == C.GetLocation() && itsRadius == C.GetRadius());
    return eq;
}

Circle3D Circle3D::operator = (const Circle3D& C)
{
    if(this == &C)
	return *this;
    cType = CIRCLE;
    itsLocation = C.GetLocation();
    itsRadius = C.GetRadius();
    return *this;
}

void Circle3D::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

Curve* Circle3D::Copy() const
{
    Circle3D* C = new Circle3D(itsLocation, itsRadius);
    return C;
}

void Circle3D::Translate(const OneAxis& Ax, const double& amt)
{
    Geometry::Translate(Ax, amt);
}

void Circle3D::Translate(const Vector3D& V)
{
    itsLocation.Translate(V);
}

void Circle3D::Translate(const Point3D& P1, const Point3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void Circle3D::Rotate(const OneAxis& Ax, double fact)
{
    itsLocation.Rotate(Ax, fact);
}

void Circle3D::Scale(const Point3D& P, double fact)
{
    itsLocation.Scale(P, fact);
    itsRadius *= fact;
    if(itsRadius < 0)
	itsRadius = -itsRadius;
}

void Circle3D::Mirror(const Point3D& P)
{
    itsLocation.Mirror(P);
}

void Circle3D::Mirror(const OneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void Circle3D::Mirror(const Plane& Pln)
{
    itsLocation.Mirror(Pln);
}
