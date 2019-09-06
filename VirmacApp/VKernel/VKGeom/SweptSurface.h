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
 *            SweptSurface.h
 *
 *  Thu Jun 29 22:41:59 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _SWEPTSURFACE_H
#define _SWEPTSURFACE_H

#include "VKGeom.h"

#include "Surface.h"
#include "Curve.h"

class Point3D;
class Curve;

//Abstract Base Class For Extruded, Revolved, Ruled and Pipe Surfaces
class VKGEOMSHARED_EXPORT SweptSurface : public Surface  
{
public:
	SweptSurface();
	virtual ~SweptSurface();
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
	Curve* baseCurve; //Acts as: 1) base curve for Extruded Surface
					   //		  2) profile for Revolved Surface
					   //		  3) spine for Pipe Surface
					   //		  4) rails for Ruled Surface
};

#endif /* _SWEPTSURFACE_H */
