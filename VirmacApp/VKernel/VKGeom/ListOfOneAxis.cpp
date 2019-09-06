// ListOfCOneAxis.cpp: implementation of the CListOfCOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfOneAxis.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListOfOneAxis::ListOfOneAxis() : firstPtr(0), lastPtr(0)
{
}


ListOfOneAxis::~ListOfOneAxis()
{


	ListNodeOfOneAxis* curPtr = firstPtr, *tmp;
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


void ListOfOneAxis::Append(const OneAxis& data)
{
	ListNodeOfOneAxis* newPtr = new ListNodeOfOneAxis(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void ListOfOneAxis::Prepend(const OneAxis& data)
{
	ListNodeOfOneAxis* newPtr = new ListNodeOfOneAxis(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

OneAxis ListOfOneAxis::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

OneAxis ListOfOneAxis::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool ListOfOneAxis::IsEmpty() const
{
	return (firstPtr==0);
}		


void ListOfOneAxis::Clear()
{
	ListNodeOfOneAxis* curPtr = firstPtr, *tmp;
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

ListNodeOfOneAxis* ListOfOneAxis::NewNode(const OneAxis& P)
{
	ListNodeOfOneAxis* newPtr= new ListNodeOfOneAxis(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
