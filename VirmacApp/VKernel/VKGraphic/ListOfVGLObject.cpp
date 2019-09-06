// ListOfCGLObject.cpp: implementation of the CListOfCGLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfVGLObject.h"
#include "ListIteratorOfListOfVGLObject.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListOfVGLObject::ListOfVGLObject() : firstPtr(0), lastPtr(0)
{
}


ListOfVGLObject::~ListOfVGLObject()
{
	ListNodeOfVGLObject* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data)
			{
				delete tmp->data;
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
	}
}


void ListOfVGLObject::Append( VGLObject* data)
{
	ListNodeOfVGLObject* newPtr = new ListNodeOfVGLObject(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}

}


void ListOfVGLObject::Prepend( VGLObject* data)
{
	ListNodeOfVGLObject* newPtr = new ListNodeOfVGLObject(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

VGLObject* ListOfVGLObject::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

VGLObject* ListOfVGLObject::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}


ListNodeOfVGLObject* ListOfVGLObject::Previous(const VGLObject* O)
{
	ListIteratorOfListOfVGLObject it(this);
	for(it.Init(); it.More(); it.Next())
	{
		if(O == it.CurrentPtr()->nextPtr->data)
			break;
	}
	return it.CurrentPtr();
}

VGLObject* ListOfVGLObject::Remove(const VGLObject* O)
{
	if(IsEmpty())
		return 0;
	VGLObject* rO = 0;
	ListNodeOfVGLObject* tmp = 0;
	if(O == First())
	{
		tmp = firstPtr;
		firstPtr = firstPtr->nextPtr;
		rO = tmp->data;
	}
	else
	{
		ListNodeOfVGLObject* p = Previous(O);
		if(p->nextPtr != NULL)
		{
			tmp = p->nextPtr;
			p->nextPtr = p->nextPtr->nextPtr;
			rO = tmp->data;
		}
	}
	tmp->data = 0;
	delete tmp->data;
	delete tmp;
	return rO;
}

bool ListOfVGLObject::IsEmpty() const
{
	return (firstPtr==0);
}		


void ListOfVGLObject::Clear()
{
	ListNodeOfVGLObject* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data)
			{
				delete tmp->data;
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
		
		firstPtr = lastPtr = 0;
	}
}

ListNodeOfVGLObject* ListOfVGLObject::NewNode(VGLObject* P)
{
	ListNodeOfVGLObject* newPtr= new ListNodeOfVGLObject(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
