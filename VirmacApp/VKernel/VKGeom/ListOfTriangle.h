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
 *            ListOfCTriangle.h
 *
 *  Thu Jun 29 21:04:38 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _LISTOFCTRIANGLE_H
#define _LISTOFCTRIANGLE_H

#include "VKGeom.h"

#include "ListNodeOfTriangle.h"

class Triangle;
class ListIteratorOfListOfTriangle;

class VKGEOMSHARED_EXPORT ListOfTriangle
{
	friend class ListIteratorOfListOfTriangle;
public:
	ListOfTriangle();
	virtual ~ListOfTriangle();
	void Append(const Triangle& data);
	void Prepend(const Triangle& data);
	Triangle First() const;
	Triangle Last() const;
	bool IsEmpty() const;
	void Clear();
private:
	ListNodeOfTriangle* firstPtr;
	ListNodeOfTriangle* lastPtr;
private:
	ListNodeOfTriangle* NewNode(const Triangle&);
};

#endif /* _LISTOFCTRIANGLE_H */
