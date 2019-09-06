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
 *            Curve2D.h
 *
 *  Thu Jun 29 22:14:20 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _CURVE2D_H
#define _CURVE2D_H

#include "VKGeom.h"

#include "Geometry2D.h"

class Point2D;

enum Curve2DType { BEZIER2D, BSPLINE2D, CIRCLE2D, ELLIPSE2D, HYPERBOLA2D, LINE2D, OFFSETCURVE2D, PARABOLA2D };

//Abstract Base Class
class VKGEOMSHARED_EXPORT Curve2D : public Geometry2D
{
public:
    Curve2D();
    virtual ~Curve2D();
	virtual void Reverse() = 0;
    virtual Point2D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual bool IsClosed() const = 0;
	Curve2DType Type() const;
	bool IsOfType(const Curve2DType&) const;
    virtual Curve2D* Copy() const = 0;
	virtual void Translate(double dx, double dy) = 0;
    virtual void Translate(const Vector2D&) = 0;
    virtual void Translate(const Point2D&, const Point2D&) = 0;
    virtual void Rotate(const Point2D&, double) = 0;
    virtual void Scale(const Point2D&, double) = 0;
    virtual void Mirror(const Point2D&) = 0;
	virtual void Mirror(const COneAxis2D&) = 0;
protected:
	Curve2DType cType;
	bool cReversed;
};

#endif /* _CURVE2D_H */
