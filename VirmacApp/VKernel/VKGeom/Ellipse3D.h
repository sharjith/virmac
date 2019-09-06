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
 *            Ellipse3D.h
 *
 *  Thu Jun 29 22:16:02 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _ELLIPSE3D_H
#define _ELLIPSE3D_H

#include "VKGeom.h"

#include "Conic.h"
#include "MMath.h"

class VKGEOMSHARED_EXPORT Ellipse3D : public Conic
{
public:
    Ellipse3D();
    Ellipse3D(const Point3D& cp, const double min, const double maj);
    Ellipse3D(const AxisSystem& Ax, double min, double maj);
    virtual ~Ellipse3D();
	virtual void Reverse();
    Ellipse3D Reversed() const;
	virtual Point3D PointAtPara(const double& para);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const { return 2 * PI; }
	virtual double Eccentricity() const;
	virtual bool IsClosed() const;
    bool operator == (const Ellipse3D& L) const;
    void operator = (const Ellipse3D& L);
	inline void SetMinorRadius(const double& rad) { minorRadius = rad; }
	inline void SetMajorRadius(const double& rad) { majorRadius = rad; }
	inline double GetMinorRadius() const { return minorRadius; }
	inline double GetMajorRadius() const { return majorRadius; }
	inline void SetLocation(const AxisSystem& ax) { itsLocation = ax; }
	inline AxisSystem GetLocation() const { return itsLocation; }
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
private:
	double minorRadius;
	double majorRadius;
};

#endif /* _ELLIPSE3D_H */
