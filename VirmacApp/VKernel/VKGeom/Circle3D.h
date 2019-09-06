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
 *            Circle3D.h
 *
 *  Thu Jun 29 22:10:19 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _CIRCLE3D_H
#define _CIRCLE3D_H

#include "VKGeom.h"

#include "Conic.h"
#include "AxisSystem.h"
#include "Matrix33.h"
#include "MMath.h"

class Point3D;
class AxisSystem;

class VKGEOMSHARED_EXPORT Circle3D : public Conic
{
    public:
	Circle3D();
	Circle3D(const Point3D&, const double);
	Circle3D(const AxisSystem& ax, const double rad);
	Circle3D(const Point3D&, const Point3D&, const Point3D&);
	Circle3D(const Circle3D& C);
	virtual ~Circle3D();
	virtual void Reverse();
	Circle3D Reversed() const;
	virtual Point3D PointAtPara(const double& para);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const { return 2*PI; }
	inline virtual double Eccentricity() const { return 0.0; }
	virtual bool IsClosed() const;
	bool operator == (const Circle3D& L) const;
	Circle3D operator = (const Circle3D& C);
	inline void SetRadius(const double& r) { itsRadius = r; }
	inline void SetLocation(const AxisSystem& ax) { itsLocation = ax; }
	inline AxisSystem GetLocation() const { return itsLocation; }
	inline double GetRadius() const { return itsRadius; }
	inline Point3D Center() const { return itsLocation.GetPosition(); }
    virtual Curve* Copy() const;
    virtual void Translate(const OneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
    virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
    virtual void Mirror(const OneAxis&);
    virtual void Mirror(const Plane&);
    protected:
	double itsRadius;
};

#endif /* _CIRCLE3D_H */
