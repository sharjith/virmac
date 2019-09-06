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
 *            Parabola3D.h
 *
 *  Thu Jun 29 22:33:00 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _PARABOLA3D_H
#define _PARABOLA3D_H

#include "VKGeom.h"

#include "Conic.h"

class VKGEOMSHARED_EXPORT Parabola3D : public Conic  
{
public:
	Parabola3D();
	Parabola3D(const AxisSystem& Ax, const double fLen);
	virtual ~Parabola3D();
	virtual void Reverse();
	Parabola3D Reversed() const;
	virtual double Eccentricity() const;
	virtual Point3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	bool operator == (const Parabola3D& L) const;
	void operator = (const Parabola3D& L);
	void SetLocation(const AxisSystem&);
	AxisSystem GetLocation() const;
	void SetFocalLength(const double&);
	double GetFocalLength() const;
	void SetYRange(const double& lower, const double& upper);
	double GetLowerRange() const;
	double GetUpperRange() const;
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
	double focalLength;
	double lowerRange;
	double upperRange;
	bool rangeSet;
};

#endif /* _PARABOLA3D_H */
