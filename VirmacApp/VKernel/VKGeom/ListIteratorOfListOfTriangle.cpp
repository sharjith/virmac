// ListIteratorOfListOfCTriangle.cpp: implementation of the CListIteratorOfListOfCTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfTriangle.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListIteratorOfListOfTriangle::ListIteratorOfListOfTriangle(ListOfTriangle* aList) : theList(aList)
{
}

ListIteratorOfListOfTriangle::~ListIteratorOfListOfTriangle()
{
}

void ListIteratorOfListOfTriangle::SetList(ListOfTriangle* aList)
{
	theList = aList;
}

void ListIteratorOfListOfTriangle::Init()
{
	curPtr = theList->firstPtr;
}

bool ListIteratorOfListOfTriangle::More() const
{
	return (curPtr != 0);
}

void ListIteratorOfListOfTriangle::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

Triangle ListIteratorOfListOfTriangle::Current() const
{
	return (curPtr) ? curPtr->data : Triangle();
}

Triangle ListIteratorOfListOfTriangle::ValueAt(const int index)
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
 
