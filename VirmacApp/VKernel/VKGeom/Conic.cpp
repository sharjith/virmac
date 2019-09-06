// Conic.cpp: implementation of the CConic class.
//
//////////////////////////////////////////////////////////////////////



#include "Conic.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Conic::Conic()
{

}

Conic::~Conic()
{

}

void Conic::Reverse()
{
	Vector3D V = itsLocation.GetDirection();
	V *= -1;
	itsLocation.SetDirection(V);
}

void Conic::SetLocation(const AxisSystem& ax)
{
	itsLocation = ax;
}

