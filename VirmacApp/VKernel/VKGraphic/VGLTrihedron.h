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
 *            GLTrihedron.h
 *
 *  Thu Jun 29 23:00:28 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GLTRIHEDRON_H
#define _GLTRIHEDRON_H

#include "vkgraphic.h"

#include "VGLObject.h"
#include <string>
#include <QGLWidget>

class VKGRAPHICSHARED_EXPORT VGLTrihedron : public VGLObject
{
public:
    VGLTrihedron(QGLWidget* view);
    VGLTrihedron(QGLWidget* view, GLfloat size);
    virtual ~VGLTrihedron();
	virtual VGLObject* Copy() const;
	virtual void DefineDisplay();
	virtual void Display(const GLDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GLDisplayMode&);

    void SetSize(GLfloat size);
    GLfloat GetSize() const { return csSize; }
private:
	GLfloat csSize;
	static GLuint list;
	GLUquadricObj* coneObj;
	GLuint base;            // base display list for the font set.
	GLuint triList;

private:
	void ComputeBoundLimits();
	void InitDisplayLists();

private:
    QGLWidget* mView;

};

#endif /* _GLTRIHEDRON_H */
