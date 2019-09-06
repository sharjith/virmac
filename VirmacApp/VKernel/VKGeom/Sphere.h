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
 *            Sphere.h
 *
 *  Thu Jun 29 22:39:42 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _SPHERE_H
#define _SPHERE_H

#include "VKGeom.h"

#include "BasicSurface.h"
#include "MMath.h"

class VKGEOMSHARED_EXPORT Sphere : public BasicSurface  
{
    public:
	Sphere();
	Sphere(const AxisSystem&, const double& rad, const double& uStart = 0, const double& uEnd = 2*PI, const double& vStart = -PI/2, const double& vEnd = PI/2);
	virtual ~Sphere();
	inline void SetRadius(const double& r) { itsRadius = r; }
	inline double GetRadius() const { return itsRadius; }
	virtual Point3D PointAtPara(const double uPar, const double vPar);
	virtual Vector3D NormalAt(const double uPar, const double vPar);
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
	double itsRadius;
};

#endif /* _SPHERE_H */
