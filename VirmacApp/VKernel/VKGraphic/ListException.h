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
 *            ListException.h
 *
 *  Thu Jun 29 20:27:11 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/

#ifndef _LISTEXCEPTION_H
#define _LISTEXCEPTION_H

enum LIST_ERROR{ LIST_OUT_OF_MEMORY, LIST_BOUND_LOWER, LIST_BOUND_UPPER, LIST_EMPTY, ERROR_UNKNOWN };

class CListException  
{
public:
	CListException(){}
	CListException(LIST_ERROR type);
	virtual ~CListException();
	char* ErrorMessage();
private:
	char* msg;

};

#endif /* _LISTEXCEPTION_H */
