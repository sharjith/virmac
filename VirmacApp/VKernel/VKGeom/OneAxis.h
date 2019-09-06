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
 *            OneAxis.h
 *
 *  Thu Jun 29 22:30:18 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _ONEAXIS_H
#define _ONEAXIS_H

#include "VKGeom.h"

#include "Geometry.h"
#include "Point3D.h"
#include "Vector3D.h"

class Point3D;
class Vector3D;

class VKGEOMSHARED_EXPORT OneAxis : public Geometry  
{
public:
	OneAxis();
	OneAxis(const Point3D& Pos, const Vector3D& Dir);
	~OneAxis();
	void SetPosition(const Point3D& P);
	void SetPosition(double x, double y, double z);
	void SetDirection(const Vector3D& D);
	void SetDirection(double dx, double dy, double dz);
	Point3D GetPosition() const;
	Vector3D GetOrigin() const;
	Vector3D GetDirection() const;
	bool operator == (const OneAxis&) const;
	virtual void Translate(const OneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
	virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
	virtual void Mirror(const OneAxis&);
	virtual void Mirror(const Plane&);
	static OneAxis OX();
	static OneAxis OY();
	static OneAxis OZ();
private:
	Point3D Position;
	Vector3D Origin;
	Vector3D Direction;
};

#endif /* _ONEAXIS_H */
