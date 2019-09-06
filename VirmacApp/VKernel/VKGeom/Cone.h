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
 *            Cone.h
 *
 *  Thu Jun 29 22:11:00 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _CONE_H
#define _CONE_H

#include "VKGeom.h"

#include "BasicSurface.h"
#include "MMath.h"


class VKGEOMSHARED_EXPORT Cone : public BasicSurface
{
    public:
    Cone(){}
    Cone(const Circle3D&, const double& ht);
    Cone(const AxisSystem&, const double& ht, const double& rad_1, const double& rad_2 = 0.0, const double& uStart = 0.0, const double& uEnd = 2.0);
    virtual ~Cone();
	inline void SetBaseRadius(const double& r) { baseRadius = r; }
	inline void SetTopRadius(const double& r) { topRadius = r; }
	inline void SetHeight(const double& h) { itsHeight = h; }
	inline double GetBaseRadius() const { return baseRadius; }
	inline double GetTopRadius() const { return topRadius; }
	inline double GetHeight() const { return itsHeight; }
	virtual Point3D PointAtPara(const double uPar, const double vPar);
	inline virtual double FirstUParameter() const { return itsFirstUParameter; }
	inline virtual double LastUParameter() const { return itsLastUParameter; }
	inline virtual double FirstVParameter() const { return itsFirstVParameter; }
	inline virtual double LastVParameter() const { return itsLastVParameter; }
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
	double itsHeight;
	double baseRadius;
	double topRadius;	
};

#endif /* _CONE_H */
