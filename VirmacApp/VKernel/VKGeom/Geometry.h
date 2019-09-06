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
 *            Geometry.h
 *
 *  Thu Jun 29 22:18:35 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "VKGeom.h"

enum GeometryType { CPOINT, CPLANE, CPOLYGON, CONEAXIS, CAXISSYSTEM, CCURVE, CSURFACE };

class Point3D;
class Vector3D;
class OneAxis;
class AxisSystem;
class CLine3D;
class Circle3D;
class Ellipse3D;
class Hyperbola3D;
class Parabola3D;
class BezierCurve;
class BSplineCurve;
class Plane;
class Cone;
class Cylinder;
class Sphere;
class Torus;
class ExtrudedSurface;
class RevolvedSurface;
class RuledSurface;
class PipeSurface;

class VKGEOMSHARED_EXPORT Geometry
{

public:
	Geometry();
	virtual ~Geometry();
    virtual void Translate(const OneAxis&, const double& amt);
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const Vector3D&) = 0;
	virtual void Translate(const Point3D&, const Point3D&) = 0;
    virtual void Rotate(const OneAxis&, double) = 0;
	virtual void Scale(const Point3D&, double) = 0;
	virtual void Mirror(const Point3D&) = 0;
    virtual void Mirror(const OneAxis&) = 0;
    virtual void Mirror(const Plane&) = 0;
	inline GeometryType GeomType() const { return geomType; }
private:
	static int refCount;
protected:
	GeometryType geomType;

};

#endif /* _GEOMETRY_H */
