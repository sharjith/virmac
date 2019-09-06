// BSplineCurve.cpp: implementation of the CBSplineCurve class.
//
//////////////////////////////////////////////////////////////////////



#include "BSplineCurve.h"
#include "Point3D.h"
#include "GeomException.h"

#include "Bsp.h" //For The Actual BSpline Algorithm 
				 //Copyright 1994 by Keith Vertanen (vertankd@cda.mrs.umn.edu)
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BSplineCurve::BSplineCurve()
{
	cType = BSPLINE;
}

BSplineCurve::BSplineCurve(ListOfPoint3D *aList, const int& degree) : itsDegree(degree)
{
	cType = BSPLINE;
	Point3D curP;
	cpList = new ListOfPoint3D;
	cpCount = 0;
	ListIteratorOfListOfPoint3D myListIter(aList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		cpList->Append(curP);
		cpCount++;
	}
	if(itsDegree >= cpCount)
		itsDegree = cpCount-1;


	if(itsDegree > GetMaxDegree())
		throw GeomException(MaxDegree);
}

BSplineCurve::~BSplineCurve()
{
	cpList->Clear();
	if(cpList)
		delete cpList;
}

void BSplineCurve::Reverse()
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	ListIteratorOfListOfPoint3D myListIter(cpList);

	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		temp->Append(myListIter.Current());

	cpList->Clear();

	myListIter.SetList(temp);

	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Prepend(myListIter.Current());

	delete temp;
}

Point3D BSplineCurve::PointAtPara(const double& para)
{
	Point3D curP;
	Point3D P;
	point p;
	int cnt = 0;
	int* u;
	int n = cpCount-1;
	int t = itsDegree+1;
	point calcxyz;
	ListIteratorOfListOfPoint3D myListIter(cpList);

	if(para == FirstParameter())
	{
		P = cpList->First();
		return P;
	}


	if(para == LastParameter())
	{
		P = cpList->Last();
		return P;
	}

	u=new int[n+t+1];
	point *control = new point[n+1];

	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		p.x = curP.GetX();
		p.y = curP.GetY();
		p.z = curP.GetZ();
		control[cnt] = p;
		cnt++;
	}

	compute_intervals(u, n, t);//Copyright 1994 by Keith Vertanen (vertankd@cda.mrs.umn.edu)
	compute_point(u, n, t, para, control, &calcxyz);//Copyright 1994 by Keith Vertanen (vertankd@cda.mrs.umn.edu)

    P.SetParam(calcxyz.x, calcxyz.y, calcxyz.z);
	delete u;
	delete [] control;
	return P;
}

double BSplineCurve::FirstParameter() const
{
	return 0.0;
}

double BSplineCurve::LastParameter() const
{
	int n = cpCount-1 ;
	int k = itsDegree+1;
	return (n-k+2);
}

bool BSplineCurve::IsClosed() const
{
	return false;
}

Curve* BSplineCurve::Copy() const
{
	BSplineCurve* C = new BSplineCurve(cpList, itsDegree);
	return C;
}

void BSplineCurve::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void BSplineCurve::Translate(double dx, double dy, double dz)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Translate(dx,dy,dz);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Translate(const Vector3D& V)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Translate(V);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Translate(const Point3D& P1, const Point3D& P2)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Translate(P1, P2);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Rotate(const OneAxis& Ax, double ang)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Rotate(Ax, ang);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Scale(const Point3D& P, double fact)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Scale(P, fact);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Mirror(const Point3D& P)
{
	ListOfPoint3D *temp = new ListOfPoint3D;

	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Mirror(P);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Mirror(const OneAxis& Ax)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Mirror(Ax);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void BSplineCurve::Mirror(const Plane& Pln)
{
	ListOfPoint3D *temp = new ListOfPoint3D;
	Point3D curP;
	ListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Mirror(Pln);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

