// BoundingBox.cpp: implementation of the CBoundingBox class.
//
//////////////////////////////////////////////////////////////////////


#include "BoundingBox.h"
#include "Point3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BoundingBox::BoundingBox(): itsXMax(1.0), itsXMin(-1.0),
    itsYMax(1.0), itsYMin(-1.0),
    itsZMax(1.0), itsZMin(-1.0)
{
    UpdateCorners();
}

BoundingBox::BoundingBox(const double& xMin, const double& xMax, 
						   const double& yMin, const double& yMax, 
						   const double& zMin, const double& zMax) : itsXMax(xMax), itsXMin(xMin),
						   itsYMax(yMax), itsYMin(yMin),
						   itsZMax(zMax), itsZMin(zMin)
{
    UpdateCorners();
}

BoundingBox::~BoundingBox()
{
    if(!corners.empty())
        corners.clear();
}

Point3D BoundingBox::Center() const
{
	Point3D P;
    P.SetX((this->XMax() + this->XMin())/2);
    P.SetY((this->YMax() + this->YMin())/2);
    P.SetZ((this->ZMax() + this->ZMin())/2);
	return P;
}

#include <iostream>
double BoundingBox::BoundingRadius() const
{
    double rad = 0.0;
    Point3D Pmax(this->XMax(), this->YMax(), this->ZMax());
	Point3D Cen = Center();
	rad = Pmax.Distance(Cen);
	return rad;
}

void BoundingBox::SetLimits(const double& xMin, const double& xMax, 
						   const double& yMin, const double& yMax, 
						   const double& zMin, const double& zMax)
{
	itsXMax = xMax;
	itsXMin = xMin;
	itsYMax = yMax;
	itsYMin = yMin;
	itsZMax = zMax;
	itsZMin = zMin;

    UpdateCorners();
}

void BoundingBox::GetLimits(double& xMin, double& xMax,
						   double& yMin, double& yMax,
						   double& zMin, double& zMax)
{
	xMax = itsXMax;
	xMin = itsXMin;
	yMax = itsYMax;
	yMin = itsYMin;
	zMax = itsZMax;
	zMin = itsZMin;
}

const std::vector<Point3D>& BoundingBox::GetCorners() const
{
    return corners;
}

bool BoundingBox::Contains(const Point3D& P) const
{
	bool bx = false, by = false, bz = false;
    bx = (P.GetX() <= this->XMax() && P.GetX() >= this->XMin());
    by = (P.GetY() <= this->YMax() && P.GetY() >= this->YMin());
    bz = (P.GetZ() <= this->ZMax() && P.GetZ() >= this->ZMin());

	return (bx && by &&bz);
}

void BoundingBox::AddBox(const BoundingBox& B)
{
    if(B.XMax() > this->XMax())
		itsXMax = B.XMax();
    if(B.XMin() < this->XMin())
		itsXMin = B.XMin();

    if(B.YMax() > this->YMax())
		itsYMax = B.YMax();
    if(B.YMin() < this->YMin())
		itsYMin = B.YMin();

    if(B.ZMax() > this->ZMax())
		itsZMax = B.ZMax();
    if(B.ZMin() < this->ZMin())
		itsZMin = B.ZMin();


    UpdateCorners();
}

void BoundingBox::UpdateCorners()
{
    if(!corners.empty())
        corners.clear();

    Point3D P1(itsXMin, itsYMin, itsZMin);
    Point3D P2(itsXMax, itsYMin, itsZMin);
    Point3D P3(itsXMax, itsYMax, itsZMin);
    Point3D P4(itsXMin, itsYMax, itsZMin);
    Point3D P5(itsXMin, itsYMin, itsZMax);
    Point3D P6(itsXMax, itsYMin, itsZMax);
    Point3D P7(itsXMax, itsYMax, itsZMax);
    Point3D P8(itsXMin, itsYMax, itsZMax);

    corners.push_back(P1);
    corners.push_back(P2);
    corners.push_back(P3);
    corners.push_back(P4);
    corners.push_back(P5);
    corners.push_back(P6);
    corners.push_back(P7);
    corners.push_back(P8);
}
