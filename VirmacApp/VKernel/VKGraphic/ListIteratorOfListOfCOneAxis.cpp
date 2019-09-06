// ListIteratorOfListOfCOneAxis.cpp: implementation of the CListIteratorOfListOfCOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfCOneAxis.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfCOneAxis::CListIteratorOfListOfCOneAxis(CListOfCOneAxis* aList) : theList(aList)
{
}

CListIteratorOfListOfCOneAxis::~CListIteratorOfListOfCOneAxis()
{
}

void CListIteratorOfListOfCOneAxis::SetList(CListOfCOneAxis* aList)
{
    theList = aList;
}

void CListIteratorOfListOfCOneAxis::Init()
{
    curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfCOneAxis::More() const
{
    return (curPtr != 0);
}

void CListIteratorOfListOfCOneAxis::Next()
{
    curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

COneAxis CListIteratorOfListOfCOneAxis::Current() const
{
    return (curPtr) ? curPtr->data : COneAxis();
}

COneAxis CListIteratorOfListOfCOneAxis::ValueAt(const int index)
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

