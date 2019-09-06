// Point2D.cpp: implementation of the CPoint2D class.
//
//////////////////////////////////////////////////////////////////////





#include "Point2D.h"
#include "Vector2D.h"
#include "OneAxis2D.h"
#include "Line2D.h"
#include "Matrix22.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Point2D::Point2D()
{
    SetParam(0,0);
    geomType = CPOINT2D;
}

Point2D::Point2D(double x, double y)
{
    SetParam(x, y);
    geomType = CPOINT2D;
}

Point2D::~Point2D()
{

}

void Point2D::SetParam(double x, double y)
{
    itsX=x;
    itsY=y;
}

Point2D Point2D::operator+(const Point2D &newPoint)
{
    return Point2D(itsX+newPoint.GetX(),itsY+newPoint.GetY());
}

Point2D Point2D::operator+(const double & inc)
{
    return Point2D(itsX+inc,itsY+inc);
}

Point2D Point2D::operator-(const Point2D &newPoint)
{
    return Point2D(itsX-newPoint.GetX(),itsY-newPoint.GetY());
}

Point2D Point2D::operator-(const double & dec)
{
    return Point2D(itsX-dec,itsY-dec);
}

Point2D Point2D::operator*(const double scale)
{
    return Point2D(itsX*scale,itsY*scale);
}

Point2D Point2D::operator/(const double scale)
{
    return Point2D(itsX/scale,itsY/scale);
}

void Point2D::operator+=(const Point2D& P)
{
    (*this) = (*this) + P;
}

void Point2D::operator+=(const double& inc)
{
    (*this) = (*this) + inc;
}

void Point2D::operator-=(const Point2D& P)
{
    (*this) = (*this) - P;
}

void Point2D::operator-=(const double& dec)
{
    (*this) = (*this) - dec;
}

void Point2D::operator*=(const double scale)
{
    (*this) = (*this) * scale;
}

void Point2D::operator/=(const double scale)
{
    (*this) = (*this) / scale;
}

Point2D Point2D::operator = (const Point2D& p)
{
    if(this == &p)
	return *this;
    itsX = p.itsX;
    itsY = p.itsY;
    return *this;
}

bool Point2D::operator == (const Point2D& p) const
{
    return (itsX==p.GetX() && itsY==p.GetY());
}

ORIENTATION Point2D::Orientation(const Point2D& P1, const Point2D& P2)
{
    Point2D tmp1 = P1, tmp2 = P2;
    Point2D a = tmp2 - *this;
    Point2D b = tmp1 - *this;
    double sa = a.GetX() * b.GetY() - b.GetX() * a.GetY();
    if(sa > 0.0)
	return ORIENTED_CCW;
    if(sa < 0.0)
	return ORIENTED_CW;
    
    return ORIENTED_COLLINEAR;
}

CLASSIFICATION Point2D::Classification(const Point2D& P1, const Point2D& P2)
{
    Point2D p0 = P1, p1 = P2;
    Point2D p2 = *this;
    Point2D a = p1 - p0;
    Point2D b = p2 - p0;
    double sa = a.GetX() * b.GetY() - b.GetX() * a.GetY();
    if(sa > 0.0)
	return CLASSIFIED_LEFT;
    if(sa < 0.0)
	return CLASSIFIED_RIGHT;
    if((a.GetX() * b.GetX() < 0.0) || (a.GetY() * b.GetY() < 0.0))
	return CLASSIFIED_BEHIND;
    if(a.Distance(Point2D(0,0)) < b.Distance(Point2D(0,0)))
	return CLASSIFIED_BEYOND;
    if(p0 == p2)
	return CLASSIFIED_ORIGIN;
    if(p1 == p2)
	return CLASSIFIED_DESTINATION;
    return CLASSIFIED_BETWEEN;
}

Point2D::operator Vector2D()
{
    Vector2D V((*this));
    return V;
}


double Point2D::Distance(const Point2D& P)
{

    double sqad, root;
    double x,y,tx,ty;
    x=P.GetX(); y=P.GetY();
    tx = fabs(this->GetX()-x);
    ty = fabs(this->GetY()-y);
    sqad=((pow(tx,2))+(pow(ty,2)));
    root=sqrt(sqad);

    return root;
}

double Point2D::PolarAngle(const Point2D& P) const
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

void Point2D::Translate(const COneAxis2D& Ax, const double& amt)
{
    Geometry2D::Translate(Ax, amt);
}

void Point2D::Translate(double dx, double dy)
{
    itsX+=dx;
    itsY+=dy;
}

void Point2D::Translate(const Vector2D& VDir)
{
    Vector2D V = VDir;
    itsX+=V.GetX();
    itsY+=V.GetY();
}

void Point2D::Translate(const Point2D& P1, const Point2D& P2)
{
    Vector2D V(P1, P2);
    Translate(V);
}

void Point2D::Rotate(const Point2D& Pt, double ang)
{
    Point2D P1 = Pt;
    CMatrix22 M;
    M.SetRotation(ang);
    Point2D tp = *this - P1;
    Vector2D V = M * Vector2D(tp);
    V += Vector2D(P1);
    *this = V.Point();
}

void Point2D::Scale(const Point2D& P, double fact)
{	
    Point2D p = P;
    p = p * (1.0 - fact);
    (*this) = (*this)*(fact);
    (*this) = (*this) + p;
}

void Point2D::Mirror(const Point2D& P)
{
    Point2D p = P;
    (*this) *= -1;
    p *= (2.0);
    (*this) += p;
}

void Point2D::Mirror(const COneAxis2D& Ax)
{
    Point2D P1 = Ax.GetPosition();
    Point2D P = (*this);
    Vector2D N = Ax.GetDirection();
    Line2D L(P1, N);
    double D = L.Distance(P);
    Vector2D Q = L.NormalThrough(P) * D * (-2.0);
    Vector2D PV((*this));
    Vector2D R = PV + Q;
    this->SetParam(R.GetX(), R.GetY());
}

Point2D Point2D::Origin()
{
    return  Point2D(0,0);
}

std::istream &operator>>(std::istream& input, Point2D &p)
{
    input>>p.itsX>>p.itsY;
    return input;
}

std::ostream &operator<<(std::ostream& output, Point2D &p)
{
    output<<p.itsX<<p.itsY;
    return output;
}
