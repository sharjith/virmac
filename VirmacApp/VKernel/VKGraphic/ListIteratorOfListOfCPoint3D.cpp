// ListIteratorOfListOfCPoint3D.cpp: implementation of the CListIteratorOfListOfCPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfCPoint3D.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfCPoint3D::CListIteratorOfListOfCPoint3D(CListOfCPoint3D* aList) : theList(aList)
{
}

CListIteratorOfListOfCPoint3D::~CListIteratorOfListOfCPoint3D()
{
}

void CListIteratorOfListOfCPoint3D::SetList(CListOfCPoint3D* aList)
{
	theList = aList;
}

void CListIteratorOfListOfCPoint3D::Init()
{
	curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfCPoint3D::More() const
{
	return (curPtr != 0);
}

void CListIteratorOfListOfCPoint3D::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

CPoint3D CListIteratorOfListOfCPoint3D::Current() const
{
	return (curPtr) ? curPtr->data : CPoint3D();
}

CPoint3D CListIteratorOfListOfCPoint3D::ValueAt(const int index)
{
	int cnt =0;
	Init();
	while(curPtr != 0)
	{
		Next();
		cnt++;
	}
	
	if(cnt < index)
		throw CListException(LIST_BOUND_UPPER);
		
	else if(index<1)
		throw CListException(LIST_BOUND_LOWER);
		
	/*else*/ if(index ==1 )
		return theList->firstPtr->data;
	else
	{
		Init();
		for(int i=1; i < index; i++)
		{
			if(curPtr->nextPtr == 0)
				break;
			Next();
		}
		
		return curPtr->data;
	}
		
}
 
