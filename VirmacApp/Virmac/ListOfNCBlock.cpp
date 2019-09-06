// ListOfNCBlock.cpp: implementation of the CListOfNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfNCBlock.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListOfNCBlock::ListOfNCBlock() : firstPtr(0), lastPtr(0), count(0)
{

}


ListOfNCBlock::~ListOfNCBlock()
{
    ListNodeOfNCBlock* curPtr = firstPtr, *tmp;
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


void ListOfNCBlock::Append(const NCBlock& data)
{
    ListNodeOfNCBlock* newPtr = new ListNodeOfNCBlock(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}

    count++;
}


void ListOfNCBlock::Prepend(const NCBlock& data)
{
    ListNodeOfNCBlock* newPtr = new ListNodeOfNCBlock(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}

    count++;
}

NCBlock ListOfNCBlock::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

NCBlock& ListOfNCBlock::First()
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->data;
}

NCBlock ListOfNCBlock::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

NCBlock& ListOfNCBlock::Last()
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->data;
}

bool ListOfNCBlock::IsEmpty() const
{
	return (firstPtr==0);
}


void ListOfNCBlock::Clear()
{
    ListNodeOfNCBlock* curPtr = firstPtr, *tmp;
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
    count = 0;
}

int ListOfNCBlock::GetCount() const
{
    return count;
}

ListNodeOfNCBlock* ListOfNCBlock::NewNode(const NCBlock& P)
{
    ListNodeOfNCBlock* newPtr= new ListNodeOfNCBlock(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
