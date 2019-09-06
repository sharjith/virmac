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
 *            AxisSystem.h
 *
 *  Thu Jun 29 22:02:15 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _AXISSYSTEM_H
#define _AXISSYSTEM_H

#include "VKGeom.h"

#include "Geometry.h"
#include "Point3D.h"
#include "Vector3D.h"

class Point3D;
class Vector3D;

class VKGEOMSHARED_EXPORT AxisSystem : public Geometry
{
public:
    AxisSystem();
    AxisSystem(const Point3D& Pos, const Vector3D& Dir, const Vector3D& XDir);
    AxisSystem(const Point3D& Pos, const Vector3D& Dir);
    AxisSystem(const AxisSystem&);
    ~AxisSystem();
	void SetPosition(const Point3D& P);
	void SetPosition(double x, double y, double z);
    void SetDirection(const Vector3D& D);
	void SetDirection(double dx, double dy, double dz);
    void SetXDirection(const Vector3D& XD);
	void SetXDirection(double dxx, double dxy, double dxz);
    void SetYDirection(const Vector3D& YD);
	void SetYDirection(double dyx, double dyy, double dyz);
	inline Point3D GetPosition() const { return Position; }
    inline Vector3D GetOrigin() const	{ return Origin; }
    inline Vector3D GetDirection() const	{ return Direction; }
    inline Vector3D GetXDirection() const { return XDirection; }
    inline Vector3D GetYDirection() const { return YDirection; }
    bool operator == (const AxisSystem& C) const;
    virtual void Translate(const OneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
    virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D& P1, const Point3D& P2);
    virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
    virtual void Mirror(const OneAxis&);
    virtual void Mirror(const Plane&);
private:
	Point3D Position;
    Vector3D Origin;
    Vector3D Direction;
    Vector3D XDirection;
    Vector3D YDirection;
};

#endif /* _AXISSYSTEM_H */
