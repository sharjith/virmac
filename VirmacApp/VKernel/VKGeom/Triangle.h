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
 *            Triangle.h
 *
 *  Thu Jun 29 22:43:46 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "VKGeom.h"

#include "Geometry.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Vector3D.h"

class VKGEOMSHARED_EXPORT Triangle : public Geometry
{
public:
    Triangle();
    Triangle(const Point3D& v1, const Point3D& v2, const Point3D& v3);
    Triangle(const Triangle& other);
    virtual ~Triangle();
    void SetVertex(const int& index, const Point3D& v);
    Point3D GetVertex(const int& index) const;
    Vector3D Normal() const;    
    bool operator == (const Triangle& p) const;
    virtual void Translate(double dx, double dy, double dz);
    virtual void Translate(const Vector3D&);
    virtual void Translate(const Point3D&, const Point3D&);
    virtual void Rotate(const OneAxis&, double);
    virtual void Scale(const Point3D&, double);
    virtual void Mirror(const Point3D&);
    virtual void Mirror(const OneAxis&);
    virtual void Mirror(const Plane&);
private:
    Point3D vArray[3];
};

#endif /* _TRIANGLE_H */
