// ListNodeOfNCBlock.cpp: implementation of the CListNodeOfNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "ListNodeOfNCBlock.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListNodeOfNCBlock::ListNodeOfNCBlock( const NCBlock& P) : data(P), nextPtr(0)
{

}

ListNodeOfNCBlock::~ListNodeOfNCBlock()
{

}

NCBlock ListNodeOfNCBlock::GetData() const
{
	return data;
}

bool ListNodeOfNCBlock::operator==(const ListNodeOfNCBlock& rhs)
{
    if(this == &rhs)
		return true;
	return false;
}

bool ListNodeOfNCBlock::operator!=(const ListNodeOfNCBlock& rhs)
{
    return !(this == &rhs);
}
