// Vector3d.cpp: implementation of the CVector3d class.
//
//////////////////////////////////////////////////////////////////////



#include "Vector3D.h"
#include "Point3D.h"
#include "Matrix33.h"
#include "OneAxis.h"
#include "Plane.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class vector
Vector3D::Vector3D()
{
	itsX = 0;
	itsY = 0;
	itsZ = 0;
}

Vector3D::Vector3D(double x, double y, double z)
{
	itsX = x;
	itsY = y;
	itsZ = z;
}

Vector3D::Vector3D(const Point3D& P)
{
	itsX = P.GetX();
	itsY = P.GetY();
	itsZ = P.GetZ();
}

Vector3D::Vector3D(const Vector3D &V1, const Vector3D &V2)
{
	Vector3D VC1, VC2, VC3;
	VC1 = V1;
	VC2 = V2;
	VC3 = VC2-VC1;
	itsX = VC3.GetX();
	itsY = VC3.GetY();
	itsZ = VC3.GetZ();
}

Vector3D::Vector3D(const Point3D &V1, const Point3D &V2)
{
	Point3D VC1, VC2;
	VC1 = V1;
	VC2 = V2;
	itsX = VC2.GetX()-VC1.GetX();
	itsY = VC2.GetY()-VC1.GetY();
	itsZ = VC2.GetZ()-VC1.GetZ();
}

Vector3D::~Vector3D()
{
}

double Vector3D::Dot(const Vector3D &V1) const
{
	double result;
	result = V1.GetX()*GetX()+V1.GetY()*GetY()+V1.GetZ()*GetZ();
	return result;
}

double Vector3D::DotCross(const Vector3D &V1, const Vector3D &V2)
{
	Vector3D A = (*this), B = V1, C = V2;
	Vector3D cross = B.Crossed(C);
	double Res = A.Dot(cross);
	return Res;
}

void Vector3D::Cross(const Vector3D &V1)
{
	SetX(GetY()*V1.GetZ()-GetZ()*V1.GetY());
	SetY(GetZ()*V1.GetX()-GetX()*V1.GetZ());
	SetZ(GetX()*V1.GetY()-GetY()*V1.GetX());
}

Vector3D Vector3D::Crossed(const Vector3D &V1) const
{
	Vector3D result;
	result.SetX(GetY()*V1.GetZ()-GetZ()*V1.GetY());
	result.SetY(GetZ()*V1.GetX()-GetX()*V1.GetZ());
	result.SetZ(GetX()*V1.GetY()-GetY()*V1.GetX());
	return result;
}

void Vector3D::CrossCross(const Vector3D &V1, const Vector3D &V2)
{
	Vector3D A = (*this), B = V1, C = V2;
	Vector3D Res = B*((C.Dot(A))) - C*(A.Dot(B));
	(*this) = Res;
}

Vector3D Vector3D::CrossCrossed(const Vector3D &V1, const Vector3D &V2)
{
	Vector3D V = (*this);
	V.CrossCross(V1, V2);
	return V;
}

void Vector3D::Reverse()
{
	this->SetX(-GetX());
	this->SetY(-GetY());
	this->SetZ(-GetZ());
}

Vector3D Vector3D::Reversed()
{
	Vector3D result;
	result.Reverse();
	return result;
}

Vector3D Vector3D::operator + (const Vector3D &V1)
{
	Vector3D result;
	result.SetX(GetX()+V1.GetX());
	result.SetY(GetY()+V1.GetY());
	result.SetZ(GetZ()+V1.GetZ());
	return result;
}

void Vector3D::operator += (const Vector3D &V1)
{
	SetX(GetX()+V1.GetX());
	SetY(GetY()+V1.GetY());
	SetZ(GetZ()+V1.GetZ());
}

Vector3D Vector3D::operator - (const Vector3D &V1)
{
	Vector3D result;
	result.SetX(GetX()-V1.GetX());
	result.SetY(GetY()-V1.GetY());
	result.SetZ(GetZ()-V1.GetZ());
	return result;
}

void Vector3D::operator -= (const Vector3D &V1)
{
	SetX(GetX()-V1.GetX());
	SetY(GetY()-V1.GetY());
	SetZ(GetZ()-V1.GetZ());
}

Vector3D Vector3D::operator * (const double &scalar)
{
	Vector3D result;
	result.SetX(GetX()*scalar);
	result.SetY(GetY()*scalar);
	result.SetZ(GetZ()*scalar);
	return result;
}

Vector3D Vector3D::operator * (const CMatrix33 &M)
{
	Vector3D V;
	V.SetX(M(0,0)*GetX()+M(0,1)*GetY()+M(0,2)*GetZ());
	V.SetY(M(1,0)*GetX()+M(1,1)*GetY()+M(1,2)*GetZ());
	V.SetZ(M(2,0)*GetX()+M(2,1)*GetY()+M(2,2)*GetZ());
	return V;
}

void Vector3D::operator *= (const double &scalar)
{
	SetX(GetX()*scalar);
	SetY(GetY()*scalar);
	SetZ(GetZ()*scalar);
}

void Vector3D::operator *= (const CMatrix33 &M)
{
	SetX(M(0,0)*GetX()+M(0,1)*GetY()+M(0,2)*GetZ());
	SetY(M(1,0)*GetX()+M(1,1)*GetY()+M(1,2)*GetZ());
	SetZ(M(2,0)*GetX()+M(2,1)*GetY()+M(2,2)*GetZ());
}

Vector3D Vector3D::operator / (const double &scalar)
{
	Vector3D result;
	if(!IsNull())
	{
		result.SetX(GetX()/scalar);
		result.SetY(GetY()/scalar);
		result.SetZ(GetZ()/scalar);
	}
	else
	{
		result.SetX(0);
		result.SetY(0);
		result.SetZ(0);
	}
	return result;
}

void Vector3D::operator /= (const double &scalar)
{
	if(!IsNull())
	{
		SetX(GetX()/scalar);
		SetY(GetY()/scalar);
		SetZ(GetZ()/scalar);
	}
	else
	{
		SetX(0);
		SetY(0);
		SetZ(0);
	}
}

Vector3D Vector3D::operator ^ (const Vector3D &V1)
{
	return this->Crossed(V1);
}

void Vector3D::operator ^= (const Vector3D &V1)
{
	this->Cross(V1);
}

bool Vector3D::operator == (const Vector3D& V) const
{
	return(itsX==V.GetX()&&itsY==V.GetY()&&itsZ==V.GetZ());
}

Vector3D::operator Point3D()
{
	Point3D P(itsX, itsY, itsZ);
	return P;
}

double Vector3D::Magnitude() const
{
	if(!IsNull())
	{
		double result;
		result = sqrt(pow((double)GetX(), 2)+pow((double)GetY(), 2)+pow((double)GetZ(), 2));
		return result;
	}
	else
	{
		return 0;
	}
}

double Vector3D::SqrMagnitude() const
{
	if(!IsNull())
	{
		double result;
		result = pow((double)GetX(), 2)+pow((double)GetY(), 2)+pow((double)GetZ(), 2);
		return result;
	}
	else
		return 0;
}

double Vector3D::CrossMagnitude(const Vector3D &V)
{
	if(!IsNull() && !V.IsNull())
	{
		Vector3D V1 = (*this);
		Vector3D V2 = V;
		V1.Cross(V2);
		double result;
		result = sqrt(pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2)+pow((double)V1.GetZ(), 2));
		return result;
	}
	else
	{
		return 0;
	}
}

double Vector3D::CrossSqrMagnitude(const Vector3D &V)
{
	if(!IsNull() && !V.IsNull())
	{
		Vector3D V1 = (*this);
		Vector3D V2 = V;
		V1.Cross(V2);
		double result;
		result = pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2)+pow((double)V1.GetZ(), 2);
		return result;
	}
	else
	{
		return 0;
	}
}

double Vector3D::Modulus()
{
	return sqrt(itsX*itsX + itsY*itsY + itsZ*itsZ);
}

Vector3D Vector3D::Unit()
{
	Vector3D result;
	double x, y, z;
	if(!IsNull())
	{
		x = GetX()/Magnitude();
		y = GetY()/Magnitude();
		z = GetZ()/Magnitude();
		result.SetX(x);
		result.SetY(y);
		result.SetZ(z);
		return result;
	}
	else
		return *this;
}

Point3D Vector3D::Point() const
{
	Point3D aPnt;
	aPnt.SetParam(GetX(), GetY(), GetZ());
	return aPnt;
}

double Vector3D::Angle(const Vector3D& Other) const
{
	double theta, a, b, dot;
	Vector3D tempV = Other;
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

double Vector3D::Angle(const Vector3D& Other, const Vector3D& Dir) const
{
	double theta;
	Vector3D tempV = Other;
	Vector3D D = Dir;
	Vector3D N = this->Crossed(tempV);
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

bool Vector3D::IsNull() const
{
	if(itsX==0&&itsY==0&&itsZ==0)
		return true;
	else
		return false;
}

bool Vector3D::IsParallel(const Vector3D& V) const
{
	/*double ang=0;
	CVector3D tempV = V;
	ang = this->Angle(tempV);
	if(ang==0 || ang==(double)2*PI)
		return true;
	else
		return false;*/
	Vector3D N = this->Crossed(V);
	return (N.IsNull());
}

bool Vector3D::IsOpposite(const Vector3D& V) const

{
	double ang=0;
	Vector3D tempV = V;
	ang = this->Angle(tempV);
	if(fabs(ang-PI)<=0.0001)

		return true;
	else
		return false;
}

bool Vector3D::IsNormal(const Vector3D& V) const
{
	double ang=0;
	Vector3D tempV = V;
	ang = this->Angle(tempV);
	if(fabs(ang-PI/2)<=0.0001)
		return true;
	else
		return false;
}

void Vector3D::Print() const
{
	cout<<"X = "<<GetX()<<endl;
	cout<<"Y = "<<GetY()<<endl;
	cout<<"Z = "<<GetZ()<<endl;
}

void Vector3D::Normalize()
{
	double x, y, z;
	if(!IsNull())
	{
		x = GetX()/Magnitude();
		y = GetY()/Magnitude();
		z = GetZ()/Magnitude();
		SetX(x);
		SetY(y);
		SetZ(z);
	}
	else
		return;
}

void Vector3D::Translate(const OneAxis& Ax, const double& amt)
{
	Geometry::Translate(Ax, amt);
}

void Vector3D::Translate(double dx, double dy, double dz)
{
	Point3D P = (*this);
	P.Translate(dx, dy, dz);
	Vector3D V = P;
	(*this) = V;

}

void Vector3D::Translate(const Vector3D& dV)
{
	Point3D P = (*this);
	P.Translate(dV);
	Vector3D V = P;
	(*this) = V;
}

void Vector3D::Translate(const Point3D& P1, const Point3D& P2)
{
	Point3D P = (*this);
	P.Translate(P1, P2);
	Vector3D V = P;
	(*this) = V;
}

void Vector3D::Rotate(const OneAxis& Ax, double ang)
{
	OneAxis ax = Ax;
	Vector3D P1 = ax.GetOrigin();
	Vector3D V = ax.GetDirection();
	V.Normalize();
	CMatrix33 M; Vector3D PV(*this);
	M.SetRotation(V, ang);
	Vector3D RV = M*(PV-P1);
	RV = RV + P1;
	*this = RV;
}

void Vector3D::Scale(const Point3D& P1, double fact)
{
	Point3D P = (*this);
	P.Scale(P1, fact);
	Vector3D V = P;
	(*this) = V;
}

void Vector3D::Mirror(const Point3D& P1)
{
	Point3D P = (*this);
	P.Mirror(P1);
	Vector3D V = P;
	(*this) = V;
}

void Vector3D::Mirror(const OneAxis& Ax)
{
	Point3D P = (*this);
	P.Mirror(Ax);
	Vector3D V = P;
	(*this) = V;
}

void Vector3D::Mirror(const Plane& Pln)
{
	Point3D P = (*this);
	P.Mirror(Pln);
	Vector3D V = P;
	(*this) = V;
}

Vector3D Vector3D::Origin()
{
	return Vector3D(0,0,0);
}

std::istream &operator>>(std::istream& input, Vector3D &p)
{
    input>>p.itsX>>p.itsY>>p.itsZ;
    return input;
}

std::ostream &operator<<(std::ostream& output, Vector3D &p)
{
    output<< p.itsX << " " << p.itsY << " " << p.itsZ;
    return output;
}

