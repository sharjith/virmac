#ifndef __TRIFACET_H__
#define __TRIFACET_H__

#include "Point3D.h"
#include "Vector3D.h"

class TriFacet
{
    public:
    TriFacet(){}
    TriFacet(Point3D p1, Point3D p2,	Point3D p3, Vector3D n)
	{
	    P1 = p1;
	    P2 = p2;
	    P3 = p3;
	    N = n;
	}

	Point3D P1;
	Point3D P2;
	Point3D P3;
	Vector3D N;
};

#endif
