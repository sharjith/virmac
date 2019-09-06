// Plane.cpp: implementation of the CPlane class.
//
//////////////////////////////////////////////////////////////////////



#include "Plane.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "OneAxis.h"
#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Plane::Plane(const Point3D& P1, const Point3D& P2, const Point3D& P3)
{
	Vector3D V1(P1, P2);
	Vector3D V2(P1, P3);
	Vector3D Dir = V1^V2;

	AxisSystem ax(P1, Dir, V1);
	itsLocation = ax;

	UpdateEquation();
	
	geomType = CPLANE;
}


Plane::Plane(const Point3D& P1, const Vector3D& V1, const Vector3D& V2)
{
	Vector3D v1 = V1, v2 = V2;
	Vector3D Dir = v1^v2;

	AxisSystem ax(P1, Dir, v1);
	itsLocation = ax;

	UpdateEquation();
	
	geomType = CPLANE;
}

Plane::Plane(const double& A, const double& B, const double& C, const double& D)
{
	Equation[0] = A;
	Equation[1] = B;
	Equation[2] = C;
	Equation[3] = D;

	Point3D Pos(A, B, D);
	Vector3D Dir(A, B, C);

	
	AxisSystem location(Pos, Dir);

	double d = location.GetDirection().Magnitude();
	if ( d > 0.0 )
	{
		d = 1.0/d;
		Vector3D O = location.GetDirection()*(-d)*Equation[3];
		location.SetPosition(O.Point());
	}

	itsLocation = location;
	
	geomType = CPLANE;
}

Plane::Plane(const OneAxis& Ax)
{
	OneAxis ax = Ax;

	Point3D P = Ax.GetPosition();
	Vector3D V = Ax.GetDirection();

	AxisSystem location(P, V);

	itsLocation = location;

	UpdateEquation();
	geomType = CPLANE;
}

Plane::~Plane()
{
}

Point3D Plane::PointAtPara(const double uPar, const double vPar)
{
	Vector3D V;
	V = itsLocation.GetOrigin() + itsLocation.GetXDirection() * uPar + itsLocation.GetYDirection() * vPar;
	/*CString str;
	str.Format("YDirection %0.3lf, %0.3lf, %0.3lf",itsLocation.GetYDirection().GetX(),itsLocation.GetYDirection().GetY(),itsLocation.GetYDirection().GetZ());
	MessageBox(0, str, "From Plane", MB_OK);*/
	return V.Point();
}

Point3D Plane::GetPosition() const
{
	return itsLocation.GetPosition();
}

Vector3D Plane::GetDirection() const
{
	return itsLocation.GetDirection();
}

void Plane::EquationAt(const Point3D& P, double* e)
{
	double x = P.GetX();
	double y = P.GetY();
	double z = P.GetZ();
	e[0] = Equation[0]*x;
	e[1] = Equation[1]*y;
	e[2] = Equation[2]*z;
	e[3] = Equation[3];
}

double Plane::GetConstant() const
{
	return Equation[3];
}

void Plane::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void Plane::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx, dy, dz);
}

void Plane::Translate(const Vector3D& V)
{
	itsLocation.Translate(V);
}

void Plane::Translate(const Point3D& P1, const Point3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void Plane::Rotate(const OneAxis& Ax, double ang)
{
	itsLocation.Rotate(Ax, ang);
}

void Plane::Scale(const Point3D& P, double fact)
{
	itsLocation.Scale(P, fact);
}

void Plane::Mirror(const Point3D& P)
{
	itsLocation.Mirror(P);
}

void Plane::Mirror(const OneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void Plane::Mirror(const Plane& Pln)
{
	itsLocation.Mirror(Pln);
}

void Plane::UpdateEquation()
{
	Vector3D Z = itsLocation.GetDirection();
	Equation[0] = Z.GetX();
	Equation[1] = Z.GetY();
	Equation[2] = Z.GetZ();
	Equation[3] = -(itsLocation.GetOrigin().Dot(Z));
}

Plane Plane::XOY()
{
	Plane P = Plane(OneAxis(Point3D(0,0,0), Vector3D(0,0,1)));
	return P;
}

Plane Plane::YOZ()
{
	Plane P = Plane(OneAxis(Point3D(0,0,0), Vector3D(1,0,0)));
	return P;
}

Plane Plane::ZOX()
{
	Plane P = Plane(OneAxis(Point3D(0,0,0), Vector3D(0,1,0)));
	return P;
}
