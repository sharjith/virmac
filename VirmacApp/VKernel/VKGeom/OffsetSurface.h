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
 *            OffsetSurface.h
 *
 *  Thu Jun 29 22:29:26 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _OFFSETSURFACE_H
#define _OFFSETSURFACE_H

#include "VKGeom.h"

#include "Surface.h"

class VKGEOMSHARED_EXPORT COffsetSurface : public Surface  
{
public:
	COffsetSurface(const Surface& pSurf, const double& Offset, bool Sense = true);
	virtual ~COffsetSurface();
	virtual Point3D PointAtPara(const double uPar, const double vPar);
	virtual Vector3D NormalAt(const double uPar, const double vPar);
	virtual double FirstUParameter() const;
	virtual double LastUParameter() const;
	virtual double FirstVParameter() const;
	virtual double LastVParameter() const;
	virtual bool IsUClosed() const;
	virtual bool IsVClosed() const;
	SurfaceType Type() const;
	bool IsOfType(const SurfaceType&) const;
	virtual Surface* Copy() const;
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
	virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
	virtual void Mirror(const OneAxis&);
	virtual void Mirror(const Plane&);
private:
	Surface* pSurface;
	double itsOffset;
	bool dirSense;
};

#endif /* _OFFSETSURFACE_H */
