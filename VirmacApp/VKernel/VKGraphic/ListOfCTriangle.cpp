// ListOfCTriangle.cpp: implementation of the CListOfCTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfCTriangle.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfCTriangle::CListOfCTriangle() : firstPtr(0), lastPtr(0)
{
}


CListOfCTriangle::~CListOfCTriangle()
{


	CListNodeOfCTriangle* curPtr = firstPtr, *tmp;
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


void CListOfCTriangle::Append(const CTriangle& data)
{
	CListNodeOfCTriangle* newPtr = new CListNodeOfCTriangle(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void CListOfCTriangle::Prepend(const CTriangle& data)
{
	CListNodeOfCTriangle* newPtr = new CListNodeOfCTriangle(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

CTriangle CListOfCTriangle::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

CTriangle CListOfCTriangle::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool CListOfCTriangle::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfCTriangle::Clear()
{
	CListNodeOfCTriangle* curPtr = firstPtr, *tmp;
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

CListNodeOfCTriangle* CListOfCTriangle::NewNode(const CTriangle& P)
{
	CListNodeOfCTriangle* newPtr= new CListNodeOfCTriangle(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
