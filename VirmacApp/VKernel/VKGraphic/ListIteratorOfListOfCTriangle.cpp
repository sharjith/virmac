// ListIteratorOfListOfCTriangle.cpp: implementation of the CListIteratorOfListOfCTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfCTriangle.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfCTriangle::CListIteratorOfListOfCTriangle(CListOfCTriangle* aList) : theList(aList)
{
}

CListIteratorOfListOfCTriangle::~CListIteratorOfListOfCTriangle()
{
}

void CListIteratorOfListOfCTriangle::SetList(CListOfCTriangle* aList)
{
	theList = aList;
}

void CListIteratorOfListOfCTriangle::Init()
{
	curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfCTriangle::More() const
{
	return (curPtr != 0);
}

void CListIteratorOfListOfCTriangle::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

CTriangle CListIteratorOfListOfCTriangle::Current() const
{
	return (curPtr) ? curPtr->data : CTriangle();
}

CTriangle CListIteratorOfListOfCTriangle::ValueAt(const int index)
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
 
