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
 *            BasicSurface.h
 *
 *  Thu Jun 29 22:04:54 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _BASICSURFACE_H
#define _BASICSURFACE_H

#include "VKGeom.h"

#include "Surface.h"

class Point3D;

//Abstract Base Class For Plane, Cylinder, Cone, Sphere and Torus
class VKGEOMSHARED_EXPORT BasicSurface : public Surface
{
public:
    BasicSurface();
    virtual ~BasicSurface();
	inline AxisSystem GetLocation() const { return itsLocation; }
	virtual Point3D PointAtPara(const double uPar, const double vPar) = 0;
	virtual double FirstUParameter() const = 0;
	virtual double LastUParameter() const = 0;
	virtual double FirstVParameter() const = 0;
	virtual double LastVParameter() const = 0;
	virtual bool IsUClosed() const = 0;
	virtual bool IsVClosed() const = 0;
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
	AxisSystem itsLocation;
	double itsFirstUParameter;
	double itsLastUParameter;
	double itsFirstVParameter;
	double itsLastVParameter;
};

#endif /* _BASICSURFACE_H */
