// Geometry.cpp: implementation of the CGeometry class.
//
//////////////////////////////////////////////////////////////////////



#include "Geometry2D.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "OneAxis2D.h"
//#include "Line2D.h"
//#include "Plane.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Geometry2D::refCount = 0;

Geometry2D::Geometry2D()
{
	refCount++;
}

Geometry2D::~Geometry2D()
{
	refCount--;
}

void Geometry2D::Translate(const COneAxis2D& Ax, const double& amt)
{
	Vector2D D = Ax.GetDirection();
	double dx, dy;
	dx = D.GetX(); dy = D.GetY();
	dx *= amt; dy *= amt;
	Translate(dx,dy);
}

