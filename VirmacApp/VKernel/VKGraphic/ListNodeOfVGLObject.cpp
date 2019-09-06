// ListNodeOfCGLObject.cpp: implementation of the CListNodeOfCGLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "ListNodeOfVGLObject.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ListNodeOfVGLObject::ListNodeOfVGLObject( VGLObject* P) : data(P), nextPtr(0)
{

}

ListNodeOfVGLObject::~ListNodeOfVGLObject()
{
	if(data)
		delete data;
}

VGLObject* ListNodeOfVGLObject::GetData() const
{
	return data;
}

bool ListNodeOfVGLObject::operator==(ListNodeOfVGLObject& rhs)
{
    if(this == &rhs)
		return true;
	return false;
}

bool ListNodeOfVGLObject::operator!=(ListNodeOfVGLObject& rhs)
{
    return !(this == &rhs);
}
