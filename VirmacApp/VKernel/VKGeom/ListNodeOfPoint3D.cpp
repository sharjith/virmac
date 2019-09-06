// ListNodeOfCPoint3D.cpp: implementation of the CListNodeOfCPoint3D class.
//
//////////////////////////////////////////////////////////////////////


#include "ListNodeOfPoint3D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListNodeOfPoint3D::ListNodeOfPoint3D( const Point3D& P) : data(P), nextPtr(0)
{

}

ListNodeOfPoint3D::~ListNodeOfPoint3D()
{

}

Point3D ListNodeOfPoint3D::GetData() const
{
	return data;
}

bool ListNodeOfPoint3D::operator==(ListNodeOfPoint3D& rhs)
{
	if(data == rhs.data)
		return true;
	return false;
}

bool ListNodeOfPoint3D::operator!=(ListNodeOfPoint3D& rhs)
{
	return !(*this==rhs);
}
