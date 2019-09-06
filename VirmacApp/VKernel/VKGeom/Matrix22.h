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
 *            Matrix22.h
 *
 *  Thu Jun 29 22:26:17 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _MATRIX22_H
#define _MATRIX22_H

#include "VKGeom.h"

#include "Geometry2D.h"

class Point2D;
class Vector2D;

class VKGEOMSHARED_EXPORT CMatrix22
{
public:
	CMatrix22();
	CMatrix22(double r1[2],double r2[2]);
	~CMatrix22();
	CMatrix22 operator*(const CMatrix22&);
	Vector2D operator*(const Vector2D&);
	CMatrix22 operator*(const double Value);
	void operator*=(const CMatrix22&);
	void operator*=(const double Value);
	CMatrix22 operator/(const double Value);
	void operator/=(const double Value);
	CMatrix22 operator+(const CMatrix22&);
	void operator+=(const CMatrix22&);
	CMatrix22 operator-(const CMatrix22&);
	void operator-=(const CMatrix22&);
	double Determinant();
	void Invert();
	CMatrix22 Inverted() const;
	void Transpose();
	void Value() const;
	bool IsNull() const;
	bool IsDiagonal() const;
	bool IsSymmetrical() const;
	bool IsScalar() const;
	bool IsIdentity() const;
	bool IsEqual(const CMatrix22&) const;
	inline double operator()(int row, int col) const { return Row[row][col]; }
	inline double &operator()(int row, int col) { return Row[row][col]; }
	void SetIdentity();
	void SetRotation(double ang);
	void SetScale(const Point2D&);
	Point2D GetDiagonal() const;
private:
  double Row[2][2];
  CMatrix22 Adjoint();
};

#endif /* _MATRIX22_H */
