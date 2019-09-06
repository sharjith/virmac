// ListIteratorOfListOfCTriFacet.cpp: implementation of the CListIteratorOfListOfCTriFacet class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfCTriFacet.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListIteratorOfListOfTriFacet::ListIteratorOfListOfTriFacet(ListOfTriFacet* aList) : theList(aList)
{
}

ListIteratorOfListOfTriFacet::~ListIteratorOfListOfTriFacet()
{
}

void ListIteratorOfListOfTriFacet::SetList(ListOfTriFacet* aList)
{
	theList = aList;
}

void ListIteratorOfListOfTriFacet::Init()
{
	curPtr = theList->firstPtr;
}

bool ListIteratorOfListOfTriFacet::More() const
{
	return (curPtr != 0);
}

void ListIteratorOfListOfTriFacet::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

TriFacet ListIteratorOfListOfTriFacet::Current() const
{
    return (curPtr) ? curPtr->data : TriFacet();
}

TriFacet ListIteratorOfListOfTriFacet::ValueAt(const int index)
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
 
