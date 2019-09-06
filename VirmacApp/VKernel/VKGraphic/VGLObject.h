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
 *            GLObject.h
 *
 *  Thu Jun 29 22:56:41 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GLOBJECT_H
#define _GLOBJECT_H

#include "vkgraphic.h"

#include "VGLTypeEnums.h"
#include "VGLMaterial.h"
#include <BoundingBox.h>
#include <Geometry.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef __linux__
//#include <GL/glx.h>
#endif


class VGLCurve;
class CGLFont;
class VGLPlane;
class VGLPoint;
class VGLSurface;
class VGLAxisSystem;
class VGLOneAxis;
class VGLTrihedron;
class VGLGrid;

class VKGRAPHICSHARED_EXPORT VGLObject
{
    public:
    VGLObject();
    virtual ~VGLObject();
    virtual VGLObject* Copy() const = 0;
	virtual void DefineDisplay() = 0;
	virtual void Display(const GLDisplayMode& = GLWIREFRAME) = 0;
	virtual void Hilight(const GLDisplayMode&) = 0;
	int GetCount() const { return glObjCount; }
	unsigned long int GetObjID() const { return glObjID; }
	void SetDisplayMode(const GLDisplayMode& );
	GLDisplayMode GetDisplayMode() const;
	void SetMaterial(const GLMaterialName&);
	void SetMaterial(const VGLMaterial&);
	VGLMaterial GetMaterial() const;
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void SetColor(const VGLColor&);
	virtual void GetColor(GLubyte*) const;
	virtual VGLColor GetColor() const;
	void SetBoundingBox(const BoundingBox&);
	BoundingBox GetBoundingBox() const;
	virtual GLObjectType GLObjType() const;
	bool IsOfType(const GLObjectType&) const;
    virtual Geometry* getGeometry() const { return 0; }
	virtual void MakeHidden(const bool& flag) { m_bHide = flag; }
	virtual bool IsHidden() const { return m_bHide; }
    protected:
	void ApplyMaterial();
    protected:
	GLObjectType glObjType;
	static int glObjCount;
	unsigned long int glObjID;
	GLDisplayMode displayMode;
	VGLMaterial itsMaterial;
	GLfloat  ambiMat[4];
	GLfloat  diffMat[4];
	GLfloat  specMat[4];
	GLfloat  emisMat[4];
	GLfloat  coloMat[4];
	GLfloat shine;
	GLdouble Matl[13];
	GLubyte itsRed;
	GLubyte itsGreen;
	GLubyte itsBlue;
	GLubyte itsShadeRed;
	GLubyte itsShadeGreen;
	GLubyte itsShadeBlue;
	GLubyte itsTransparency;
	GLuint list;
	GLuint listNum;
	BoundingBox itsBox;
	bool m_bHide;
	bool firstTime;
};

//helper function to draw torus... removes 'glut' dependency
extern VKGRAPHICSHARED_EXPORT void drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius);

#endif /* _GLOBJECT_H */
