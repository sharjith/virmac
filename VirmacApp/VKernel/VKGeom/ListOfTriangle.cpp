// ListOfCTriangle.cpp: implementation of the CListOfCTriangle class.
//
//////////////////////////////////////////////////////////////////////



#include "ListOfTriangle.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListOfTriangle::ListOfTriangle() : firstPtr(0), lastPtr(0)
{
}


ListOfTriangle::~ListOfTriangle()
{


	ListNodeOfTriangle* curPtr = firstPtr, *tmp;
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


void ListOfTriangle::Append(const Triangle& data)
{
	ListNodeOfTriangle* newPtr = new ListNodeOfTriangle(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void ListOfTriangle::Prepend(const Triangle& data)
{
	ListNodeOfTriangle* newPtr = new ListNodeOfTriangle(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

Triangle ListOfTriangle::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

Triangle ListOfTriangle::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool ListOfTriangle::IsEmpty() const
{
	return (firstPtr==0);
}		


void ListOfTriangle::Clear()
{
	ListNodeOfTriangle* curPtr = firstPtr, *tmp;
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

ListNodeOfTriangle* ListOfTriangle::NewNode(const Triangle& P)
{
	ListNodeOfTriangle* newPtr= new ListNodeOfTriangle(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
