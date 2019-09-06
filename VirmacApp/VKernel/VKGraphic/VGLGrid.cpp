// GLGrid.cpp: implementation of the CGLGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLGrid.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLGrid::VGLGrid()
{
    itsPlane = Plane::XOY();
    itsSize = 10000;
    itsStep = 50;
    itsRed = 125;
    itsGreen = 125;
    itsBlue = 125;
    glObjID = 0;
    firstTime = true;
}

VGLGrid::VGLGrid(const Plane& plane, const double& size, const double& step) : itsSize(size),
										itsStep(step),
										itsPlane(plane)
{
    itsRed = 255;
    itsGreen = 125;
    itsBlue = 125;
    glObjID = 0;
    firstTime = true;
}

VGLGrid::~VGLGrid()
{
    glDeleteLists(gridList, 1);
}
VGLObject* VGLGrid::Copy() const
{
    VGLGrid* G = new VGLGrid(itsPlane, itsSize, itsStep);
    return G;
}

void VGLGrid::SetPlane(const Plane& plane)
{ 
    itsPlane = plane; 
    firstTime = true;
}

void VGLGrid::SetSize(const double& size)
{
    itsSize = size;
    firstTime = true;
}

void VGLGrid::SetStep(const double& step)
{
    itsStep = step;
    firstTime = true;
}

void VGLGrid::DefineDisplay()
{
    if(firstTime)
    {
	InitDisplayLists();
	firstTime = false;
    }
    glCallList(gridList);
}

void VGLGrid::InitDisplayLists()
{
    gridList = glGenLists(1);
    glNewList(gridList, GL_COMPILE);
    double size = itsSize;
    double step = itsStep;
    Plane plane = itsPlane;

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glColor3ub(itsRed, itsGreen, itsBlue);

    double i;
    for(i = -size/2; i <= size/2; i += step)
    {
	Point3D P1 = plane.PointAtPara(i, -size/2);
	Point3D P2 = plane.PointAtPara(i, size/2);
	glBegin(GL_LINES);
	glVertex3d(P1.GetX(), P1.GetY(), P1.GetZ());
	glVertex3d(P2.GetX(), P2.GetY(), P2.GetZ());
	glEnd();
    }
    for(i = -size/2; i <= size/2; i += step)
    {
	Point3D P1 = plane.PointAtPara(-size/2, i);
	Point3D P2 = plane.PointAtPara(size/2, i);
	glBegin(GL_LINES);
	glVertex3d(P1.GetX(), P1.GetY(), P1.GetZ());
	glVertex3d(P2.GetX(), P2.GetY(), P2.GetZ());
	glEnd();
    }
    glEndList();
}

void VGLGrid::Display(const GLDisplayMode& /*mode*/)
{
    DefineDisplay();
}

