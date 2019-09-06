// GLPlane.cpp: implementation of the CGLPlane class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLPlane.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLPlane::VGLPlane(const Plane& P, const double& length, const double& width) : itsPlane(P), uSize(length), vSize(width)
{
    glObjType = GLPLANE;
    glObjID = (int)glObjType + VGLObject::GetCount();

    itsMaterial.SetName(PEARL);
    itsShadeRed = 155;
    itsShadeGreen = 155;
    itsShadeBlue = 155;

    itsRed = 225;
    itsGreen = 225;
    itsBlue = 0;

    ComputeBoundLimits();
}

VGLPlane::~VGLPlane()
{
}

VGLObject* VGLPlane::Copy() const
{
    VGLPlane* P = new VGLPlane(itsPlane, uSize, vSize);
    P->SetColor(itsRed, itsGreen, itsBlue);
    P->SetMaterial(GetMaterial());
    P->glObjID = glObjID;
    return P;
}

Geometry* VGLPlane::GetGeometry() const
{
    Vector3D Dir = itsPlane.GetDirection();
    double Const = itsPlane.GetConstant();
    Plane* pln = new Plane(Dir.GetX(), Dir.GetY(), Dir.GetZ(), Const);
    return pln;
}

void VGLPlane::DefineDisplay()
{
    Point3D sP1, sP2, eP1, eP2;
    double uPar = uSize/2;
    double vPar = vSize/2;
    sP1 = itsPlane.PointAtPara(-uPar, -vPar);
    eP1 = itsPlane.PointAtPara(uPar, -vPar);
    sP2 = itsPlane.PointAtPara(-uPar, vPar);
    eP2 = itsPlane.PointAtPara(uPar, vPar);

    Vector3D O(sP1), OX(eP1), OY(sP2);
    Vector3D X(O, OX), Y(O, OY);
    Vector3D N = X^Y;
    N.Normalize();

    if(displayMode == GLWIREFRAME || displayMode == GLHLREMOVED)
    {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(itsRed, itsGreen, itsBlue);
    }

    else if(displayMode == GLSHADED)
    {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };	

	ApplyMaterial();

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);


	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// Enable lighting
	glEnable(GL_LIGHTING);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,128);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glColor3ub(itsShadeRed, itsShadeGreen, itsShadeBlue);
    }

    glBegin(GL_QUADS);
    glNormal3d(N.GetX(), N.GetY(), N.GetZ());
    glVertex3d(sP1.GetX(), sP1.GetY(), sP1.GetZ());
    glVertex3d(eP1.GetX(), eP1.GetY(), eP1.GetZ());
    glVertex3d(eP2.GetX(), eP2.GetY(), eP2.GetZ());
    glVertex3d(sP2.GetX(), sP2.GetY(), sP2.GetZ());
    glEnd();
}

void VGLPlane::Display(const GLDisplayMode& dMode)
{
    displayMode = dMode;
    DefineDisplay();
}

void VGLPlane::Hilight(const GLDisplayMode&)
{
    displayMode = GLWIREFRAME;
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    DefineDisplay();
}

void VGLPlane::SetColor(const GLubyte& red, const GLubyte& green, const GLubyte& blue)
{
    if(displayMode == GLWIREFRAME)
    {
	itsRed = red;
	itsGreen = green;
	itsBlue = blue;
    }
    else
    {
	itsShadeRed = red;
	itsShadeGreen = green;
	itsShadeBlue = blue;
    }
    DefineDisplay();
}


void VGLPlane::GetColor(GLubyte* colVect) const
{
    colVect = new GLubyte[3];
    if(displayMode == GLWIREFRAME)
    {
	colVect[0] = itsRed;
	colVect[1] = itsGreen;
	colVect[2] = itsBlue;
    }
    else
    {
	colVect[0] = itsShadeRed;
	colVect[1] = itsShadeGreen;
	colVect[2] = itsShadeBlue;
    }
}

#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"
void VGLPlane::ComputeBoundLimits()
{
    Point3D sP1, sP2, eP1, eP2;
    double uPar = uSize/2;
    double vPar = vSize/2;
    sP1 = itsPlane.PointAtPara(-uPar, -vPar);
    eP1 = itsPlane.PointAtPara(uPar, -vPar);
    sP2 = itsPlane.PointAtPara(-uPar, vPar);
    eP2 = itsPlane.PointAtPara(uPar, vPar);

    Vector3D O(sP1), OX(eP1), OY(sP2);
    Vector3D X(O, OX), Y(O, OY);
    Vector3D N = X^Y;
    N.Normalize();

    if(displayMode == GLWIREFRAME || displayMode == GLHLREMOVED)
    {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(itsRed, itsGreen, itsBlue);
    }

    else if(displayMode == GLSHADED)
    {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };	

	ApplyMaterial();

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);


	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// Enable lighting
	glEnable(GL_LIGHTING);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,128);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glColor3ub(itsShadeRed, itsShadeGreen, itsShadeBlue);
    }

    glBegin(GL_QUADS);
    glNormal3d(N.GetX(), N.GetY(), N.GetZ());
    glVertex3d(sP1.GetX(), sP1.GetY(), sP1.GetZ());
    glVertex3d(eP1.GetX(), eP1.GetY(), eP1.GetZ());
    glVertex3d(eP2.GetX(), eP2.GetY(), eP2.GetZ());
    glVertex3d(sP2.GetX(), sP2.GetY(), sP2.GetZ());
    glEnd();
}
