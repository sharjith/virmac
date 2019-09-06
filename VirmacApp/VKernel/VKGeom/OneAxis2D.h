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
 *            OneAxis2D.h
 *
 *  Thu Jun 29 22:31:25 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _ONEAXIS2D_H
#define _ONEAXIS2D_H

#include "VKGeom.h"

#include "Geometry2D.h"
#include "Point2D.h"
#include "Vector2D.h"

class Point2D;
class Vector2D;

class VKGEOMSHARED_EXPORT COneAxis2D : public Geometry2D
{
public:
	COneAxis2D();
	COneAxis2D(const Point2D& Pos, const Vector2D& Dir);
	~COneAxis2D();
	void SetPosition(const Point2D& P);
	void SetPosition(double x, double y);
	void SetDirection(const Vector2D& D);
	void SetDirection(double dx, double dy);
	Point2D GetPosition() const;
	Vector2D GetOrigin() const;
	Vector2D GetDirection() const;
	bool operator == (const COneAxis2D&) const;
	virtual void Translate(const COneAxis2D&, const double&);
	virtual void Translate(double dx, double dy);
	virtual void Translate(const Vector2D&);
	virtual void Translate(const Point2D&, const Point2D&);
	virtual void Rotate(const Point2D&, double);
	virtual void Scale(const Point2D&, double);
	virtual void Mirror(const Point2D&);
	virtual void Mirror(const COneAxis2D&);
	static COneAxis2D OX();
	static COneAxis2D OY();
private:
	Point2D Position;
	Vector2D Origin;
	Vector2D Direction;
};

#endif /* _ONEAXIS2D_H */
