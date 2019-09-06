// Matrix22.cpp: implementation of the CMatrix22 class.
//
//////////////////////////////////////////////////////////////////////


#include "Matrix22.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of CMatrix22 class
CMatrix22::CMatrix22()
{
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=0;
	}
    }
}

CMatrix22::CMatrix22(double R1[2], double R2[2])
{
    int i;
    for(i=0;i<2;i++)
    {
	Row[0][i]=R1[i];
    }
    for(i=0;i<2;i++)
    {
	Row[1][i]=R2[i];
    }
}

CMatrix22::~CMatrix22()
{
}

CMatrix22 CMatrix22::operator*(const CMatrix22 &Other)
{
    int i,j,k;
    CMatrix22 New;
    double temp[2][2];
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    temp[i][j]=0;
	}
    }

    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    for(k=0;k<2;k++)
	    {
		temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
	    }
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=temp[i][j];
	}
    }
    return New;
}

Vector2D CMatrix22::operator*(const Vector2D &Other)
{
    Vector2D O = Other;
    Vector2D Result;

    Result.SetX(this->Row[0][0]*O.GetX() + this->Row[0][1]*O.GetY());
    Result.SetY(this->Row[1][0]*O.GetX() + this->Row[1][1]*O.GetY());

    return Result;
}

CMatrix22 CMatrix22::operator*(double value)
{
    CMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]*=value;
	}
    }
    return New;
}

void CMatrix22::operator*=(const CMatrix22 &Other)
{
    int i,j,k;
    double temp[2][2];
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    temp[i][j]=0;
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    for(k=0;k<2;k++)
	    {
		temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
	    }
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=temp[i][j];
	}
    }
}

void CMatrix22::operator*=(double value)
{
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]*=value;
	}
    }
}

CMatrix22 CMatrix22::operator/(const double Value)
{
    CMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]/=Value;
	}
    }
    return New;
}

void CMatrix22::operator/=(const double Value)
{
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]/=Value;
	}
    }
}

CMatrix22 CMatrix22::operator+(const CMatrix22 &Other)
{
    CMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]+=Other.Row[i][j];
	}
    }
    return New;
}

void CMatrix22::operator+=(const CMatrix22 &Other)
{
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]+=Other.Row[i][j];
	}
    }
}

CMatrix22 CMatrix22::operator-(const CMatrix22 &Other)
{
    CMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)

	{
	    New.Row[i][j]-=Other.Row[i][j];

	}
    }
    return New;
}

void CMatrix22::operator-=(const CMatrix22 &Other)
{
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]-=Other.Row[i][j];
	}
    }
}

double CMatrix22::Determinant()
{
    double D;
    D=(Row[0][0]*(Row[1][1] - Row[0][1]*Row[1][0]));
    return D;
}

void CMatrix22::Invert()
{
    CMatrix22 tmpCMatrix22;
    if(Determinant()==0)
	throw GeomException(DivideByZero);
    tmpCMatrix22=Adjoint()/Determinant();
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=tmpCMatrix22.Row[i][j];
	}
    }
}

CMatrix22 CMatrix22::Inverted() const
{
    CMatrix22 tmpCMatrix22;
    tmpCMatrix22.Invert();
    return tmpCMatrix22;
}

void CMatrix22::Transpose()
{
    double temp[2][2];
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    temp[i][j]=Row[j][i];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=temp[i][j];
	}
    }
}

void CMatrix22::Value() const
{
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    cout<<" "<<Row[i][j];
	}
	cout<<"\n";
    }
    cout<<"\n";
}

bool CMatrix22::IsNull() const
{
    int i,j,flag=0;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
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

bool CMatrix22::IsDiagonal() const
{
    if(Row[0][0]==0&&Row[1][1]==0)
	return true;
    return false;
}

bool CMatrix22::IsSymmetrical() const
{
    int i,j,flag=0;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
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

bool CMatrix22::IsScalar() const
{
    if(Row[0][0]==Row[1][1])
	return true;
    return false;
}

bool CMatrix22::IsIdentity() const
{
    if(Row[0][0]==1 && Row[1][1]==1 && Row[0][1]==0 && Row[1][0]==0)
	return true;
    return false;
}

bool CMatrix22::IsEqual(const CMatrix22 &Other) const
{
    int i,j,flag=0;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
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

CMatrix22 CMatrix22::Adjoint()
{
    CMatrix22 tmpCMatrix22;
    Transpose();
    //A11
    tmpCMatrix22.Row[0][0] =  1*(Row[1][1]);
    //B12
    tmpCMatrix22.Row[0][1] = -1*(Row[1][0]);
    //A21
    tmpCMatrix22.Row[1][0]=   1*(Row[0][1]);
    //B22
    tmpCMatrix22.Row[1][1] = -1*(Row[0][0]);
    Transpose();
    return tmpCMatrix22;
}

void CMatrix22::SetIdentity()
{
    //Identity Matrix
    double Row1[2]={1,0};
    double Row2[2]={0,1};
    CMatrix22 M(Row1, Row2);
    *this = M;
}

void CMatrix22::SetRotation(double t)
{

    /*double nx, ny, nz;
    nx = Axis.GetX(); ny = Axis.GetY(); nz = Axis.GetZ();
    double Row1[3]={ nx*nx*vsin(t)+cos(t), nx*ny*vsin(t)-nz*sin(t), nx*nz*vsin(t)+ny*sin(t)};
    double Row2[3]={ nx*ny*vsin(t)+nz*sin(t), ny*ny*vsin(t)+cos(t), ny*nz*vsin(t)-nx*sin(t)};
    double Row3[3]={ nx*nz*vsin(t)-ny*sin(t), ny*nz*vsin(t)+nx*sin(t), nz*nz*vsin(t)+cos(t)};
    CMatrix22 M(Row1, Row2, Row3);
    *this = M;*/
    double Row1[2]={cos(t), -1*sin(t)};
    double Row2[2]={sin(t), cos(t)};
    CMatrix22 M(Row1, Row2);
    *this = M;
}

void CMatrix22::SetScale(const Point2D& Point)
{
    Point2D P = Point;
    double Row1[2]={P.GetX(),          0};
    double Row2[2]={0       ,   P.GetY()};
    CMatrix22 M(Row1, Row2);
    *this = M;
}

Point2D CMatrix22::GetDiagonal() const
{
    Point2D V;
    CMatrix22 M = *this;
    V.SetX(M(0,0));
    V.SetY(M(1,1));
    return V;
}
