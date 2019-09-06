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
 *            GLCamera.h
 *
 *  Thu Jun 29 22:46:35 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/

/**********************************************************************

//Part of this code is taken from "camera" tutorial written by Philipp Crocoll
//Contact: 
//philipp.crocoll@web.de
//www.codecolony.de
 **********************************************************************/

#ifndef _GLCAMERA_H
#define _GLCAMERA_H

#include "vkgraphic.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <MMath.h>

#include <QMatrix4x4>
#include <QQuaternion>

#include <iostream>
using namespace std;

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#define PIdiv180 (PI/180.0)

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3DVector
{
    SF3DVector()
    {
        x = 1.0;
        y = 0.0;
        z = 0.0;
    }

    SF3DVector( GLdouble ix, GLdouble iy, GLdouble iz )
    {
        x = ix;
        y = iy;
        z = iz;
    }

    double x;
    double y;
    double z;
};

struct SF2DVector
{
    double x;
    double y;
};


// CGLCamera

class VKGRAPHICSHARED_EXPORT VGLCamera
{
public:
    typedef	enum tagViewProjection
    {
        TOP_VIEW	= 0,
        BOTTOM_VIEW	= ( TOP_VIEW + 1 ) ,
        FRONT_VIEW	= ( BOTTOM_VIEW + 1 ) ,
        REAR_VIEW	= ( FRONT_VIEW + 1 ) ,
        LEFT_VIEW	= ( REAR_VIEW + 1 ) ,
        RIGHT_VIEW	= ( LEFT_VIEW + 1 ) ,
        NE_ISOMETRIC_VIEW	= ( RIGHT_VIEW + 1 ) ,
        SE_ISOMETRIC_VIEW	= ( NE_ISOMETRIC_VIEW + 1 ) ,
        NW_ISOMETRIC_VIEW	= ( SE_ISOMETRIC_VIEW + 1 ) ,
        SW_ISOMETRIC_VIEW	= ( NW_ISOMETRIC_VIEW + 1 ) ,
        DIMETRIC_VIEW	= ( SW_ISOMETRIC_VIEW + 1 ) ,
        TRIMETRIC_VIEW	= ( DIMETRIC_VIEW + 1 )
    }VIEW_PROJECTION;

    VGLCamera()
    {
        resetAll();
    }

    void resetAll(void);
    void render(void);
    void renderRotations( void);
    void renderFixedZoom( void);
    void rotateX(double iAngle);
    double getRotatedX() const { return RotatedX; }
    void rotateY(double iAngle);
    double getRotatedY() const { return RotatedY; }
    void rotateZ(double iAngle);
    double getRotatedZ() const { return RotatedZ; }
    void move(double iDX, double iDY, double iDZ);
    void moveForward(double iDist);
    void moveUpward(double iDist);
    void moveAcross(double iDist);
    void setZoom(double iFactor);
    double getZoom() const { return ZoomValue; }
    void setView(VIEW_PROJECTION iProj);
    void setPosition(double iX, double iY, double iZ);

    SF3DVector getViewDir()		const { return ViewDir; }
    SF3DVector getRightVector() const { return RightVector; }
    SF3DVector getUpVector()	const { return UpVector; }
    SF3DVector getPosition()	const { return Position; }

    void getRotationAngles(double* oAlpha, double* oBeta, double* oGamma);

    QQuaternion quaternionFromMatrix(QMatrix4x4 m);
    void quatToEuler(const QQuaternion& quat, double *rotx,  double *roty, double *rotz);

private:

    SF3DVector ViewDir;
    SF3DVector RightVector;
    SF3DVector UpVector;
    SF3DVector Position;

    GLdouble RotatedX, RotatedY, RotatedZ, ZoomValue;
    VIEW_PROJECTION m_ViewProj;
};


#endif /* _GLCAMERA_H */
