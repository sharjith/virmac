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
 *            BSplineCurve.h
 *
 *  Thu Jun 29 22:03:08 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _BSPLINECURVE_H
#define _BSPLINECURVE_H

#include "VKGeom.h"

#include "PCurve.h"
#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"

class VKGEOMSHARED_EXPORT BSplineCurve : public PCurve
{
public:
    BSplineCurve();
    BSplineCurve(ListOfPoint3D*, const int& = 3);
    virtual ~BSplineCurve();
	virtual void Reverse();
	virtual Point3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
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
	ListOfPoint3D *cpList;
	int cpCount;
	int itsDegree;
};

#endif /* _BSPLINECURVE_H */
