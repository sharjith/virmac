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
 *            ListIteratorOfListOfCTriangle.h
 *
 *  Thu Jun 29 20:41:34 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _LISTITERATOROFLISTOFCTRIANGLE_H
#define _LISTITERATOROFLISTOFCTRIANGLE_H

#include "VKGeom.h"

#include "ListNodeOfTriangle.h"
#include "ListOfTriangle.h"

class VKGEOMSHARED_EXPORT ListIteratorOfListOfTriangle
{
public:
	ListIteratorOfListOfTriangle() {;}
	ListIteratorOfListOfTriangle(ListOfTriangle*);
	virtual ~ListIteratorOfListOfTriangle();
	void SetList(ListOfTriangle*);
	void Init();
	bool More() const;
	void Next();
	Triangle Current() const;
	Triangle ValueAt(const int index);
private:
	ListNodeOfTriangle* curPtr;
	ListOfTriangle* theList;
};

#endif /* _LISTITERATOROFLISTOFCTRIANGLE_H */
