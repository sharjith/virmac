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
 *            Geometry2D.h
 *
 *  Thu Jun 29 22:19:13 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GEOMETRY2D_H
#define _GEOMETRY2D_H

#include "VKGeom.h"

enum Geometry2DType { CPOINT2D, CONEAXIS2D, CCURVE2D };

class Point2D;
class Vector2D;
class COneAxis2D;
/*class CLine2D;
class CCircle2D;
class CEllipse2D;
class CHyperbola2D;
class CParabola2D;
class CBezierCurve2D;
class CBSplineCurve2D;*/

class VKGEOMSHARED_EXPORT Geometry2D
{

public:
	Geometry2D();
	virtual ~Geometry2D();
	virtual void Translate(const COneAxis2D&, const double& amt);
	virtual void Translate(double dx, double dy) = 0;
    virtual void Translate(const Vector2D&) = 0;
    virtual void Translate(const Point2D&, const Point2D&) = 0;
    virtual void Rotate(const Point2D&, double) = 0;
    virtual void Scale(const Point2D&, double) = 0;
    virtual void Mirror(const Point2D&) = 0;
	virtual void Mirror(const COneAxis2D&) = 0;
	inline Geometry2DType GeomType() const { return geomType; }
private:
	static int refCount;
protected:
	Geometry2DType geomType;

};

#endif /* _GEOMETRY2D_H */
