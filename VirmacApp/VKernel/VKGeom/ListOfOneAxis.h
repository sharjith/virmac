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
 *            ListOfCOneAxis.h
 *
 *  Thu Jun 29 20:50:10 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/

#ifndef _LISTOFCONEAXIS_H
#define _LISTOFCONEAXIS_H

#include "VKGeom.h"

#include "ListNodeOfOneAxis.h"

class OneAxis;
class ListIteratorOfListOfOneAxis;

class VKGEOMSHARED_EXPORT ListOfOneAxis
{
	friend class ListIteratorOfListOfOneAxis;
public:
	ListOfOneAxis();
	virtual ~ListOfOneAxis();
	void Append(const OneAxis& data);
	void Prepend(const OneAxis& data);
	OneAxis First() const;
	OneAxis Last() const;
	bool IsEmpty() const;
	void Clear();
private:
	ListNodeOfOneAxis* firstPtr;
	ListNodeOfOneAxis* lastPtr;
private:
	ListNodeOfOneAxis* NewNode(const OneAxis&);
};

#endif /* _LISTOFCONEAXIS_H */
