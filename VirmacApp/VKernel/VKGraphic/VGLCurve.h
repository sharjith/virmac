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
 *            GLCurve.h
 *
 *  Thu Jun 29 22:50:24 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GLCURVE_H
#define _GLCURVE_H

#include "vkgraphic.h"

#include "VGLObject.h"

#include <Geometry.h>
#include <GeomException.h>
#include <Point3D.h>
#include <Vector3D.h>
#include <OneAxis.h>
#include <AxisSystem.h>
#include <Line3D.h>
#include <Circle3D.h>
#include <Ellipse3D.h>
#include <Hyperbola3D.h>
#include <Parabola3D.h>
#include <BezierCurve.h>
#include <BSplineCurve.h>

#include <ListOfCPoint3D.h>
#include <ListIteratorOfListOfCPoint3D.h>

class Curve;

class VKGRAPHICSHARED_EXPORT VGLCurve : public VGLObject
{
    public:
    VGLCurve(const Curve*, const GLLineStyle& = LINE_SOLID);
    virtual ~VGLCurve();
    virtual VGLObject* Copy() const;
	virtual void DefineDisplay();
	virtual void Display(const GLDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GLDisplayMode&);
	void SetLineStyle(const GLLineStyle& st) { lineStyle = st; }
	GLLineStyle GetLineStyle() const { return lineStyle; }
	void SetSmooth(const double&);
	void SetCurve(const Curve*);
    virtual Geometry* GetGeometry() const;
    private:
	void ComputePoints();
	void ComputeBoundLimits();

    private:
	GLdouble SMOOTH;
	ListOfPoint3D* pointList;
	Curve* pCurve;
	GLLineStyle lineStyle;
};

#endif /* _GLCURVE_H */
