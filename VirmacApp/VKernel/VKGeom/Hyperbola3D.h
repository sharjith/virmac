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
 *            Hyperbola3D.h
 *
 *  Thu Jun 29 22:20:12 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _HYPERBOLA3D_H
#define _HYPERBOLA3D_H

#include "VKGeom.h"

#include "Conic.h"

class VKGEOMSHARED_EXPORT Hyperbola3D : public Conic
{
public:
    Hyperbola3D();
    Hyperbola3D(const AxisSystem&, const double&, const double&);
    virtual ~Hyperbola3D();
	virtual void Reverse();
    Hyperbola3D Reversed() const;
	virtual double Eccentricity() const;
	virtual Point3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
    bool operator == (const Hyperbola3D& L) const;

    void operator = (const Hyperbola3D& L);
	void SetMinorRadius(const double&);
	void SetMajorRadius(const double&);
	double GetMinorRadius() const;
	double GetMajorRadius() const;
    Hyperbola3D GetConjugateBranch1() const;
    Hyperbola3D GetConjugateBranch2() const;
    Hyperbola3D GetOtherBranch() const;
	void SetLocation(const AxisSystem& ax);
	AxisSystem GetLocation() const;
	double FocalLength() const;
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
	double majorRadius;
	double minorRadius;
};

#endif /* _HYPERBOLA3D_H */
