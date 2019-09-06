// ListOfCPoint3D.cpp: implementation of the CListOfCPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfCPoint3D.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfCPoint3D::CListOfCPoint3D() : firstPtr(0), lastPtr(0)
{
    itsCount = 0;
}


CListOfCPoint3D::~CListOfCPoint3D()
{


	CListNodeOfCPoint3D* curPtr = firstPtr, *tmp;
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


void CListOfCPoint3D::Append(const CPoint3D& data)
{
	CListNodeOfCPoint3D* newPtr = new CListNodeOfCPoint3D(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
	++itsCount;
}


void CListOfCPoint3D::Prepend(const CPoint3D& data)
{
	CListNodeOfCPoint3D* newPtr = new CListNodeOfCPoint3D(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
	++itsCount;
}

CPoint3D CListOfCPoint3D::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

CPoint3D CListOfCPoint3D::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool CListOfCPoint3D::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfCPoint3D::Clear()
{
	CListNodeOfCPoint3D* curPtr = firstPtr, *tmp;
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
	itsCount = 0;
}

CListNodeOfCPoint3D* CListOfCPoint3D::NewNode(const CPoint3D& P)
{
	CListNodeOfCPoint3D* newPtr= new CListNodeOfCPoint3D(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
