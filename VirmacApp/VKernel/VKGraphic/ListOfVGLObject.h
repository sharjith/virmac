/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
/***************************************************************************
 *            ListOfCGLObject.h
 *
 *  Thu Jun 29 20:47:35 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _LISTOFCGLOBJECT_H
#define _LISTOFCGLOBJECT_H

#include "vkgraphic.h"

#include "ListNodeOfVGLObject.h"

class VGLObject;
class ListIteratorOfListOfVGLObject;

class VKGRAPHICSHARED_EXPORT ListOfVGLObject
{
	friend class ListIteratorOfListOfVGLObject;
public:
    ListOfVGLObject();
    virtual ~ListOfVGLObject();
	void Append(VGLObject*);
	void Prepend(VGLObject*);
	VGLObject* First() const;
	VGLObject* Last() const;
	ListNodeOfVGLObject* Previous(const VGLObject*);
	VGLObject* Remove(const VGLObject*);
	bool IsEmpty() const;
	void Clear();
private:
	ListNodeOfVGLObject* firstPtr;
	ListNodeOfVGLObject* lastPtr;
private:
	ListNodeOfVGLObject* NewNode(VGLObject*);
};

#endif /* _LISTOFCGLOBJECT_H */
