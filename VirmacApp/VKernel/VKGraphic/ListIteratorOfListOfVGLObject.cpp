// ListIteratorOfListOfCGLObject.cpp: implementation of the CListIteratorOfListOfCGLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "ListIteratorOfListOfVGLObject.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListIteratorOfListOfVGLObject::ListIteratorOfListOfVGLObject(ListOfVGLObject* aList) : theList(aList)
{
}

ListIteratorOfListOfVGLObject::~ListIteratorOfListOfVGLObject()
{
}

void ListIteratorOfListOfVGLObject::SetList(ListOfVGLObject* aList)
{
	theList = aList;
}

void ListIteratorOfListOfVGLObject::Init()
{
	curPtr = theList->firstPtr;
}

bool ListIteratorOfListOfVGLObject::More() const
{
	return (curPtr != 0);
}

bool ListIteratorOfListOfVGLObject::IsFound(const VGLObject* O) const
{
	bool b = false;
	ListIteratorOfListOfVGLObject li(theList);
	for(li.Init(); li.More(); li.Next())
	{
		if(li.Current() == O)
		{
			b = true;
			break;
		}
	}
	return b;
}

void ListIteratorOfListOfVGLObject::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

VGLObject* ListIteratorOfListOfVGLObject::Current() const
{
	return (curPtr) ? curPtr->data : 0;
}

ListNodeOfVGLObject* ListIteratorOfListOfVGLObject::CurrentPtr() const
{
	return curPtr;
}

void ListIteratorOfListOfVGLObject::SetCurrent(VGLObject* Obj)
{
	curPtr->data = Obj;
}

VGLObject* ListIteratorOfListOfVGLObject::ValueAt(const int index)
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
 
