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
 *            ExtrudedSurface.h
 *
 *  Thu Jun 29 22:17:00 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _EXTRUDEDSURFACE_H
#define _EXTRUDEDSURFACE_H

#include "VKGeom.h"

#include "SweptSurface.h"
#include "Vector3D.h"

class VKGEOMSHARED_EXPORT ExtrudedSurface : public SweptSurface
{
public:
    ExtrudedSurface(){}
    ExtrudedSurface(const Curve*, const Vector3D&, const double&, const double&);
    virtual ~ExtrudedSurface();
	virtual Point3D PointAtPara(const double uPar, const double vPar);
	virtual double FirstUParameter() const;
	virtual double LastUParameter() const;
	virtual double FirstVParameter() const;
	virtual double LastVParameter() const;
	virtual bool IsUClosed() const;
	virtual bool IsVClosed() const;
	virtual Surface* Copy() const;
    virtual void Translate(const OneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
    virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
    virtual void Mirror(const OneAxis&);
    virtual void Mirror(const Plane&);
private:
	Vector3D itsDirection;
	double startLimit;
	double endLimit;

};

#endif /* _EXTRUDEDSURFACE_H */
