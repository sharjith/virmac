// ListNodeOfCTriangle.cpp: implementation of the CListNodeOfCTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "ListNodeOfCTriangle.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfCTriangle::CListNodeOfCTriangle( const CTriangle& P) : data(P), nextPtr(0)
{

}

CListNodeOfCTriangle::~CListNodeOfCTriangle()
{

}

CTriangle CListNodeOfCTriangle::GetData() const
{
	return data;
}

bool CListNodeOfCTriangle::operator==(CListNodeOfCTriangle& rhs)
{
	if(*this==rhs)
		return true;
	return false;
}

bool CListNodeOfCTriangle::operator!=(CListNodeOfCTriangle& rhs)
{
	return !(*this==rhs);
}
