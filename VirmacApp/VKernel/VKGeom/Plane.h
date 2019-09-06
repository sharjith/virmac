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
 *            Plane.h
 *
 *  Thu Jun 29 22:34:03 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/

#ifndef _PLANE_H
#define _PLANE_H

#include "VKGeom.h"

#include "Geometry.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "OneAxis.h"
#include "AxisSystem.h"

class Point3D;
class Vector3D;
class OneAxis;
class AxisSystem;

class VKGEOMSHARED_EXPORT Plane : public Geometry
{
public:
	Plane(){}
	Plane(const Point3D&, const Point3D&, const Point3D&);
	Plane(const Point3D&, const Vector3D&, const Vector3D&);
	Plane(const double&, const double&, const double&, const double&);
	Plane(const OneAxis&);
	virtual ~Plane();
	virtual Point3D PointAtPara(const double uPar, const double vPar);
	Point3D GetPosition() const;
	Vector3D GetDirection() const;
	void EquationAt(const Point3D&, double*);
	double GetConstant() const;
	virtual void Translate(const OneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
	virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
	virtual void Mirror(const OneAxis&);
	virtual void Mirror(const Plane&);
	static Plane XOY();
	static Plane YOZ();
	static Plane ZOX();
private:
	void UpdateEquation();
private:
	double Equation[4];	//Plane Equation
	AxisSystem itsLocation;

};

#endif /* _PLANE_H */
