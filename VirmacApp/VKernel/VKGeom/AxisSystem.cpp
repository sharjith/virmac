// AxisSystem.cpp: implementation of the CAxisSystem class.
//
//////////////////////////////////////////////////////////////////////


#include "Point3D.h"
#include "Vector3D.h"
#include "OneAxis.h"
#include "AxisSystem.h"
#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class CoordSys (Local Coordinate System)
AxisSystem::AxisSystem()
{
	geomType = CAXISSYSTEM;
}

AxisSystem::AxisSystem(const Point3D& Pos, const Vector3D& Dir, const Vector3D& XDir)
{
	Position = Pos;
	Origin.SetParam(Pos.GetX(),Pos.GetY(),Pos.GetZ());
	Direction = Dir;
	Direction.Normalize();
	XDirection = XDir;
	XDirection.Normalize();
	if(!Direction.IsNormal(XDirection))
		throw GeomException(ConstructionFailure);
	else
		YDirection = Direction.Crossed(XDirection);

	geomType = CAXISSYSTEM;
}

AxisSystem::AxisSystem(const Point3D& Pos, const Vector3D& Dir)
{
	Position = Pos;
	Origin.SetParam(Pos.GetX(),Pos.GetY(),Pos.GetZ());
	Direction = Dir;
	Direction.Normalize();

	Vector3D V = Direction;
	double lA = V.GetX();
	double lB = V.GetY();
	double lC = V.GetZ();

	double Aabs = lA;
	if (Aabs < 0)
		Aabs = - Aabs;

	double Babs = lB;
	if (Babs < 0)
		Babs = - Babs;

	double Cabs = lC;
	if (Cabs < 0)
		Cabs = - Cabs;

	Vector3D XAxis;
    
	if      ( Babs <= Aabs && Babs <= Cabs)
	{

		if (Aabs > Cabs)
			XAxis.SetParam(-lC,0., lA);
		else
			XAxis.SetParam( lC,0.,-lA);
	}
	else if( Aabs <= Babs && Aabs <= Cabs)
	{
		if (Babs > Cabs)
			XAxis.SetParam(0.,-lC, lB);
		else
			XAxis.SetParam(0., lC,-lB);
	}
	else
	{
		if (Aabs > Babs)
			XAxis.SetParam(-lB, lA,0.);
		else
			XAxis.SetParam(lB,-lA,0.);
	}
	XDirection = XAxis;
	XDirection.Normalize();
	if(!Direction.IsNormal(XDirection))
		throw GeomException(ConstructionFailure);
	else
		YDirection = Direction.Crossed(XDirection);

	geomType = CAXISSYSTEM;
}

AxisSystem::AxisSystem(const AxisSystem& Ax) : Geometry()
{
	Position = Ax.GetPosition();
	Origin = Ax.GetOrigin();
	Direction = Ax.GetDirection();
	XDirection = Ax.GetXDirection();
	YDirection = Direction.Crossed(XDirection);

	geomType = CAXISSYSTEM;
}

AxisSystem::~AxisSystem()
{
}

void AxisSystem::SetDirection(const Vector3D& D)
{
	Direction = D;
	Direction.Normalize();
	if(!XDirection.IsParallel(Direction))
	{
		Vector3D tempY = D.Crossed(XDirection);
		XDirection = tempY.Crossed(D);
		YDirection = Direction.Crossed(XDirection);
		XDirection.Normalize();
		YDirection.Normalize();
	}
	else
	{
		Vector3D tempX = YDirection.Crossed(D);
		YDirection = D.Crossed(tempX);
		XDirection = Direction.Crossed(YDirection);
		XDirection.Normalize();
		YDirection.Normalize();
	}
}

void AxisSystem::SetDirection(double dx, double dy, double dz)
{
	Vector3D D(dx, dy, dz);
	D.Unit();
	SetDirection(D);
}

void AxisSystem::SetXDirection(const Vector3D& XD)
{
	if(!this->Direction.IsParallel(XD))
	{
		Vector3D XDir = XD;
		XDir.Normalize();
		XDirection = Direction.CrossCrossed(XDir,Direction);
		YDirection = Direction.Crossed(XDirection);
	}
	else
		throw GeomException(ConstructionFailure);
}

void AxisSystem::SetXDirection(double dxx, double dxy, double dxz)
{
	Vector3D XD(dxx, dxy, dxz);
	if(!this->Direction.IsParallel(XD))
	{
		SetXDirection(XD.Unit());
	}
	else
		throw GeomException(ConstructionFailure);
}

void AxisSystem::SetYDirection(const Vector3D& YD)
{
	if(!this->Direction.IsParallel(YD))
	{
		Vector3D YDir = YD;
		YDir.Normalize();
		YDirection = Direction.CrossCrossed(YDir, Direction);
		XDirection = YDirection.Crossed(Direction);
	}
	else
		throw GeomException(ConstructionFailure);
}

void AxisSystem::SetYDirection(double dyx, double dyy, double dyz)
{
	Vector3D YD(dyx, dyy, dyz);
	if(!this->Direction.IsParallel(YD))
	{
		SetYDirection(YD.Unit());
	}
	else
		throw GeomException(ConstructionFailure);
}

void AxisSystem::SetPosition(double x, double y, double z)
{
	Position.SetParam(x,y,z);
	Origin.SetParam(x,y,z);
}

void AxisSystem::SetPosition(const Point3D& P)
{
	SetPosition(P.GetX(), P.GetY(), P.GetZ());
}

bool AxisSystem::operator == (const AxisSystem& C) const
{
	return (Position==C.GetPosition()&&Direction==C.GetDirection()
		&&XDirection==C.GetXDirection()&&YDirection==C.GetYDirection());
}

void AxisSystem::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}


void AxisSystem::Translate(double dx, double dy, double dz)
{
	Position.Translate(dx,dy,dz);
	Origin.Translate(dx,dy,dz);
}

void AxisSystem::Translate(const Vector3D& V)
{
	Position.Translate(V);
	Origin.Translate(V);
}

void AxisSystem::Translate(const Point3D& P1, const Point3D& P2)
{
	Position.Translate(P1, P2);
	Origin.Translate(P1, P2);
}

void AxisSystem::Rotate(const OneAxis& Ax, double ang)
{
	OneAxis tAx = Ax;
	tAx.Translate(tAx.GetPosition(), Point3D(0,0,0));
	Vector3D Dir = GetDirection();
	OneAxis ax(GetPosition(), GetDirection());
	ax.Rotate(tAx, ang);
	Origin.Rotate(Ax, ang);
	Position = Origin.Point();
	SetDirection(ax.GetDirection());
}

void AxisSystem::Scale(const Point3D& P, double fact)
{
	Position.Scale(P, fact);
	Origin.Scale(P, fact);
	if (fact < 0)
	{
		Direction.Reverse();
	    XDirection.Reverse();
		YDirection.Reverse();
	}
}

void AxisSystem::Mirror(const Point3D& P)
{
	Position.Mirror(P);
	Origin.Mirror(P);
	Direction.Reverse();
	XDirection.Reverse();
	YDirection.Reverse();
}

void AxisSystem::Mirror(const OneAxis& Ax)
{
	Position.Mirror(Ax);
	Origin.Mirror(Ax);
	if(Direction.IsParallel(Ax.GetDirection()))
		Direction.Mirror (Ax.GetDirection());
	else
		Direction.Mirror (Ax);
	if(XDirection.IsParallel(Ax.GetDirection()))
		XDirection.Mirror (Ax.GetDirection());
	else
		XDirection.Mirror (Ax);
	if(YDirection.IsParallel(Ax.GetDirection()))
		YDirection.Mirror (Ax.GetDirection());
	else
		YDirection.Mirror (Ax);
	//SetDirection (XDirection.Crossed(YDirection));
}

void AxisSystem::Mirror(const Plane& Pln)
{
	Position.Mirror(Pln);
	Origin.Mirror(Pln);
	Direction.Mirror (Pln);
	XDirection.Mirror (Pln);
	YDirection.Mirror (Pln);
}



