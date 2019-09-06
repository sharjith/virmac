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
 *            GLSurface.h
 *
 *  Thu Jun 29 22:59:47 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GLSURFACE_H
#define _GLSURFACE_H

#include "vkgraphic.h"

#include "VGLObject.h"
#include <Geometry.h>
#include <GeomException.h>
#include <Point3D.h>
#include <Vector3D.h>
#include <Line3D.h>
#include <Plane.h>
#include <Cone.h>
#include <Cylinder.h>
#include <Sphere.h>
#include <Torus.h>
#include <ExtrudedSurface.h>
#include <RevolvedSurface.h>
#include <RuledSurface.h>
#include <PipeSurface.h>

#include <ListOfPoint3D.h>
#include <ListIteratorOfListOfPoint3D.h>

class VKGRAPHICSHARED_EXPORT VGLSurface : public VGLObject
{
public:
    VGLSurface(const Surface*);
    virtual ~VGLSurface();
	virtual VGLObject* Copy() const;
	virtual void DefineDisplay();
	virtual void Display(const GLDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GLDisplayMode&);
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void GetColor(GLubyte*) const;
	void SetSurface(const Surface*);
    virtual Geometry* GetGeometry() const;
private:
	void ComputePoints();
	void ComputeWFPoints();
	void ComputeBoundLimits();
	void DrawWired();
	void DrawShaded();
	void DrawEdges();
	void DrawUIso();
	void DrawVIso();
	void ComputeUIso(const double vPar);
	void ComputeVIso(const double uPar);
	void InitDisplayList();
private:
	GLdouble SMOOTH;
	GLdouble CSMOOTH;
	ListOfPoint3D* pointList;
	ListOfPoint3D* pointWFUList;
	ListOfPoint3D* pointWFVList;
	ListOfPoint3D* normalList;
	ListOfPoint3D* bpointList;
    ListIteratorOfListOfPoint3D myListWFUIter;
    ListIteratorOfListOfPoint3D myListWFVIter;
	Surface* pSurf;
	GLubyte isoRed;
	GLubyte isoGreen;
	GLubyte isoBlue;
	GLint factor;			// Stippling factor
	GLushort pattern;	// Stipple pattern
	
	GLint wireList;
	GLint edgeList;
	GLint shadList;
};

#endif /* _GLSURFACE_H */
