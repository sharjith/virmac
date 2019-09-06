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
 *            Curve.h
 *
 *  Thu Jun 29 22:13:32 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _CURVE_H
#define _CURVE_H

#include "VKGeom.h"

#include "Geometry.h"

class Point3D;

enum CurveType { BEZIER, BSPLINE, CIRCLE, ELLIPSE, HELIX, HYPERBOLA, LINE, OFFSETCURVE, PARABOLA};

//Abstract Base Class
class VKGEOMSHARED_EXPORT Curve : public Geometry  
{
public:
	Curve();
	virtual ~Curve();
	virtual void Reverse() = 0;
	virtual Point3D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual bool IsClosed() const = 0;
	CurveType Type() const;
	bool IsOfType(const CurveType&) const;
	virtual Curve* Copy() const = 0;
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const Vector3D&) = 0;
	virtual void Translate(const Point3D&, const Point3D&) = 0;
    virtual void Rotate(const OneAxis&, double) = 0;
	virtual void Scale(const Point3D&, double) = 0;
	virtual void Mirror(const Point3D&) = 0;
    virtual void Mirror(const OneAxis&) = 0;
    virtual void Mirror(const Plane&) = 0;
protected:
	CurveType cType;
	bool cReversed;
};

#endif /* _CURVE_H */
