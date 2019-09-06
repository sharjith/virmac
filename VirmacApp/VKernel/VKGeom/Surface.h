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
 *            Surface.h
 *
 *  Thu Jun 29 22:40:38 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _SURFACE_H
#define _SURFACE_H

#include "VKGeom.h"

#include "Geometry.h"
#include "Point3D.h"
#include "AxisSystem.h"

enum SurfaceType { CONE, CYLINDER, EXTRUDED, OFFSET, PIPE, PLANE, REVOLVED, RULED, SPHERE, TORUS };

class Point3D;
class AxisSystem;

//Abstract Base Class For All Surfaces
class VKGEOMSHARED_EXPORT Surface : public Geometry  
{
public:
	Surface();
	virtual ~Surface();
	virtual Point3D PointAtPara(const double uPar, const double vPar) = 0;
	virtual Vector3D NormalAt(const double uPar, const double vPar);
	virtual double FirstUParameter() const = 0;
	virtual double LastUParameter() const = 0;
	virtual double FirstVParameter() const = 0;
	virtual double LastVParameter() const = 0;
	virtual bool IsUClosed() const = 0;
	virtual bool IsVClosed() const = 0;
	SurfaceType Type() const;
	bool IsOfType(const SurfaceType&) const;
	virtual Surface* Copy() const = 0;
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const Vector3D&) = 0;
	virtual void Translate(const Point3D&, const Point3D&) = 0;
	virtual void Rotate(const OneAxis&, double) = 0;
	virtual void Scale(const Point3D&, double) = 0;
	virtual void Mirror(const Point3D&) = 0;
	virtual void Mirror(const OneAxis&) = 0;
	virtual void Mirror(const Plane&) = 0;
protected:
	SurfaceType sType;
};

#endif /* _SURFACE_H */
