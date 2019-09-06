// ListNodeOfCOneAxis.cpp: implementation of the CListNodeOfCOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "ListNodeOfOneAxis.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListNodeOfOneAxis::ListNodeOfOneAxis( const OneAxis& P) : data(P), nextPtr(0)
{

}

ListNodeOfOneAxis::~ListNodeOfOneAxis()
{

}

OneAxis ListNodeOfOneAxis::GetData() const
{
	return data;
}

bool ListNodeOfOneAxis::operator==(ListNodeOfOneAxis& rhs)
{
	if(data == rhs.data)
		return true;
	else
		return false;
}

bool ListNodeOfOneAxis::operator!=(ListNodeOfOneAxis& rhs)
{
	return !(*this==rhs);
}
