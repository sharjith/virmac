// Line2D.cpp: implementation of the CLine2D class.
//
//////////////////////////////////////////////////////////////////////


#include "Line2D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Line2D::Line2D()
{
	cType = LINE2D;
}

Line2D::Line2D(const Point2D& sP, const Point2D& eP) : startPoint(sP), endPoint(eP)
{
	COneAxis2D Ax(sP, Vector2D(sP, eP));
	itsLocation = Ax;
	cType = LINE2D;
}

Line2D::Line2D(const Point2D& P, const Vector2D& V)
{
	Vector2D dir = V;
	Vector2D sv = dir.Unit() * -INFINITY;
	Vector2D ev = dir.Unit() * INFINITY;
	sv.SetParam(sv.GetX()+P.GetX(), sv.GetY()+P.GetY());
	ev.SetParam(ev.GetX()+P.GetX(), ev.GetY()+P.GetY());

	startPoint.SetParam(sv.GetX(), sv.GetY());
	endPoint.SetParam(ev.GetX(), ev.GetY());

	COneAxis2D Ax(startPoint, Vector2D(sv, ev));
	itsLocation = Ax;

	cType = LINE2D;
}

Line2D::~Line2D()
{
}

void Line2D::Reverse()
{
	Point2D tPnt = startPoint;
	startPoint = endPoint;
	endPoint = tPnt;
}

Point2D Line2D::PointAtPara(const double& par)
{
	double u;
	if (par < 0)
		u = 0;
	else if(par > 1)
		u = 1;
	else
		u = par;

	Point2D aPnt;
	aPnt = startPoint + (endPoint - startPoint) * u;
	return aPnt;
}

bool Line2D::IsClosed() const
{
	return false;
}

bool Line2D::operator == (const Line2D& L) const
{
	bool eq = (startPoint == L.StartPoint() && endPoint == L.EndPoint());
	return eq;
}

void Line2D::operator = (const Line2D& L)
{
	itsLocation = L.GetLocation();
	startPoint = L.StartPoint();
	endPoint = L.EndPoint();
}

Vector2D Line2D::Direction() const
{
	Vector2D sv(startPoint);
	Vector2D ev(endPoint);
	Vector2D dir(sv, ev);
	return dir.Unit();
}

Vector2D Line2D::NormalThrough(const Point2D& P)
{
	Point2D P3 = P;
	Point2D P1 = startPoint;
	double D = Distance(P3);
	D = 1/D;
	Vector2D N1 = Direction();
	Vector2D PV = Vector2D(P3 - P1);
	double dt = PV.Dot(N1);
	Vector2D N = (Vector2D(P3 - P1) - N1*(dt)) * D;
	return N;
}

double Line2D::Distance(const Point2D& P)
{
	Point2D P3 = P;
	Point2D P1 = startPoint;
	Point2D P2 = endPoint;
	double x1, y1, x2, y2, x3, y3;
	x1 = P1.GetX(); y1 = P1.GetY();
	x2 = P2.GetX(); y2 = P2.GetY();
	x3 = P3.GetX(); y3 = P3.GetY();
	double L = P1.Distance(P2);
	L = 1/L;
	double D = L * (sqrt(pow((x3-x1)*(y2-y1)-(y3-y1)*(x2-x1),2)));
	return D;
}

void Line2D::Translate(const COneAxis2D& Ax, const double& amt)
{
	Geometry2D::Translate(Ax, amt);
}

void Line2D::Translate(double dx, double dy)
{
	startPoint.Translate(dx,dy);
	endPoint.Translate(dx,dy);
}

void Line2D::Translate(const Vector2D& V)
{
	startPoint.Translate(V);
	endPoint.Translate(V);
}

Curve2D* Line2D::Copy() const
{
	Line2D* L = new Line2D(startPoint, endPoint);
	return L;
}

void Line2D::Translate(const Point2D& P1, const Point2D& P2)
{
	startPoint.Translate(P1, P2);
	endPoint.Translate(P1, P2);
}

void Line2D::Rotate(const Point2D& Ax, double ang)
{
	startPoint.Rotate(Ax, ang);
	endPoint.Rotate(Ax, ang);
}

void Line2D::Scale(const Point2D& P, double fact)
{
	startPoint.Scale(P, fact);
	endPoint.Scale(P, fact);
}

void Line2D::Mirror(const Point2D& P)
{
	startPoint.Mirror(P);
	endPoint.Mirror(P);
}

void Line2D::Mirror(const COneAxis2D& Ax)
{
	startPoint.Mirror(Ax);
	endPoint.Mirror(Ax);
}

