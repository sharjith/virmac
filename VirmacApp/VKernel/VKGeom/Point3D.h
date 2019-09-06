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
 *            Point3D.h
 *
 *  Thu Jun 29 22:36:31 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _POINT3D_H
#define _POINT3D_H

#include <iostream>
using namespace std;

#include "VKGeom.h"

#include "Geometry.h"

    class Vector3D;
    class OneAxis;
    class CLine3D;
    class Plane;


class VKGEOMSHARED_EXPORT Point3D  : public Geometry
    {
	friend std::istream &operator>>(std::istream& , Point3D&);
	friend std::ostream &operator<<(std::ostream& , Point3D&);
	public:
	Point3D();
	Point3D(double, double, double);
	virtual ~Point3D();
	void SetParam(double, double, double);
	inline void SetX(double x) {itsX=x;}
	inline void SetY(double y) {itsY=y;}
	inline void SetZ(double z) {itsZ=z;}
	inline double GetX() const { return itsX; }
	inline double GetY() const { return itsY; }
	inline double GetZ() const { return itsZ; }
	Point3D operator+(const Point3D&);
	Point3D operator+(const double&);
	Point3D operator-(const Point3D&);
	Point3D operator-(const double&);
	Point3D operator*(const double scale);
	Point3D operator/(const double scale);
	void operator+=(const Point3D&);
	void operator+=(const double&);
	void operator-=(const Point3D&);
	void operator-=(const double&);
	void operator*=(const double scale);
	void operator/=(const double scale);
    Point3D operator = (const Point3D& p);
	double Distance(const Point3D&) const;
	double Distance(const Plane&) const;
	double PolarAngle(const Point3D& P = Point3D::Origin()) const;
	bool operator == (const Point3D& p) const;
	operator Vector3D();
	virtual void Translate(const OneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
	virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
	virtual void Mirror(const OneAxis&);
	virtual void Mirror(const Plane&);
	static Point3D Origin();
	private:
	double itsX;
	double itsY;
	double itsZ;
};

#endif /* _POINT3D_H */
