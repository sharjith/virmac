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
 *            Torus.h
 *
 *  Thu Jun 29 22:43:04 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _TORUS_H
#define _TORUS_H

#include "VKGeom.h"

#include "BasicSurface.h"
#include "MMath.h"

class VKGEOMSHARED_EXPORT Torus : public BasicSurface  
{
public:
	Torus();
	Torus(const AxisSystem&, const double& maj, const double& min, const double& uStart = 0, const double& uEnd = 2*PI, const double& vStart = 0, const double& vEnd = 2*PI);
	virtual ~Torus();
	inline void SetMinorRadius(const double& rad) { minorRadius = rad; }
	inline void SetMajorRadius(const double& rad) { majorRadius = rad; }
	inline double GetMinorRadius() const { return minorRadius; }
	inline double GetMajorRadius() const { return majorRadius; }
	virtual Point3D PointAtPara(const double uPar, const double vPar);
	virtual Vector3D NormalAt(const double uPar, const double vPar);
	inline virtual double FirstUParameter() const { return itsFirstUParameter; }
	inline virtual double LastUParameter() const  { return itsLastUParameter; }
	inline virtual double FirstVParameter() const { return itsFirstVParameter; }
	inline virtual double LastVParameter() const  { return itsLastVParameter; }
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
	double majorRadius;
	double minorRadius;	
};

#endif /* _TORUS_H */
