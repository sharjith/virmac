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
 *            Line2D.h
 *
 *  Thu Jun 29 22:21:37 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _LINE2D_H
#define _LINE2D_H

#include "VKGeom.h"

#include "Curve2D.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "OneAxis2D.h"

class Point2D;
class Vector2D;
class COneAxis2D;

class VKGEOMSHARED_EXPORT Line2D : public Curve2D
{
public:
    Line2D();
    Line2D(const Point2D&, const Point2D&);
    Line2D(const Point2D&, const Vector2D&);
    virtual ~Line2D();
	virtual void Reverse();
    virtual Point2D PointAtPara(const double& par);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const {return 1; }
	virtual bool IsClosed() const;
    bool operator == (const Line2D& L) const;
    void operator = (const Line2D& L);
    Vector2D Direction() const;
	inline COneAxis2D GetLocation() const { return itsLocation; }
    Vector2D NormalThrough(const Point2D&);
    double Distance(const Point2D&);
	inline double SegmentLength() { return startPoint.Distance(endPoint); }
    inline Point2D StartPoint() const { return startPoint; }
    inline Point2D EndPoint() const { return endPoint; }
	virtual Curve2D* Copy() const;
	virtual void Translate(const COneAxis2D&, const double&);
	virtual void Translate(double dx, double dy);
    virtual void Translate(const Vector2D&);
    virtual void Translate(const Point2D&, const Point2D&);
    virtual void Rotate(const Point2D&, double);
    virtual void Scale(const Point2D&, double);
    virtual void Mirror(const Point2D&);
	virtual void Mirror(const COneAxis2D&);
private:
    Point2D startPoint;
    Point2D endPoint;
	COneAxis2D itsLocation;
};

#endif /* _LINE2D_H */
