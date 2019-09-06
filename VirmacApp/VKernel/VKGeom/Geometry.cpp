// Geometry.cpp: implementation of the CGeometry class.
//
//////////////////////////////////////////////////////////////////////


#include "Geometry.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Line3D.h"
#include "Plane.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Geometry::refCount = 0;

Geometry::Geometry()
{
	refCount++;
}

Geometry::~Geometry()
{
	refCount--;
}

void Geometry::Translate(const OneAxis& Ax, const double& amt)
{
	Vector3D D = Ax.GetDirection();
	double dx, dy, dz;
	dx = D.GetX(); dy = D.GetY(); dz = D.GetZ();
	dx *= amt; dy *= amt; dz *= amt;
	Translate(dx,dy,dz);
}
