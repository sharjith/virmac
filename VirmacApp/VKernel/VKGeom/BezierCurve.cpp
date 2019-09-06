// BezierCurve.cpp: implementation of the CBezierCurve class.
//
//////////////////////////////////////////////////////////////////////



#include "BezierCurve.h"
#include "Point3D.h"
#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BezierCurve::BezierCurve()
{
	cType = BEZIER;
}

BezierCurve::BezierCurve(ListOfPoint3D *aList)
{
	cType = BEZIER;
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
	if(cpCount > GetMaxDegree())
		throw GeomException(MaxDegree);
}

BezierCurve::~BezierCurve()
{
	cpList->Clear();
	if(cpList)
		delete cpList;
}

void BezierCurve::Reverse()
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

Point3D BezierCurve::PointAtPara(const double& para)
{
	Point3D P;
	int cnt = 0;
	double x=0, y=0, z=0;
	double degree = cpCount-1;
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

	for(myListIter.Init(); myListIter.More(); myListIter.Next(), cnt++)
	{
		x+=myListIter.Current().GetX()*BlendingFunc((int)degree,cnt,para);
		y+=myListIter.Current().GetY()*BlendingFunc((int)degree,cnt,para);
		z+=myListIter.Current().GetZ()*BlendingFunc((int)degree,cnt,para);
	}
	P.SetParam(x,y,z);
	return P;
}

double BezierCurve::FirstParameter() const
{
	return 0.0;
}

double BezierCurve::LastParameter() const
{
	return 1.0;
}

bool BezierCurve::IsClosed() const
{
	return false;
}

Curve* BezierCurve::Copy() const
{
	BezierCurve* C = new BezierCurve(cpList);
	return C;
}

void BezierCurve::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void BezierCurve::Translate(double dx, double dy, double dz)
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


void BezierCurve::Translate(const Vector3D& V)
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

void BezierCurve::Translate(const Point3D& P1, const Point3D& P2)
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

void BezierCurve::Rotate(const OneAxis& Ax, double ang)
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

void BezierCurve::Scale(const Point3D& P, double fact)
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

void BezierCurve::Mirror(const Point3D& P)
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

void BezierCurve::Mirror(const OneAxis& Ax)
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

void BezierCurve::Mirror(const Plane& Pln)
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

double BezierCurve::BlendingFunc(int n,int r,double t)
{
	long int p=1,m=1;
	int i;
	if(t<1e-5)
		return  (r==0 ?  1.0 : 0.0);
	if(t>.999995)
		return (r==n ? 1.0 : 0.0) ;

	for(i=1;i<=r;i++)
	{
		m*=i;
		p*=(n-i+1);
	}
	return ((double)(p/m))*pow(t,r)*pow(1.0-t,n-r);
}

