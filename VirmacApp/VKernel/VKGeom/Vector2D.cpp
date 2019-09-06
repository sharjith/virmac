// Vector2D.cpp: implementation of the CVector2D class.
//
//////////////////////////////////////////////////////////////////////



#include "Vector2D.h"
#include "Point2D.h"
#include "Matrix22.h"
#include "OneAxis2D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class vector
Vector2D::Vector2D()
{
    itsX = 0;
    itsY = 0;
}

Vector2D::Vector2D(double x, double y)
{
    itsX = x;
    itsY = y;
}

Vector2D::Vector2D(const Point2D& P)
{
    itsX = P.GetX();
    itsY = P.GetY();
}

Vector2D::Vector2D(const Vector2D &V1, const Vector2D &V2)
{
    Vector2D VC1, VC2, VC3;
    VC1 = V1;
    VC2 = V2;
    VC3 = VC2-VC1;
    itsX = VC3.GetX();
    itsY = VC3.GetY();
}

Vector2D::Vector2D(const Point2D &V1, const Point2D &V2)
{
    Point2D VC1, VC2;
    VC1 = V1;
    VC2 = V2;
    itsX = VC2.GetX()-VC1.GetX();
    itsY = VC2.GetY()-VC1.GetY();
}

Vector2D::~Vector2D()
{
}

double Vector2D::Dot(const Vector2D &V1) const
{
    double result;
    result = V1.GetX()*GetX()+V1.GetY()*GetY();
    return result;
}

double Vector2D::DotCross(const Vector2D &V1, const Vector2D &V2)
{
    Vector2D A = (*this), B = V1, C = V2;
    Vector2D cross = B.Crossed(C);
    double Res = A.Dot(cross);
    return Res;
}

void Vector2D::Cross(const Vector2D& V1)
{
    SetX(GetY()-V1.GetY());
    SetY(V1.GetX()-GetX());
}

Vector2D Vector2D::Crossed(const Vector2D& V1) const
{
    Vector2D result;
    result.SetX(GetY()-V1.GetY());
    result.SetY(V1.GetX()-GetX());
    return result;
}

void Vector2D::CrossCross(const Vector2D &V1, const Vector2D &V2)
{
    Vector2D A = (*this), B = V1, C = V2;
    Vector2D Res = B*((C.Dot(A))) - C*(A.Dot(B));
    (*this) = Res;
}

Vector2D Vector2D::CrossCrossed(const Vector2D &V1, const Vector2D &V2)
{
    Vector2D V = (*this);
    V.CrossCross(V1, V2);
    return V;
}

void Vector2D::Reverse()
{
    this->SetX(-GetX());
    this->SetY(-GetY());
}

Vector2D Vector2D::Reversed()
{
    Vector2D result;
    result.Reverse();
    return result;
}

Vector2D Vector2D::operator + (const Vector2D &V1)
{
    Vector2D result;
    result.SetX(GetX()+V1.GetX());
    result.SetY(GetY()+V1.GetY());
    return result;
}

void Vector2D::operator += (const Vector2D &V1)
{
    SetX(GetX()+V1.GetX());
    SetY(GetY()+V1.GetY());
}

Vector2D Vector2D::operator - (const Vector2D &V1)
{
    Vector2D result;
    result.SetX(GetX()-V1.GetX());
    result.SetY(GetY()-V1.GetY());
    return result;
}

void Vector2D::operator -= (const Vector2D &V1)
{
    SetX(GetX()-V1.GetX());
    SetY(GetY()-V1.GetY());
}

Vector2D Vector2D::operator * (const double &scalar)
{
    Vector2D result;
    result.SetX(GetX()*scalar);
    result.SetY(GetY()*scalar);
    return result;
}

Vector2D Vector2D::operator * (const CMatrix22 &M)
{
   Vector2D V;
   V.SetX(M(0,0)*GetX()+M(0,1)*GetY());
   V.SetY(M(1,0)*GetX()+M(1,1)*GetY());
   return V;
}


void Vector2D::operator *= (const double &scalar)
{
    SetX(GetX()*scalar);
    SetY(GetY()*scalar);
}


void Vector2D::operator *= (const CMatrix22 &M)
{
   SetX(M(0,0)*GetX()+M(0,1)*GetY());
   SetY(M(1,0)*GetX()+M(1,1)*GetY());
}

Vector2D Vector2D::operator / (const double &scalar)
{
    Vector2D result;
    if(!IsNull())
    {
	result.SetX(GetX()/scalar);
	result.SetY(GetY()/scalar);
    }
    else
    {
	result.SetX(0);
	result.SetY(0);
    }
    return result;
}

void Vector2D::operator /= (const double &scalar)
{
    if(!IsNull())
    {
	SetX(GetX()/scalar);
	SetY(GetY()/scalar);
    }
    else
    {
	SetX(0);
	SetY(0);
    }
}

Vector2D Vector2D::operator ^ (const Vector2D &V1)
{
    return this->Crossed(V1);
}

void Vector2D::operator ^= (const Vector2D &V1)
{
    this->Cross(V1);
}

bool Vector2D::operator == (const Vector2D& V) const
{
    return(itsX==V.GetX()&&itsY==V.GetY());
}

Vector2D::operator Point2D()
{
    Point2D P(itsX, itsY);
    return P;
}

double Vector2D::Magnitude() const
{
    if(!IsNull())
    {
	double result;
	result = sqrt(pow((double)GetX(), 2)+pow((double)GetY(), 2));
	return result;
    }
    else
    {
	return 0;
    }
}

double Vector2D::SqrMagnitude() const
{
    if(!IsNull())
    {
	double result;
	result = pow((double)GetX(), 2)+pow((double)GetY(), 2);
	return result;
    }
    else
	return 0;
}

double Vector2D::CrossMagnitude(const Vector2D &V)
{
    if(!IsNull() && !V.IsNull())
    {
	Vector2D V1 = (*this);
	Vector2D V2 = V;
	V1.Cross(V2);
	double result;
	result = sqrt(pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2));
	return result;
    }
    else
    {
	return 0;
    }
}

double Vector2D::CrossSqrMagnitude(const Vector2D &V)
{
    if(!IsNull() && !V.IsNull())
    {
	Vector2D V1 = (*this);
	Vector2D V2 = V;
	V1.Cross(V2);
	double result;
	result = pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2);
	return result;
    }
    else
    {
	return 0;
    }
}

double Vector2D::Modulus()
{
    return sqrt(itsX*itsX + itsY*itsY);
}

Vector2D Vector2D::Unit()
{
    Vector2D result;
    double x, y;
    if(!IsNull())
    {
	x = GetX()/Magnitude();
	y = GetY()/Magnitude();
	result.SetX(x);
	result.SetY(y);
	return result;
    }
    else
	return *this;
}

Point2D Vector2D::Point()
{
    Point2D aPnt;
    aPnt.SetParam(GetX(), GetY());
    return aPnt;
}

double Vector2D::Angle(const Vector2D& Other) const
{
    double theta, a, b, dot;
    Vector2D tempV = Other;
    if(!this->IsNull() && !tempV.IsNull())
    {
	dot = this->Dot(Other);
	a = this->Magnitude();
	b = tempV.Magnitude();
	theta = acos(dot/(a*b));
	return theta;
    }
    else
	return 0;
}

double Vector2D::Angle(const Vector2D& Other, const Vector2D& Dir) const
{
    double theta;
    Vector2D tempV = Other;
    Vector2D D = Dir;
    Vector2D N = this->Crossed(tempV);
    if(!this->IsNull() && !tempV.IsNull())
    {
	theta = Angle(Other);

	if(IsOpposite(tempV))
	{
	    return PI;
	}
	else
	{
	    if(N.Angle(D)<=0.0001)

		return theta;
	    else
		return -theta;
	}
    }
    else
	return 0;
}

bool Vector2D::IsNull() const
{
    if(itsX==0&&itsY==0)
	return true;
    return false;
}

bool Vector2D::IsParallel(const Vector2D& V) const
{
    /*double ang=0;
      CVector2D tempV = V;
      ang = this->Angle(tempV);
      if(ang==0 || ang==(double)2*PI)
      return true;
      else
      return false;*/
    Vector2D N = this->Crossed(V);
    return (N.IsNull());
}

bool Vector2D::IsOpposite(const Vector2D& V) const

{
    double ang=0;
    Vector2D tempV = V;
    ang = this->Angle(tempV);
    if(fabs(ang-PI)<=0.0001)

	return true;
    else
	return false;
}

bool Vector2D::IsNormal(const Vector2D& V) const
{
    double ang=0;
    Vector2D tempV = V;
    ang = this->Angle(tempV);
    if(fabs(ang-PI/2)<=0.0001)
	return true;
    else
	return false;
}

void Vector2D::Print() const
{
    cout<<"X = "<<GetX()<<endl;
    cout<<"Y = "<<GetY()<<endl;
}

void Vector2D::Normalize()
{
    double x, y;
    if(!IsNull())
    {
	x = GetX()/Magnitude();
	y = GetY()/Magnitude();
	SetX(x);
	SetY(y);
    }
    else
	return;
}

void Vector2D::Translate(const COneAxis2D& Ax, const double& amt)
{
    Geometry2D::Translate(Ax, amt);
}

void Vector2D::Translate(double dx, double dy)
{
    Point2D P = (*this);
    P.Translate(dx, dy);
    Vector2D V = P;
    (*this) = V;

}

void Vector2D::Translate(const Vector2D& dV)
{
    Point2D P = (*this);
    P.Translate(dV);
    Vector2D V = P;
    (*this) = V;
}

void Vector2D::Translate(const Point2D& P1, const Point2D& P2)
{
    Point2D P = (*this);
    P.Translate(P1, P2);
    Vector2D V = P;
    (*this) = V;
}

void Vector2D::Rotate(const Point2D& Pt, double ang)
{
    Point2D P1 = Pt;
    CMatrix22 M;
    M.SetRotation(ang);
    Point2D tp = *this - (Vector2D)P1;
    Vector2D V = M * (Vector2D)tp;
    V += (Vector2D)P1;
    *this = V;
}

void Vector2D::Scale(const Point2D& P1, double fact)
{
    Point2D P = (*this);
    P.Scale(P1, fact);
    Vector2D V = P;
    (*this) = V;
}

void Vector2D::Mirror(const Point2D& P1)
{
    Point2D P = (*this);
    P.Mirror(P1);
    Vector2D V = P;
    (*this) = V;
}

void Vector2D::Mirror(const COneAxis2D& Ax)
{
    Point2D P = (*this);
    P.Mirror(Ax);
    Vector2D V = P;
    (*this) = V;
}

Vector2D Vector2D::Origin()
{
    return Vector2D(0,0);
}
