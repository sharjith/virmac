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
 *            Point2D.h
 *
 *  Thu Jun 29 22:35:47 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _POINT2D_H
#define _POINT2D_H


#include <iostream>
using namespace std;

#include "VKGeom.h"

#include "Geometry2D.h"


class Vector2D;
class COneAxis2D;

enum ORIENTATION 
{ 
	ORIENTED_CCW, 
	ORIENTED_CW, 
	ORIENTED_COLLINEAR 
};

enum CLASSIFICATION
{
	CLASSIFIED_LEFT,
	CLASSIFIED_RIGHT,
	CLASSIFIED_BEHIND,
	CLASSIFIED_BEYOND,
	CLASSIFIED_BETWEEN,
	CLASSIFIED_ORIGIN,
	CLASSIFIED_DESTINATION
};

class VKGEOMSHARED_EXPORT Point2D  : public Geometry2D
{
    friend std::istream &operator>>(std::istream& , Point2D&);
    friend std::ostream &operator<<(std::ostream& , Point2D&);
    public:
    Point2D();
    Point2D(double, double);
    virtual ~Point2D();
    void SetParam(double, double);
    inline void SetX(double x) {itsX=x;}
    inline void SetY(double y) {itsY=y;}
    inline double GetX() const { return itsX; }
    inline double GetY() const { return itsY; }
    Point2D operator+(const Point2D&);
    Point2D operator+(const double&);
    Point2D operator-(const Point2D&);
    Point2D operator-(const double&);
    Point2D operator*(const double scale);
    Point2D operator/(const double scale);
    void operator+=(const Point2D&);
    void operator+=(const double&);
    void operator-=(const Point2D&);
    void operator-=(const double&);
    void operator*=(const double scale);
    void operator/=(const double scale);
    Point2D operator = (const Point2D& p);    
    double Distance(const Point2D&);
    
    double PolarAngle(const Point2D& P = Point2D::Origin()) const;
    bool operator == (const Point2D& p) const;
    ORIENTATION Orientation(const Point2D& P1, const Point2D& P2);
    CLASSIFICATION Classification(const Point2D& P1, const Point2D& P2);
    operator Vector2D();
    virtual void Translate(const COneAxis2D&, const double&);
    virtual void Translate(double dx, double dy);
    virtual void Translate(const Vector2D&);
    virtual void Translate(const Point2D&, const Point2D&);
    virtual void Rotate(const Point2D&, double);
    virtual void Scale(const Point2D&, double);
    virtual void Mirror(const Point2D&);
    virtual void Mirror(const COneAxis2D&);
    static Point2D Origin();
    private:
    double itsX;
    double itsY;
};

#endif /* _POINT2D_H */
