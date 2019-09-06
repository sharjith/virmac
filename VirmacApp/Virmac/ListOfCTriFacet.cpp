// ListOfCTriFacet.cpp: implementation of the CListOfCTriFacet class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfCTriFacet.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListOfTriFacet::ListOfTriFacet() : firstPtr(0), lastPtr(0)
{
}


ListOfTriFacet::~ListOfTriFacet()
{


	ListNodeOfTriFacet* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
	}
}


void ListOfTriFacet::Append(const TriFacet& data)
{
	ListNodeOfTriFacet* newPtr = new ListNodeOfTriFacet(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void ListOfTriFacet::Prepend(const TriFacet& data)
{
	ListNodeOfTriFacet* newPtr = new ListNodeOfTriFacet(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

TriFacet ListOfTriFacet::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

TriFacet ListOfTriFacet::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool ListOfTriFacet::IsEmpty() const
{
	return (firstPtr==0);
}		


void ListOfTriFacet::Clear()
{
	ListNodeOfTriFacet* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
		
		firstPtr = lastPtr = 0;
	}
}

ListNodeOfTriFacet* ListOfTriFacet::NewNode(const TriFacet& P)
{
	ListNodeOfTriFacet* newPtr= new ListNodeOfTriFacet(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
