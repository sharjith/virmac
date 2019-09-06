// Matrix33.cpp: implementation of the CMatrix33 class.
//
//////////////////////////////////////////////////////////////////////

#include "Matrix33.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of CMatrix33 class
CMatrix33::CMatrix33()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=0;
		}
	}
}

CMatrix33::CMatrix33(double R1[3], double R2[3], double R3[3])
{
	int i;
	for(i=0;i<3;i++)
	{
		Row[0][i]=R1[i];
	}
    for(i=0;i<3;i++)
	{
		Row[1][i]=R2[i];
	}
	for(i=0;i<3;i++)
	{
		Row[2][i]=R3[i];
	}
}

CMatrix33::~CMatrix33()
{
}

CMatrix33 CMatrix33::operator*(const CMatrix33 &Other)
{
	int i,j,k;
	CMatrix33 New;
	double temp[3][3];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
		}
	}


	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
			}
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=temp[i][j];
		}
	}
	return New;
}

Vector3D CMatrix33::operator*(const Vector3D &Other)
{
	Vector3D O = Other;
	Vector3D Result;

	Result.SetX(this->Row[0][0]*O.GetX() + this->Row[0][1]*O.GetY() + this->Row[0][2]*O.GetZ());
	Result.SetY(this->Row[1][0]*O.GetX() + this->Row[1][1]*O.GetY() + this->Row[1][2]*O.GetZ());
	Result.SetZ(this->Row[2][0]*O.GetX() + this->Row[2][1]*O.GetY() + this->Row[2][2]*O.GetZ());

	return Result;
}

CMatrix33 CMatrix33::operator*(double value)
{
	CMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]*=value;
		}
	}
	return New;
}

void CMatrix33::operator*=(const CMatrix33 &Other)
{
	int i,j,k;
	double temp[3][3];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
			}
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=temp[i][j];
		}
	}
}

void CMatrix33::operator*=(double value)
{
	int i, j;
    for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]*=value;
		}
	}
}

CMatrix33 CMatrix33::operator/(const double Value)
{
	CMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]/=Value;
		}
	}
	return New;
}

void CMatrix33::operator/=(const double Value)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]/=Value;
		}
	}
}

CMatrix33 CMatrix33::operator+(const CMatrix33 &Other)
{
	CMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]+=Other.Row[i][j];
		}
	}
	return New;
}

void CMatrix33::operator+=(const CMatrix33 &Other)
{
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]+=Other.Row[i][j];
		}
	}
}

CMatrix33 CMatrix33::operator-(const CMatrix33 &Other)
{
	CMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)

		{
			New.Row[i][j]-=Other.Row[i][j];

		}
	}
	return New;
}

void CMatrix33::operator-=(const CMatrix33 &Other)
{
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]-=Other.Row[i][j];
		}
	}
}

double CMatrix33::Determinant()
{
	double D;
	D=(Row[0][0]*(Row[1][1]*Row[2][2]-Row[2][1]*Row[1][2]))
		-(Row[0][1]*(Row[1][0]*Row[2][2]-Row[2][0]*Row[1][2]))
		+(Row[0][2]*(Row[1][0]*Row[2][1]-Row[2][0]*Row[1][1]));
	return D;
}

void CMatrix33::Invert()
{
	CMatrix33 tmpCMatrix33;
	if(Determinant()==0)
		throw GeomException(DivideByZero);
	tmpCMatrix33=Adjoint()/Determinant();
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=tmpCMatrix33.Row[i][j];
		}
	}
}

CMatrix33 CMatrix33::Inverted() const
{
	CMatrix33 tmpCMatrix33;
	tmpCMatrix33.Invert();
	return tmpCMatrix33;
}

void CMatrix33::Transpose()
{
	double temp[3][3];
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=Row[j][i];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=temp[i][j];
		}
	}
}

void CMatrix33::Value() const
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cout<<" "<<Row[i][j];
		}
		cout<<"\n";
	}
	cout<<"\n";
}

bool CMatrix33::IsNull() const
{
	int i,j,flag=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(Row[i][j]!=0)
			{
				flag=1;
					break;
			}
		}
	}
	if(flag==1)
		return false;
	return true;
}

bool CMatrix33::IsDiagonal() const
{
	if(Row[1][0]==0&&Row[2][0]==0&&Row[2][1]==0
		&&Row[0][1]==0&&Row[0][2]==0&&Row[1][2]==0)
		return true;
	return false;
}

bool CMatrix33::IsSymmetrical() const
{
	int i,j,flag=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(Row[j][i] != Row[i][j])
			{
				flag=1;
					break;
			}
		}
	}
	if(flag==1)
		return false;
	return true;
}

bool CMatrix33::IsScalar() const
{
	if(Row[0][0]==Row[1][1] && Row[1][1]==Row[2][2]
		 && Row[0][0]==Row[2][2])
		return true;
	return false;
}

bool CMatrix33::IsIdentity() const
{
	if(Row[0][0]==1&&Row[1][1]==1&&Row[2][2]==1&&Row[0][1]==0
		&&Row[0][2]==0&&Row[1][0]==0&&Row[1][2]==0&&Row[2][0]==0
		&&Row[2][1]==0)
		return true;
	return false;
}

bool CMatrix33::IsEqual(const CMatrix33 &Other) const
{
	int i,j,flag=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(Row[i][j] != Other.Row[i][j])
			{
				flag=1;
					break;
			}
		}

	}
	if(flag==1)
		return false;
	return true;
}

CMatrix33 CMatrix33::Adjoint()
{
	CMatrix33 tmpCMatrix33;
	Transpose();
	//A11
	tmpCMatrix33.Row[0][0]=
		1*(Row[1][1]*Row[2][2]-Row[2][1]*Row[1][2]);
	//B12
	tmpCMatrix33.Row[0][1]=
		-1*(Row[1][0]*Row[2][2]-Row[2][0]*Row[1][2]);
	//C13
	tmpCMatrix33.Row[0][2]=
		1*(Row[1][0]*Row[2][1]-Row[2][0]*Row[1][1]);
	//A21
	tmpCMatrix33.Row[1][0]=
		-1*(Row[0][1]*Row[2][2]-Row[2][1]*Row[0][2]);
	//B22
	tmpCMatrix33.Row[1][1]=
		1*(Row[0][0]*Row[2][2]-Row[2][0]*Row[0][2]);
	//C23
	tmpCMatrix33.Row[1][2]=
		-1*(Row[0][0]*Row[2][1]-Row[2][0]*Row[0][1]);
	//A31
	tmpCMatrix33.Row[2][0]=
		1*(Row[0][1]*Row[1][2]-Row[1][1]*Row[0][2]);
	//B32
	tmpCMatrix33.Row[2][1]=
		-1*(Row[0][0]*Row[1][2]-Row[1][0]*Row[0][2]);
	//C33
	tmpCMatrix33.Row[2][2]=
		1*(Row[0][0]*Row[1][1]-Row[1][0]*Row[0][1]);
	Transpose();
	return tmpCMatrix33;
}

void CMatrix33::SetIdentity()
{
	//Identity Matrix
	double Row1[3]={1,0,0};
	double Row2[3]={0,1,0};
	double Row3[3]={0,0,1};
	CMatrix33 M(Row1, Row2, Row3);
	*this = M;
}

void CMatrix33::SetRotation(const Vector3D& Axis, double t)
{

	double nx, ny, nz;
	nx = Axis.GetX(); ny = Axis.GetY(); nz = Axis.GetZ();
	double Row1[3]={ nx*nx*vsin(t)+cos(t), nx*ny*vsin(t)-nz*sin(t), nx*nz*vsin(t)+ny*sin(t)};
	double Row2[3]={ nx*ny*vsin(t)+nz*sin(t), ny*ny*vsin(t)+cos(t), ny*nz*vsin(t)-nx*sin(t)};
	double Row3[3]={ nx*nz*vsin(t)-ny*sin(t), ny*nz*vsin(t)+nx*sin(t), nz*nz*vsin(t)+cos(t)};
	CMatrix33 M(Row1, Row2, Row3);
	*this = M;
}

void CMatrix33::SetScale(const Point3D& Point)
{
	Point3D P = Point;
	double Row1[3]={P.GetX(),          0,          0};
	double Row2[3]={         0, P.GetY(),          0};
	double Row3[3]={         0, 0,          P.GetZ()};
	CMatrix33 M(Row1, Row2, Row3);
	*this = M;
}

Point3D CMatrix33::GetDiagonal() const
{
	Point3D V;
	CMatrix33 M = *this;
	V.SetX(M(0,0));
	V.SetY(M(1,1));
	V.SetZ(M(2,2));
	return V;
}
