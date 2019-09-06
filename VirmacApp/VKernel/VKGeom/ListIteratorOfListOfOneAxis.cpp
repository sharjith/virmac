// ListIteratorOfListOfCOneAxis.cpp: implementation of the CListIteratorOfListOfCOneAxis class.
//
//////////////////////////////////////////////////////////////////////


#include "ListIteratorOfListOfOneAxis.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListIteratorOfListOfOneAxis::ListIteratorOfListOfOneAxis(ListOfOneAxis* aList) : theList(aList)
{
}

ListIteratorOfListOfOneAxis::~ListIteratorOfListOfOneAxis()
{
}

void ListIteratorOfListOfOneAxis::SetList(ListOfOneAxis* aList)
{
    theList = aList;
}

void ListIteratorOfListOfOneAxis::Init()
{
    curPtr = theList->firstPtr;
}

bool ListIteratorOfListOfOneAxis::More() const
{
    return (curPtr != 0);
}

void ListIteratorOfListOfOneAxis::Next()
{
    curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

OneAxis ListIteratorOfListOfOneAxis::Current() const
{
    return (curPtr) ? curPtr->data : OneAxis();
}

OneAxis ListIteratorOfListOfOneAxis::ValueAt(const int index)
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

