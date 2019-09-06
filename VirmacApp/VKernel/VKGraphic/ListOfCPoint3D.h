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
 *            ListOfCPoint3D.h
 *
 *  Thu Jun 29 21:01:02 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/

#ifndef _LISTOFCPOINT3D_H
#define _LISTOFCPOINT3D_H

#include "ListNodeOfCPoint3D.h"

class Point3D;
class CListIteratorOfListOfCPoint3D;

class ListOfPoint3D
{
	friend class CListIteratorOfListOfCPoint3D;
public:
	ListOfPoint3D();
	virtual ~ListOfPoint3D();
	void Append(const Point3D& data);
	void Prepend(const Point3D& data);
	Point3D First() const;
	Point3D Last() const;
	bool IsEmpty() const;
	void Clear();
	inline unsigned long Count() const { return itsCount; }
private:
	CListNodeOfCPoint3D* firstPtr;
	CListNodeOfCPoint3D* lastPtr;
	unsigned long itsCount; 
private:
	CListNodeOfCPoint3D* NewNode(const Point3D&);
};

#endif /* _LISTOFCPOINT3D_H */
