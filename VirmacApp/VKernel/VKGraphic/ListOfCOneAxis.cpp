// ListOfCOneAxis.cpp: implementation of the CListOfCOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfCOneAxis.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfCOneAxis::CListOfCOneAxis() : firstPtr(0), lastPtr(0)
{
}


CListOfCOneAxis::~CListOfCOneAxis()
{


	CListNodeOfCOneAxis* curPtr = firstPtr, *tmp;
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


void CListOfCOneAxis::Append(const COneAxis& data)
{
	CListNodeOfCOneAxis* newPtr = new CListNodeOfCOneAxis(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void CListOfCOneAxis::Prepend(const COneAxis& data)
{
	CListNodeOfCOneAxis* newPtr = new CListNodeOfCOneAxis(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

COneAxis CListOfCOneAxis::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

COneAxis CListOfCOneAxis::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool CListOfCOneAxis::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfCOneAxis::Clear()
{
	CListNodeOfCOneAxis* curPtr = firstPtr, *tmp;
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

CListNodeOfCOneAxis* CListOfCOneAxis::NewNode(const COneAxis& P)
{
	CListNodeOfCOneAxis* newPtr= new CListNodeOfCOneAxis(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
