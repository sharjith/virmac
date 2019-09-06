// OneAxis.cpp: implementation of the COneAxis class.
//
//////////////////////////////////////////////////////////////////////




#include "OneAxis.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class OneAxis 
//(Used for construction of revolutions and as axis of symmetries)
OneAxis::OneAxis()
{
	Position = Point3D(0,0,0);
	Direction = Vector3D(0,0,1);
	Direction.Normalize();
	Origin.SetParam(0,0,0);
	geomType = CONEAXIS;
}

OneAxis::OneAxis(const Point3D& Pos, const Vector3D& Dir) : Position(Pos), Direction(Dir)
{
	Direction.Normalize();
	Origin.SetParam(Pos.GetX(),Pos.GetY(),Pos.GetZ());
	geomType = CONEAXIS;
}

OneAxis::~OneAxis()
{
}

void OneAxis::SetPosition(const Point3D& P)
{
	Position = P;
	Origin = P;
}

void OneAxis::SetPosition(double x, double y, double z)

{
	Position.SetParam(x,y,z);
	Origin.SetParam(x,y,z);
}

void OneAxis::SetDirection(const Vector3D& D)
{
	Direction = D;
	Direction.Normalize();
}

void OneAxis::SetDirection(double dx, double dy, double dz)
{
	Direction.SetParam(dx,dy,dz);
	Direction.Normalize();
}

Point3D OneAxis::GetPosition() const
{
	return Position;
}

Vector3D OneAxis::GetOrigin() const
{
	return Origin;
}

Vector3D OneAxis::GetDirection() const
{
	return Direction;
}

bool OneAxis::operator == (const OneAxis& rhAx) const
{
	bool eq = (Position == rhAx.GetPosition() && Direction == rhAx.GetDirection()
				&& Origin == rhAx.GetOrigin());
	return eq;
}

void OneAxis::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void OneAxis::Translate(double dx, double dy, double dz)
{
	Point3D P = Position;
	P.Translate(dx, dy, dz);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Translate(const Vector3D& V)
{
	Point3D P = Position;
	P.Translate(V);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Translate(const Point3D& P1, const Point3D& P2)
{
	Point3D P = Position;
	P.Translate(P1, P2);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Rotate(const OneAxis& Ax, double ang)
{
	Point3D P = Position;
	Vector3D D = Direction;
	P.Rotate(Ax, ang);
	D.Rotate(Ax, ang);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Scale(const Point3D& Pnt, double fact)
{
	Point3D P = Position;
	Vector3D D = Direction;
	P.Scale(Pnt, fact);
	D.Scale(Pnt, fact);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Mirror(const Point3D& Pnt)
{
	Point3D P = Position;
	Vector3D D = Direction;
	P.Mirror(Pnt);
	D.Mirror(Pnt);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Mirror(const OneAxis& Ax)
{
	Point3D P = Position;
	Vector3D D = Direction;
	/*CString str;
	str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	P.Mirror(Ax);
	Vector3D dir = Ax.GetDirection();
	if(dir.IsParallel(D))
		D.Mirror(Ax.GetDirection());
	else
		D.Mirror(Ax);
	/*str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void OneAxis::Mirror(const Plane& Pln)
{
	Point3D P = Position;
	Vector3D D = Direction;
	P.Mirror(Pln);
	D.Mirror(Pln);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

OneAxis OneAxis::OX()
{
	OneAxis Ax(Point3D(0,0,0), Vector3D(1,0,0));
	return Ax;
}

OneAxis OneAxis::OY()
{
	OneAxis Ax(Point3D(0,0,0), Vector3D(0,1,0));
	return Ax;
}

OneAxis OneAxis::OZ()
{
	OneAxis Ax(Point3D(0,0,0), Vector3D(0,0,1));
	return Ax;
}

