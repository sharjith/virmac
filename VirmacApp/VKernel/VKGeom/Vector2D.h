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
 *            Vector2D.h
 *
 *  Thu Jun 29 22:44:35 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#include "VKGeom.h"

#include "Geometry2D.h"

class Point2D;
class CMatrix22;
class COneAxis2D;

class VKGEOMSHARED_EXPORT Vector2D : public Geometry2D
{
public:
    Vector2D();
    Vector2D(double x, double y);
    Vector2D(const Point2D&);
    Vector2D(const Vector2D&, const Vector2D&);
    Vector2D(const Point2D&, const Point2D&);
    ~Vector2D();
	inline void SetX(double x){itsX = x;} //Set The X Component Value
	inline void SetY(double y){itsY = y;} //Set The Y Component Value
	inline void SetParam(double x, double y){itsX = x; itsY = y;} //Set The X Y and Z Values
	inline double GetX() const {return itsX;}// Returns The X Component
	inline double GetY() const {return itsY;}// Returns The Y Component
    double Dot(const Vector2D &V1) const;//Calculate Dot Product
    double DotCross(const Vector2D &V1, const Vector2D &V2);//Calculate Scalar Triple Product
    void Cross(const Vector2D &V1);//Calculate Cross Product Of' this' And Other
    Vector2D Crossed(const Vector2D &V1) const;//Return The Cross Product Vector
    void CrossCross(const Vector2D &V1, const Vector2D &V2);//Calculate The Vector Triple Product
    Vector2D CrossCrossed(const Vector2D &V1, const Vector2D &V2);//Return Vector Triple Product
	void Reverse();//Reverse The Direction Of 'this'
    Vector2D Reversed();//Return The Reversed Vector Of 'this'
    Vector2D operator + (const Vector2D &V1);//Return Addition Of 'this' And Other
    void operator += (const Vector2D &V1);//Add Other To 'this'
    Vector2D operator - (const Vector2D &V1);//Return Subtraction Of 'this' And Other
    void operator -= (const Vector2D &V1);//Subtract Other From 'this'
    Vector2D operator * (const double &scalar);//Scalar Multiple With Other Vector
    Vector2D operator * (const CMatrix22& M);//Multiply With Matrix
	void operator *= (const double &scalar);//Multiply 'this' With Other
	void operator *= (const CMatrix22 &M);//Multiply 'this With Matrix
    Vector2D operator / (const double &scalar);//Scalar Division
	void operator /= (const double &scalar);//Divide 'this' By Scalar
    Vector2D operator ^ (const Vector2D &V1);//Return The Cross Product
    void operator ^= (const Vector2D &V1);//Calculate Cross Product Of' this' And Other
	double Magnitude() const;// Calculate 'this' Vector's Magnitude
	double SqrMagnitude() const;// Calculate 'this' Vector's Square Magnitude
    double CrossMagnitude(const Vector2D &V);// Calculate 'this' Vector's Cross Magnitude
    double CrossSqrMagnitude(const Vector2D &V1);// Calculate 'this' Vector's Cross Square Magnitude
	double Modulus();// Return Modulus
    Vector2D Unit();//Return Normalized Vector Of 'this'
    Point2D Point();//Return Component Triplet As Point
    double Angle(const Vector2D&) const;//Angle Bet'n 'this' And Other
    double Angle(const Vector2D&, const Vector2D&) const;//Angle Bet'n 'this' And Other WRT Direction
	bool IsNull() const;//Check For Null Vector
    bool IsParallel(const Vector2D&) const;//Check If Parallel To Other
    bool IsOpposite(const Vector2D&) const;//Check If Opposite Direction To Other
    bool IsNormal(const Vector2D&) const;//Check If Normal To Other
    bool operator == (const Vector2D& V) const;//Check Equality
    operator Point2D();//Convertion Cast To Point;
	void Print() const;//Print Values Of Components
	void Normalize();//Normalize 'this' Vector
	virtual void Translate(const COneAxis2D&, const double&);
	virtual void Translate(double dx, double dy);
    virtual void Translate(const Vector2D&);
    virtual void Translate(const Point2D&, const Point2D&);
    virtual void Rotate(const Point2D&, double);
    virtual void Scale(const Point2D&, double);
    virtual void Mirror(const Point2D&);
	virtual void Mirror(const COneAxis2D&);
    static Vector2D Origin();
private:
	double itsX;
	double itsY;
};

#endif /* _VECTOR2D_H */
