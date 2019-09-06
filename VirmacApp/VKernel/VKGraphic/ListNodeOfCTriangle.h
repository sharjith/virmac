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
 *            ListNodeOfCTriangle.h
 *
 *  Thu Jun 29 20:46:39 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _LISTNODEOFCTRIANGLE_H
#define _LISTNODEOFCTRIANGLE_H

#include <Triangle.h>

class CListOfCTriangle;

class CListNodeOfCTriangle  
{
	friend class CListOfCTriangle;
	friend class CListIteratorOfListOfCTriangle;
public:
	CListNodeOfCTriangle(const CTriangle&);
	CTriangle GetData() const;
	virtual ~CListNodeOfCTriangle();
	bool operator==(CListNodeOfCTriangle& rhs);
	bool operator!=(CListNodeOfCTriangle& rhs);
private:
	CTriangle data;
	CListNodeOfCTriangle* nextPtr;

};

#endif /* _LISTNODEOFCTRIANGLE_H */
