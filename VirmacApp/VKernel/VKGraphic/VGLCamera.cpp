// GLCamera.cpp: implementation of the VGLCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLCamera.h"

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <math.h>
#include <cmath>

#define SQR(x) (x*x)

#define NULL_VECTOR F3DVector(0.0f,0.0f,0.0f)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SF3DVector F3DVector ( GLdouble x, GLdouble y, GLdouble z )
{
    SF3DVector tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    return tmp;
}

GLdouble getF3DVectorLength( SF3DVector * v)
{
    return (GLdouble)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

SF3DVector Normalize3DVector( SF3DVector v)
{
    SF3DVector res;
    double l = getF3DVectorLength(&v);
    if (l == 0.0f) return NULL_VECTOR;
    res.x = v.x / l;
    res.y = v.y / l;
    res.z = v.z / l;
    return res;
}

SF3DVector operator+ (SF3DVector v, SF3DVector u)
{
    SF3DVector res;
    res.x = v.x+u.x;
    res.y = v.y+u.y;
    res.z = v.z+u.z;
    return res;
}
SF3DVector operator- (SF3DVector v, SF3DVector u)
{
    SF3DVector res;
    res.x = v.x-u.x;
    res.y = v.y-u.y;
    res.z = v.z-u.z;
    return res;
}


SF3DVector operator* (SF3DVector v, double r)
{
    SF3DVector res;
    res.x = v.x*r;
    res.y = v.y*r;
    res.z = v.z*r;
    return res;
}

SF3DVector CrossProduct (SF3DVector * u, SF3DVector * v)
{
    SF3DVector resVector;
    resVector.x = u->y*v->z - u->z*v->y;
    resVector.y = u->z*v->x - u->x*v->z;
    resVector.z = u->x*v->y - u->y*v->x;

    return resVector;
}
double operator* (SF3DVector v, SF3DVector u)	//dot product
{
    return v.x*u.x+v.y*u.y+v.z*u.z;
}

// VGLCamera

void VGLCamera::resetAll( void)
{
    //Init with standard OGL values:
    Position = F3DVector (0.0, 0.0,	0.0);
    ViewDir = F3DVector( 0.0, 0.0, -1.0);
    RightVector = F3DVector (1.0, 0.0, 0.0);
    UpVector = F3DVector (0.0, 1.0, 0.0);

    //Only to be sure:
    RotatedX = RotatedY = RotatedZ = 0.0;
    ZoomValue = 1.0;
}

void VGLCamera::render( void)
{
    //The point at which the camera looks:
    SF3DVector ViewPoint = Position+ViewDir;

    // Camera Zooming
    glScaled(ZoomValue, ZoomValue, ZoomValue);

    //as we know the up vector, we can easily use gluLookAt:
    gluLookAt(	Position.x,Position.y,Position.z,
                ViewPoint.x,ViewPoint.y,ViewPoint.z,
                UpVector.x,UpVector.y,UpVector.z);
}

void VGLCamera::renderRotations( void)
{
    gluLookAt(	0,0,0,
                ViewDir.x,ViewDir.y,ViewDir.z,
                UpVector.x,UpVector.y,UpVector.z);
}

void VGLCamera::renderFixedZoom( void)
{
    //The point at which the camera looks:
    SF3DVector ViewPoint = Position+ViewDir;

    // Disable Camera Zooming
    //glScaled(ZoomValue, ZoomValue, ZoomValue);

    //as we know the up vector, we can easily use gluLookAt:
    gluLookAt(	Position.x,Position.y,Position.z,
                ViewPoint.x,ViewPoint.y,ViewPoint.z,
                UpVector.x,UpVector.y,UpVector.z);
}

void VGLCamera::rotateX(double iAngle)
{
    RotatedX += iAngle;

    if((RotatedX > 360) || (RotatedX < -360))
    {
        RotatedX = 0;
    }

    //Rotate viewdir around the right vector:
    ViewDir = Normalize3DVector(ViewDir*cos(iAngle*PIdiv180)
                                + UpVector*sin(iAngle*PIdiv180));

    //now compute the new UpVector (by cross product)
    UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void VGLCamera::rotateY(double iAngle)
{
    RotatedY += iAngle;

    if((RotatedY > 360) || (RotatedY < -360))
    {
        RotatedY = 0;
    }

    //Rotate viewdir around the up vector:
    ViewDir = Normalize3DVector(ViewDir*cos(iAngle*PIdiv180)
                                - RightVector*sin(iAngle*PIdiv180));

    //now compute the new RightVector (by cross product)
    RightVector = CrossProduct(&ViewDir, &UpVector);
}


void VGLCamera::rotateZ(double iAngle)
{
    RotatedZ += iAngle;

    if((RotatedZ > 360) || (RotatedZ < -360))
    {
        RotatedZ = 0;
    }

    //Rotate viewdir around the right vector:
    RightVector = Normalize3DVector(RightVector*cos(iAngle*PIdiv180)
                                    + UpVector*sin(iAngle*PIdiv180));

    //now compute the new UpVector (by cross product)
    UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void VGLCamera::move(double iDX, double iDY, double iDZ)
{
    SF3DVector Dir;
    Dir.x = iDX;
    Dir.y = iDY;
    Dir.z = iDZ;
    Position = Position + Dir;
}

void VGLCamera::moveForward(double iDist)
{
    Position = Position + (ViewDir* - iDist);
}

void VGLCamera::moveUpward(double iDist)
{
    Position = Position + (UpVector * iDist);
}

void VGLCamera::moveAcross(double iDist)
{
    Position = Position + (RightVector * iDist);
}

void VGLCamera::setZoom(double iFactor)
{
    ZoomValue = iFactor;
}

void VGLCamera::setView(VIEW_PROJECTION iProj)
{
    ViewDir = F3DVector( 0.0, 0.0, -1.0);
    RightVector = F3DVector (1.0, 0.0, 0.0);
    UpVector = F3DVector (0.0, 1.0, 0.0);
    RotatedX = RotatedY = RotatedZ = 0.0;

    m_ViewProj = iProj;
    switch(m_ViewProj)
    {
    case TOP_VIEW:
        ViewDir = F3DVector( 0.0, 0.0, -1.0);
        RightVector = F3DVector (1.0, 0.0, 0.0);
        UpVector = F3DVector (0.0, 1.0, 0.0);
        break;
    case BOTTOM_VIEW:
        ViewDir = F3DVector( 0.0, 0.0, 1.0);
        RightVector = F3DVector (1.0, 0.0, 0.0);
        UpVector = F3DVector (0.0, -1.0, 0.0);
        break;
    case FRONT_VIEW:
        ViewDir = F3DVector( 0.0, 1.0, 0.0);
        RightVector = F3DVector (1.0, 0.0, 0.0);
        UpVector = F3DVector (0.0, 0.0, 1.0);
        break;
    case REAR_VIEW:
        ViewDir = F3DVector( 0.0, -1.0, 0.0);
        RightVector = F3DVector (-1.0, 0.0, 0.0);
        UpVector = F3DVector (0.0, 0.0, 1.0);
        break;
    case LEFT_VIEW:
        ViewDir = F3DVector( -1.0, 0.0, 0.0);
        RightVector = F3DVector (0.0, 1.0, 0.0);
        UpVector = F3DVector (0.0, 0.0, 1.0);
        break;
    case RIGHT_VIEW:
        ViewDir = F3DVector( 1.0, 0.0, 0.0);
        RightVector = F3DVector (0.0, -1.0, 0.0);
        UpVector = F3DVector (0.0, 0.0, 1.0);
        break;
    case DIMETRIC_VIEW:
        ViewDir = F3DVector (-2.0, 2.0, -1);
        RightVector = F3DVector (1, 1, 0);
        UpVector = F3DVector(-1, 1, 0);
        break;
    case TRIMETRIC_VIEW:
        ViewDir = F3DVector (-0.486, 0.732, -0.477);
        RightVector = F3DVector (1.181, 0.778, 0.010);
        UpVector = F3DVector(-0.363, 0.568, 1.243);
        break;
    case NW_ISOMETRIC_VIEW:
        ViewDir = F3DVector (1, -1, -1);
        RightVector = F3DVector (-1, -1, 0);
        UpVector = F3DVector(1, -1, 1);
        break;
    case SW_ISOMETRIC_VIEW:
        ViewDir = F3DVector (1, 1, -1);
        RightVector = F3DVector (1, -1, 0);
        UpVector = F3DVector(1, 1, 0);
        break;
    case NE_ISOMETRIC_VIEW:
        ViewDir = F3DVector (-1, -1, -1);
        RightVector = F3DVector (-1, 1, 0);
        UpVector = F3DVector(-1, -1, 1);
        break;
    case SE_ISOMETRIC_VIEW:
    default:
        ViewDir = F3DVector (-1, 1, -1);
        RightVector = F3DVector (1, 1, 0);
        UpVector = F3DVector(-1, 1, 0);
        break;
    }
    // Update the rotation angles
    double rx, ry, rz;
    getRotationAngles(&rx, &ry, &rz);
    RotatedX = rx;
    RotatedY = ry;
    RotatedZ = rz;
}

void VGLCamera::setPosition(double iX, double iY, double iZ)
{
    Position.x = iX;
    Position.y = iY;
    Position.z = iZ;
}


void VGLCamera::getRotationAngles(double* oAlpha, double* oBeta, double* oGamma)
{
    QMatrix4x4 mvMat;
    mvMat.setToIdentity();

    //The point at which the camera looks:
    SF3DVector ViewPoint = Position+ViewDir;
    mvMat.lookAt(QVector3D(Position.x,Position.y,Position.z),
                 QVector3D(ViewPoint.x,ViewPoint.y,ViewPoint.z),
                 QVector3D(UpVector.x,UpVector.y,UpVector.z));

    QQuaternion quat = quaternionFromMatrix(mvMat);
    quatToEuler(quat, oAlpha, oBeta, oGamma);
}


double sign(double num)
{
    return (num > 0) ? 1 : -1;
}
QQuaternion VGLCamera::quaternionFromMatrix(QMatrix4x4 m)
{
    // Adapted from: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

    QVector4D v;
    v.setW(sqrt( max( 0.0, 1.0 + m(0,0) + m(1,1) + m(2,2) ) ) / 2);
    v.setX(sqrt( max( 0.0, 1.0 + m(0,0) - m(1,1) - m(2,2) ) ) / 2);
    v.setY(sqrt( max( 0.0, 1.0 - m(0,0) + m(1,1) - m(2,2) ) ) / 2);
    v.setZ(sqrt( max( 0.0, 1.0 - m(0,0) - m(1,1) + m(2,2) ) ) / 2);
    v.setX(v.x() * sign( v.x() * ( m(2,1) - m(1,2) ) ));
    v.setY(v.y() * sign( v.y() * ( m(0,2) - m(2,0) ) ));
    v.setZ(v.z() * sign( v.z() * ( m(1,0) - m(0,1) ) ));
    QQuaternion q(v);
    return q;
}

void VGLCamera::quatToEuler(const QQuaternion& quat, double *rotx,  double *roty, double *rotz)
{
    double sqw;
    double sqx;
    double sqy;
    double sqz;

    double rotxrad;
    double rotyrad;
    double rotzrad;

    sqw = quat.scalar() * quat.scalar();
    sqx = quat.x() * quat.x();
    sqy = quat.y() * quat.y();
    sqz = quat.z() * quat.z();

    rotxrad = (double)atan2l(2.0 * ( quat.y() * quat.z() + quat.x() * quat.scalar() ) , ( -sqx - sqy + sqz + sqw ));
    rotyrad = (double)asinl(-2.0 * ( quat.x() * quat.z() - quat.y() * quat.scalar() ));
    rotzrad = (double)atan2l(2.0 * ( quat.x() * quat.y() + quat.z() * quat.scalar() ) , (  sqx - sqy - sqz + sqw ));

    *rotx = rotxrad*180.0/PI;
    *roty = rotyrad*180.0/PI;
    *rotz = rotzrad*180.0/PI;
}
