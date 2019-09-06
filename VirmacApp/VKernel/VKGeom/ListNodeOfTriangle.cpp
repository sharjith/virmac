// ListNodeOfCTriangle.cpp: implementation of the CListNodeOfCTriangle class.
//
//////////////////////////////////////////////////////////////////////


#include "ListNodeOfTriangle.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListNodeOfTriangle::ListNodeOfTriangle( const Triangle& P) : data(P), nextPtr(0)
{

}

ListNodeOfTriangle::~ListNodeOfTriangle()
{

}

Triangle ListNodeOfTriangle::GetData() const
{
	return data;
}

bool ListNodeOfTriangle::operator==(ListNodeOfTriangle& rhs)
{
	if(data == rhs.data)
		return true;
	return false;
}

bool ListNodeOfTriangle::operator!=(ListNodeOfTriangle& rhs)
{
	return !(*this==rhs);
}
