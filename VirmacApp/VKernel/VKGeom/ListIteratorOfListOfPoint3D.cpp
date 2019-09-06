// ListIteratorOfListOfCPoint3D.cpp: implementation of the CListIteratorOfListOfCPoint3D class.
//
//////////////////////////////////////////////////////////////////////


#include "ListIteratorOfListOfPoint3D.h"
#include "ListException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListIteratorOfListOfPoint3D::ListIteratorOfListOfPoint3D(ListOfPoint3D* aList) : theList(aList)
{
}

ListIteratorOfListOfPoint3D::~ListIteratorOfListOfPoint3D()
{
}

void ListIteratorOfListOfPoint3D::SetList(ListOfPoint3D* aList)
{
	theList = aList;
}

void ListIteratorOfListOfPoint3D::Init()
{
	curPtr = theList->firstPtr;
}

bool ListIteratorOfListOfPoint3D::More() const
{
	return (curPtr != 0);
}

void ListIteratorOfListOfPoint3D::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

Point3D ListIteratorOfListOfPoint3D::Current() const
{
	return (curPtr) ? curPtr->data : Point3D();
}

Point3D ListIteratorOfListOfPoint3D::ValueAt(const int index)
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
 
