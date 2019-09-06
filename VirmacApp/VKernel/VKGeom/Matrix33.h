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
 *            Matrix33.h
 *
 *  Thu Jun 29 22:28:00 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _MATRIX33_H
#define _MATRIX33_H

#include "VKGeom.h"

#include "Geometry.h"

class Point3D;
class Vector3D;

class VKGEOMSHARED_EXPORT CMatrix33
{
public:
	CMatrix33();
	CMatrix33(double r1[3],double r2[3],double r3[3]);
	~CMatrix33();
	CMatrix33 operator*(const CMatrix33&);
	Vector3D operator*(const Vector3D&);
	CMatrix33 operator*(const double Value);
	void operator*=(const CMatrix33&);
	void operator*=(const double Value);
	CMatrix33 operator/(const double Value);
	void operator/=(const double Value);
	CMatrix33 operator+(const CMatrix33&);
	void operator+=(const CMatrix33&);
	CMatrix33 operator-(const CMatrix33&);
	void operator-=(const CMatrix33&);
	double Determinant();
	void Invert();
	CMatrix33 Inverted() const;
	void Transpose();
	void Value() const;
	bool IsNull() const;
	bool IsDiagonal() const;
	bool IsSymmetrical() const;
	bool IsScalar() const;
	bool IsIdentity() const;
	bool IsEqual(const CMatrix33&) const;
	inline double operator()(int row, int col) const { return Row[row][col]; }
	inline double &operator()(int row, int col) { return Row[row][col]; }
	void SetIdentity();
	void SetRotation(const Vector3D& axis, double ang);
	void SetScale(const Point3D&);
	Point3D GetDiagonal() const;
private:
  double Row[3][3];
  CMatrix33 Adjoint();
};

#endif /* _MATRIX33_H */
