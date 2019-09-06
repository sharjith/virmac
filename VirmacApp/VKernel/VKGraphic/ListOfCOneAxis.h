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

#include "ListNodeOfCOneAxis.h"

class COneAxis;
class CListIteratorOfListOfCOneAxis;

class CListOfCOneAxis
{
	friend class CListIteratorOfListOfCOneAxis;
public:
	CListOfCOneAxis();
	virtual ~CListOfCOneAxis();
	void Append(const COneAxis& data);
	void Prepend(const COneAxis& data);
	COneAxis First() const;
	COneAxis Last() const;
	bool IsEmpty() const;
	void Clear();
private:
	CListNodeOfCOneAxis* firstPtr;
	CListNodeOfCOneAxis* lastPtr;
private:
	CListNodeOfCOneAxis* NewNode(const COneAxis&);
};

#endif /* _LISTOFCONEAXIS_H */
