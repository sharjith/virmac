// ListNodeOfCTriFacet.cpp: implementation of the CListNodeOfCTriFacet class.
//
//////////////////////////////////////////////////////////////////////

#include "ListNodeOfCTriFacet.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListNodeOfTriFacet::ListNodeOfTriFacet( const TriFacet& P) : data(P), nextPtr(0)
{

}

ListNodeOfTriFacet::~ListNodeOfTriFacet()
{

}

TriFacet ListNodeOfTriFacet::GetData() const
{
	return data;
}

bool ListNodeOfTriFacet::operator==(const ListNodeOfTriFacet& rhs)
{
    if(this == &rhs)
		return true;
	return false;
}

bool ListNodeOfTriFacet::operator!=(const ListNodeOfTriFacet& rhs)
{
    return !(this == &rhs);
}
