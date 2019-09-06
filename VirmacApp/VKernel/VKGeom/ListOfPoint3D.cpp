// ListOfCPoint3D.cpp: implementation of the CListOfCPoint3D class.
//
//////////////////////////////////////////////////////////////////////


#include "ListOfPoint3D.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListOfPoint3D::ListOfPoint3D() : firstPtr(0), lastPtr(0)
{
    itsCount = 0;
}


ListOfPoint3D::~ListOfPoint3D()
{


	ListNodeOfPoint3D* curPtr = firstPtr, *tmp;
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


void ListOfPoint3D::Append(const Point3D& data)
{
	ListNodeOfPoint3D* newPtr = new ListNodeOfPoint3D(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
	++itsCount;
}


void ListOfPoint3D::Prepend(const Point3D& data)
{
	ListNodeOfPoint3D* newPtr = new ListNodeOfPoint3D(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
	++itsCount;
}

Point3D ListOfPoint3D::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

Point3D ListOfPoint3D::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool ListOfPoint3D::IsEmpty() const
{
	return (firstPtr==0);
}		


void ListOfPoint3D::Clear()
{
	ListNodeOfPoint3D* curPtr = firstPtr, *tmp;
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

ListNodeOfPoint3D* ListOfPoint3D::NewNode(const Point3D& P)
{
	ListNodeOfPoint3D* newPtr= new ListNodeOfPoint3D(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
