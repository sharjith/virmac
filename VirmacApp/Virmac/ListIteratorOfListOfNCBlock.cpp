// ListIteratorOfListOfNCBlock.cpp: implementation of the CListIteratorOfListOfNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfNCBlock.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListIteratorOfListOfNCBlock::ListIteratorOfListOfNCBlock(ListOfNCBlock* aList) : theList(aList)
{
}

ListIteratorOfListOfNCBlock::~ListIteratorOfListOfNCBlock()
{
}

void ListIteratorOfListOfNCBlock::SetList(ListOfNCBlock* aList)
{
	theList = aList;
}

void ListIteratorOfListOfNCBlock::Init()
{
	curPtr = theList->firstPtr;
}

bool ListIteratorOfListOfNCBlock::More() const
{
	return (curPtr != 0);
}

void ListIteratorOfListOfNCBlock::Next()
{
	curPtr = (curPtr) ? (curPtr->nextPtr) : 0;
}

NCBlock ListIteratorOfListOfNCBlock::Current() const
{
    return (curPtr != NULL) ? curPtr->data : NCBlock();
}

NCBlock ListIteratorOfListOfNCBlock::ValueAt(const int index)
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

