// MillCutter.cpp: implementation of the CMillCutter class.
//
//////////////////////////////////////////////////////////////////////

#include "MillCutter.h"
#include <MMath.h>

static GLubyte halftone[] = {
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
    0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MillingCutter::MillingCutter(const MillCutterType& typ,
	const double& HolderDia,
	const double& HolderLen,
	const double& ShankDia,
	const double& ShankLen,
	const double& TaperDiaA,
	const double& TaperDiaB,
	const double& TaperLen,	
	const double& BodyDia,
	const double& BodyLen,
	const double& BallRad,
	const bool& tip
	) : itsType(typ),
	    itsHolderDia(HolderDia),
	    itsHolderLen(HolderLen),
	    itsShankDia(ShankDia),
	    itsShankLen(ShankLen),
	    itsTaperDiaA(TaperDiaA),
	    itsTaperDiaB(TaperDiaB), 
	    itsTaperLen(TaperLen),  
	    itsBodyDia(BodyDia),
	    itsBodyLen(BodyLen),
	    itsBallRad(BallRad),
	    bTip(tip)

{
    ToolObj = gluNewQuadric();
    gluQuadricOrientation(ToolObj, GLU_OUTSIDE);
    glObjType = GLCUTTER;
    glObjID = (int)glObjType + VGLObject::GetCount();
    myTriangleList = new ListOfTriangle;

    itsMaterial.SetName(PLASTIC);

    itsResolution = MODEL_HIGH;

    itsShadeRed = 170;
    itsShadeGreen = 170;
    itsShadeBlue = 255;

    itsRed = 170;
    itsGreen = 170;
    itsBlue = 255;

    m_dOX = m_dOY = m_dOZ = 0;
    displayMode = GLSHADED;

    numTriangles = 0;

    m_dTransX = 0;
    m_dTransY = 0;
    m_dTransZ = 0;

    m_dScaleX = 1;
    m_dScaleY = 1;
    m_dScaleZ = 1;

    m_dRotCX = 0;
    m_dRotCY = 0;
    m_dRotCZ = 0;

    m_dRotRX = 0;
    m_dRotRY = 0;
    m_dRotRZ = 0;

    m_dRotA = 0;
    m_dRotB = 0;
    m_dRotC = 0;

    InitDisplayLists();
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    //cout << NumTriangles() << " Triangles\n";
}

MillingCutter::~MillingCutter()
{
    gluDeleteQuadric(ToolObj);
    glDeleteLists(cutterList, 1);
    if(myTriangleList)
    {
	myTriangleList->Clear();
	delete myTriangleList;
    }
}

VGLObject* MillingCutter::Copy() const
{
    MillingCutter* C = new MillingCutter(itsType, itsHolderDia, itsHolderLen, itsShankDia, itsShankLen, itsTaperDiaA, itsTaperDiaB, itsTaperLen, itsBodyDia, itsBodyLen, itsBallRad, bTip);
    C->SetColor(itsRed, itsGreen, itsBlue);
    C->SetMaterial(GetMaterial());
    C->SetResolution(itsResolution);
    C->m_dTransX = m_dTransX;
    C->m_dTransY = m_dTransY;
    C->m_dTransZ = m_dTransZ;

    C->m_dScaleX = m_dScaleX;
    C->m_dScaleY = m_dScaleY;
    C->m_dScaleZ = m_dScaleZ;

    C->m_dRotCX = m_dRotCX;
    C->m_dRotCY = m_dRotCY;
    C->m_dRotCZ = m_dRotCZ;

    C->m_dRotRX = m_dRotRX;
    C->m_dRotRY = m_dRotRX;
    C->m_dRotRZ = m_dRotRX;

    C->m_dRotA = m_dRotA;
    C->m_dRotB = m_dRotB;
    C->m_dRotC = m_dRotC;

    C->cutterList = cutterList;
    C->MoveTo(Point3D(m_dOX, m_dOY, m_dOZ));
    return C;
}

void MillingCutter::SetCutterType  (const MillCutterType& typ)
{
    itsType = typ;
}

void MillingCutter::SetHolderDia  (const double& val)
{
    itsHolderDia = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetHolderLen  (const double& val)
{
    itsHolderLen = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetShankDia   (const double& val)
{
    itsShankDia = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetShankLen   (const double& val)
{
    itsShankLen = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetTaperDiaA  (const double& val)
{
    itsTaperDiaA = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetTaperDiaB  (const double& val)
{
    itsTaperDiaB = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetTaperLen   (const double& val)
{
    itsTaperLen = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetBodyDia	(const double& val)
{
    itsBodyDia = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetBodyLen	(const double& val)
{
    itsBodyLen = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetBallRad	(const double& val)
{
    itsBallRad = val;
    ComputeBoundLimits();
    BuildCollisionModel(0.02);
    DefineDisplay();
}

void MillingCutter::SetResolution( const ModelResolution& res)
{
    itsResolution = res;
    DefineDisplay();
}

#include "OneAxis.h"
void MillingCutter::MoveTo(const Point3D& P)
{
    Point3D p = P;

    p.Translate(m_dTransX,m_dTransY,m_dTransZ);

    p.Rotate(OneAxis(Point3D(m_dRotCX, m_dRotCY, m_dRotCZ), Vector3D(1,0,0)), m_dRotRX*PI/180.0);
    p.Rotate(OneAxis(Point3D(m_dRotCX, m_dRotCY, m_dRotCZ), Vector3D(0,1,0)), m_dRotRY*PI/180.0);
    p.Rotate(OneAxis(Point3D(m_dRotCX, m_dRotCY, m_dRotCZ), Vector3D(0,0,1)), m_dRotRZ*PI/180.0);

    m_dOX = p.GetX();
    m_dOY = p.GetY();
    m_dOZ = p.GetZ();

    m_dOX *= m_dScaleX;
    m_dOY *= m_dScaleY;
    m_dOZ *= m_dScaleZ;

    DefineDisplay();
}

void MillingCutter::Rotate(double A, double B, double C)
{
    m_dRotA = A;
    m_dRotB = B;
    m_dRotC = C;
}

void MillingCutter::ComputeBoundLimits()
{
    double totlen = itsHolderLen + itsShankLen + itsTaperLen + itsBodyLen + itsBallRad + 120;
    itsBox.SetLimits(-55, 55, -55, 55, 0, totlen);
}

void MillingCutter::SetTranslation(double X, double Y, double Z)
{
    m_dTransX = X;
    m_dTransY = Y;
    m_dTransZ = Z;
    DefineDisplay();
}

void MillingCutter::SetScale(double X, double Y, double Z)
{
    m_dScaleX = X;
    m_dScaleY = Y;
    m_dScaleZ = Z;
    DefineDisplay();
}

void MillingCutter::SetRotation(double CX, double CY, double CZ, double RX, double RY, double RZ)
{
    m_dRotCX = CX;
    m_dRotCY = CY;
    m_dRotCZ = CZ;

    m_dRotRX = RX;
    m_dRotRY = RY;
    m_dRotRZ = RZ;

    DefineDisplay();
}

void MillingCutter::GetTranslation(double& X, double& Y, double& Z)
{
    X = m_dTransX;
    Y = m_dTransY;
    Z = m_dTransZ;
}

void MillingCutter::GetScale(double& X, double& Y, double& Z)
{
    X = m_dScaleX;
    Y = m_dScaleY;
    Z = m_dScaleZ;
}

void MillingCutter::GetRotation(double& CX, double& CY, double& CZ, double& RX, double& RY, double& RZ)
{
    CX = m_dRotCX;
    CY = m_dRotCY;
    CZ = m_dRotCZ;

    RX = m_dRotRX;
    RY = m_dRotRY;
    RZ = m_dRotRZ;
}

bool MillingCutter::operator == (MillingCutter c) const
{
    bool b = (m_dOX == c.m_dOX &&
	    m_dOY == c.m_dOY &&
	    m_dOZ == c.m_dOZ &&
	    itsHolderDia == c.itsHolderDia &&
	    itsHolderLen == c.itsHolderLen &&
	    itsShankDia == c.itsShankDia &&
	    itsShankLen == c.itsShankLen &&
	    itsTaperDiaA == c.itsTaperDiaA &&
	    itsTaperDiaB == c.itsTaperDiaB &&
	    itsTaperLen == c.itsTaperLen &&
	    itsBodyDia == c.itsBodyDia &&
	    itsBodyLen == c.itsBodyLen &&
	    itsBallRad == c.itsBallRad &&
	    bTip == c.bTip &&
	    m_dTransX == c.m_dTransX &&
	    m_dTransY == c.m_dTransY &&
	    m_dTransZ == c.m_dTransZ &&
	    m_dScaleX == c.m_dScaleX &&
	    m_dScaleY == c.m_dScaleY &&
	    m_dScaleZ == c.m_dScaleZ &&
	    m_dRotCX == c.m_dRotCX &&
	    m_dRotCY == c.m_dRotCY &&
	    m_dRotCZ == c.m_dRotCZ &&
	    m_dRotRX == c.m_dRotRX &&
	    m_dRotRY == c.m_dRotRY &&
	    m_dRotRZ == c.m_dRotRZ &&
	    m_dRotA == c.m_dRotA &&
	    m_dRotB == c.m_dRotB &&
	    m_dRotC == c.m_dRotC);
    return b;
}

void MillingCutter::DefineDisplay()
{
    GLfloat bgcol[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, bgcol);
    GLfloat  specref[] =  { 0.250f, 0.250f, 0.250f, 1.0f };
    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_LINE_STIPPLE);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,5);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);

    glColor4ub(itsShadeRed, itsShadeGreen, itsShadeBlue, 255);

    glPushMatrix();

    glTranslatef(m_dOX, m_dOY, m_dOZ);

    glTranslated(m_dTransX,m_dTransY,m_dTransZ);
    glTranslated(m_dRotCX,m_dRotCY,m_dRotCZ);

    glRotated(m_dRotRX,1,0,0);
    glRotated(m_dRotRY,0,1,0);
    glRotated(m_dRotRZ,0,0,1);

    glScaled(m_dScaleX, m_dScaleY, m_dScaleZ);

    glPushMatrix();

    glTranslatef(-m_dRotCX,-m_dRotCY,-m_dRotCZ);

    if(displayMode == GLSHADED)
    {	
	ApplyMaterial();
	DrawShadedTool();
    }	

    else if(displayMode == GLWIREFRAME)
    {
	DrawWiredTool();
    }

    glPopMatrix();
    glPopMatrix();

}

void MillingCutter::Display(const GLDisplayMode& dMode)
{
    displayMode = dMode;
    glDepthFunc(GL_LESS);
    DefineDisplay();
}

void MillingCutter::Hilight(const GLDisplayMode& /*dMode*/)
{
    DrawHilitTool();
}

void MillingCutter::DoRotation()
{
    glRotated(m_dRotC,0,0,1);
    glRotated(m_dRotA,1,0,0);
    glRotated(m_dRotB,0,1,0);
}

void MillingCutter::DrawWiredTool()
{

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    gluQuadricDrawStyle(ToolObj,GLU_FILL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(halftone);
    glCullFace(GL_FRONT);
    DrawTool();
    glCullFace(GL_BACK);
    DrawTool();
    glDisable(GL_POLYGON_STIPPLE);
    glDisable(GL_CULL_FACE);
}

void MillingCutter::DrawShadedTool()
{
    //if(displayMode == GLSHADED) 
    //	glColor4ub(itsShadeRed, itsShadeGreen, itsShadeBlue, 255);
    //else HLR

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
    gluQuadricDrawStyle(ToolObj,GLU_FILL);

    DrawTool();
}

void MillingCutter::DrawHilitTool()
{
    itsRed = 0; itsGreen = 255; itsBlue = 255;

    glColor3ub(itsRed, itsGreen, itsBlue);

    glDisable(GL_LINE_STIPPLE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    gluQuadricDrawStyle(ToolObj,GLU_SILHOUETTE);

    DrawTool();
}

#include <ListIteratorOfListOfTriangle.h>
void MillingCutter::DrawTool()
{
    glPushMatrix();
    DoRotation();
    glCallList(cutterList);
    /* // Test collision model
    CListIteratorOfListOfCTriangle itr(myTriangleList);
    int cnt;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3ub(255, 0, 0);
    for(itr.Init(), cnt=0; itr.More(); itr.Next(),++cnt)
    {
	CTriangle t = itr.Current();
	CVector3D n = t.Normal();
	n.Normalize();
	glBegin(GL_TRIANGLES);
	glVertex3d(t.GetVertex(1).GetX(), t.GetVertex(1).GetY(), t.GetVertex(1).GetZ());
	glVertex3d(t.GetVertex(2).GetX(), t.GetVertex(2).GetY(), t.GetVertex(2).GetZ());
	glVertex3d(t.GetVertex(3).GetX(), t.GetVertex(3).GetY(), t.GetVertex(3).GetZ());
	glNormal3d(n.GetX(), n.GetY(), n.GetZ());
	glEnd();
    }
    */
    glPopMatrix();
}

void MillingCutter::InitDisplayLists()
{
    cutterList = glGenLists(1);
    glNewList(cutterList, GL_COMPILE);
    int slice = (int)itsResolution, stack = 1;
    GLdouble eqn[4] = {0.0,0.0,-1.0,0.0};
    //*******Ball End Tool********
    if(itsType == MILL_BALL_NOSE)
    {
	glPushMatrix();

	//Ball
	glTranslatef(0,0,itsBallRad);
	glClipPlane(GL_CLIP_PLANE0,eqn);
	glEnable(GL_CLIP_PLANE0);
	gluSphere(ToolObj,itsBallRad,slice,slice);
	glDisable(GL_CLIP_PLANE0);

	//Body
	gluCylinder(ToolObj,itsBallRad,itsBallRad,itsBodyLen,slice,stack); 

	//Taper
	glTranslatef(0,0,itsBodyLen);
	gluCylinder(ToolObj,itsTaperDiaA/2,itsTaperDiaB/2,itsTaperLen,slice,stack);

	//Shank
	glTranslatef(0,0,itsTaperLen);
	gluDisk(ToolObj,0,itsShankDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsShankDia/2,itsShankDia/2,itsShankLen,slice,stack);

	//holder
	glTranslatef(0,0,itsShankLen);
	gluDisk(ToolObj,0,itsHolderDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsHolderDia/2,itsHolderDia/2, itsHolderLen,slice,stack);

	//holder step;
	glTranslatef(0,0, itsHolderLen);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj, 50, 50, 20, slice, stack);
	//holder taper
	glTranslatef(0,0, 20);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj,35,15,100,slice,stack);
	glTranslatef(0,0, 100);
	gluDisk(ToolObj,0,15,slice,stack);//Cover Cone Top
	glPopMatrix();
	// End Holder
    }
    //********* Spherical End Tool*********
    else if(itsType == MILL_SPHERICAL)			
    {
	glPushMatrix();

	//Ball
	glTranslatef(0,0,itsBallRad);
	gluSphere(ToolObj,itsBallRad,slice,slice);

	//Body
	//gluCylinder(ToolObj,itsBallRad,itsBallRad,itsBodyLen,slice,stack); 

	//Taper
	glTranslatef(0,0,itsBodyLen-itsBallRad);
	gluCylinder(ToolObj,itsTaperDiaA/2,itsTaperDiaB/2,itsTaperLen,slice,stack);

	//Shank
	glTranslatef(0,0,itsTaperLen);
	gluDisk(ToolObj,0,itsShankDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsShankDia/2,itsShankDia/2,itsShankLen,slice,stack);

	//holder
	glTranslatef(0,0,itsShankLen);
	gluDisk(ToolObj,0,itsHolderDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsHolderDia/2,itsHolderDia/2, itsHolderLen,slice,stack);

	//holder step;
	glTranslatef(0,0, itsHolderLen);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj, 50, 50, 20, slice, stack);

	//holder taper
	glTranslatef(0,0, 20);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj,35,15,100,slice,stack);
	glTranslatef(0,0, 100);
	gluDisk(ToolObj,0,15,slice,stack);//Cover Cone Top
	glPopMatrix();
	// End Holder
    }	
    //*********Toroidal Tool********
    else if(itsType == MILL_TOROIDAL)
    {
	glPushMatrix();

	//Torus
	GLfloat iRad, oRad;
	oRad = ((itsBodyDia-2*itsBallRad)/2);
	iRad = itsBallRad;
	gluDisk(ToolObj,0,oRad,slice,stack);//Cover Bottom
	glTranslatef(0,0,itsBallRad);
	drawTorus(slice, slice, oRad, iRad);

	//Body
	gluCylinder(ToolObj,itsBodyDia/2,itsBodyDia/2,itsBodyLen,slice,stack); 

	//Taper
	glTranslatef(0,0,itsBodyLen);
	gluCylinder(ToolObj,itsTaperDiaA/2,itsTaperDiaB/2,itsTaperLen,slice,stack);

	//Shank
	glTranslatef(0,0,itsTaperLen);
	gluDisk(ToolObj,0,itsShankDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsShankDia/2,itsShankDia/2,itsShankLen,slice,stack);

	//holder
	glTranslatef(0,0,itsShankLen);
	gluDisk(ToolObj,0,itsHolderDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsHolderDia/2,itsHolderDia/2, itsHolderLen,slice,stack);

	//holder step;
	glTranslatef(0,0, itsHolderLen);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj, 50, 50, 20, slice, stack);

	//holder taper
	glTranslatef(0,0, 20);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj,35,15,100,slice,stack);
	glTranslatef(0,0, 100);
	gluDisk(ToolObj,0,15,slice,stack);//Cover Cone Top
	glPopMatrix();
	// End Holder
    }
    //******* Square Nose Tool ********
    else if(itsType == MILL_CYLINDRICAL)
    {
	glPushMatrix();

	//Body
	gluDisk(ToolObj,0,itsBodyDia/2,slice,stack);//Cover Bottom
	gluCylinder(ToolObj,itsBodyDia/2,itsBodyDia/2,itsBodyLen,slice,stack); 

	//Taper
	glTranslatef(0,0,itsBodyLen);
	gluCylinder(ToolObj,itsTaperDiaA/2,itsTaperDiaB/2,itsTaperLen,slice,stack);

	//Shank
	glTranslatef(0,0,itsTaperLen);
	gluDisk(ToolObj,0,itsShankDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsShankDia/2,itsShankDia/2,itsShankLen,slice,stack);

	//holder
	glTranslatef(0,0,itsShankLen);
	gluDisk(ToolObj,0,itsHolderDia/2,slice,stack);//Cover Top
	gluCylinder(ToolObj,itsHolderDia/2,itsHolderDia/2, itsHolderLen,slice,stack);

	//holder step;
	glTranslatef(0,0, itsHolderLen);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj, 50, 50, 20, slice, stack);

	//holder taper
	glTranslatef(0,0, 20);
	gluDisk(ToolObj,0,50,slice,stack);//Cover Top
	gluCylinder(ToolObj,35,15,100,slice,stack);
	glTranslatef(0,0, 100);
	gluDisk(ToolObj,0,15,slice,stack);//Cover Cone Top
	glPopMatrix();
	// End Holder
    }    
    glEndList();
}

double chordalAngle(const double& radius, const double& chordalError)
{
    double theta = acos((radius-chordalError)/radius);
    return theta*2.0;
}

/*
#include <AxisSystem.h>
#include <Sphere.h>
#include <Cylinder.h>
#include <Cone.h>
#include <Torus.h>
*/
void MillingCutter::BuildCollisionModel(const double& /*chordalError*/)
{/*
    if(myTriangleList && (!myTriangleList->IsEmpty()))
	myTriangleList->Clear();
    // ********* Ball End Tool*********
    if(itsType == MILL_BALL_NOSE)
    {
	//Ball
	CAxisSystem ax(CPoint3D(0,0,itsBallRad), CVector3D(0,0,1));
	CSphere ball(ax, itsBallRad, 0, 2*PI, -PI/2, 0);
	double ang = chordalAngle(itsBallRad, chordalError);
	double uParts = (2*PI)/ang;
	double vParts = (PI/2)/ang;
	AddSurfaceTriangles(&ball, uParts, vParts);
	
	//Body 
	CCylinder body(ax, itsBodyLen, itsBallRad);
	AddSurfaceTriangles(&body, uParts, 1);

	//Taper
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen), CVector3D(0,0,1));
	CCone taper(ax,itsTaperLen,itsTaperDiaA/2,itsTaperDiaB/2);
	ang = chordalAngle((itsTaperDiaA>itsTaperDiaB)?itsTaperDiaA/2:itsTaperDiaB/2, chordalError);
	uParts = (2*PI)/ang;
	AddSurfaceTriangles(&taper, uParts, 1);

	//Shank
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen+itsTaperLen), CVector3D(0,0,1));
	ang = chordalAngle(itsShankDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder shank(ax, itsShankLen, itsShankDia/2);
	AddSurfaceTriangles(&shank, uParts, 1);

	//holder
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen+itsTaperLen+itsShankLen), CVector3D(0,0,1));
	ang = chordalAngle(itsHolderDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder holder(ax, itsHolderLen, itsHolderDia/2);
	AddSurfaceTriangles(&holder, uParts, 1);

	//holder step;
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen+itsTaperLen+itsShankLen+itsHolderLen), CVector3D(0,0,1));
	ang = chordalAngle(50, chordalError);
	uParts = (2*PI)/ang;
	CCylinder hstep(ax, 20, 50);
	AddSurfaceTriangles(&hstep, uParts, 1);
    }
    // ********* Spherical End Tool*********
    else if(itsType == MILL_SPHERICAL)			
    {
	//Ball
	CAxisSystem ax(CPoint3D(0,0,itsBallRad), CVector3D(0,0,1));
	CSphere ball(ax, itsBallRad);
	double ang = chordalAngle(itsBallRad, chordalError);
	double uParts = (2*PI)/ang;
	double vParts = (PI/2)/ang;
	AddSurfaceTriangles(&ball, uParts, vParts);
	
	//Body
	//Taper
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen), CVector3D(0,0,1));
	CCone taper(ax,itsTaperLen,itsTaperDiaA/2,itsTaperDiaB/2);
	ang = chordalAngle((itsTaperDiaA>itsTaperDiaB)?itsTaperDiaA/2:itsTaperDiaB/2, chordalError);
	uParts = (2*PI)/ang;
	AddSurfaceTriangles(&taper, uParts, 1);

	//Shank
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen+itsTaperLen), CVector3D(0,0,1));
	ang = chordalAngle(itsShankDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder shank(ax, itsShankLen, itsShankDia/2);
	AddSurfaceTriangles(&shank, uParts, 1);

	//holder
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen+itsTaperLen+itsShankLen), CVector3D(0,0,1));
	ang = chordalAngle(itsHolderDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder holder(ax, itsHolderLen, itsHolderDia/2);
	AddSurfaceTriangles(&holder, uParts, 1);

	//holder step;
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen+itsTaperLen+itsShankLen+itsHolderLen), CVector3D(0,0,1));
	ang = chordalAngle(50, chordalError);
	uParts = (2*PI)/ang;
	CCylinder hstep(ax, 20, 50);
	AddSurfaceTriangles(&hstep, uParts, 1);
	
	// End Holder
    }	
    // *********Toroidal Tool********
    else if(itsType == MILL_TOROIDAL)
    {
	//Torus
	GLfloat iRad, oRad;
	oRad = ((itsBodyDia-2*itsBallRad)/2);
	iRad = itsBallRad;
	CAxisSystem ax(CPoint3D(0,0,itsBallRad), CVector3D(0,0,1));
	CTorus toroid(ax, oRad, iRad);
	double ang = chordalAngle(oRad, chordalError);
	double uParts = (2*PI)/ang;
	ang = chordalAngle(iRad, chordalError);
	double vParts = (2*PI)/ang;
	AddSurfaceTriangles(&toroid, uParts, vParts);	
	
	//Body
	ang = chordalAngle(oRad, chordalError);
	uParts = (2*PI)/ang;
	CCylinder body(ax, itsBodyLen, itsBodyDia/2);
	AddSurfaceTriangles(&body, uParts, 1);

	//Taper
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen), CVector3D(0,0,1));
	CCone taper(ax,itsTaperLen,itsTaperDiaA/2,itsTaperDiaB/2);
	ang = chordalAngle((itsTaperDiaA>itsTaperDiaB)?itsTaperDiaA/2:itsTaperDiaB/2, chordalError);
	uParts = (2*PI)/ang;
	AddSurfaceTriangles(&taper, uParts, 1);
	
	//Shank
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen+itsTaperLen), CVector3D(0,0,1));
	ang = chordalAngle(itsShankDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder shank(ax, itsShankLen, itsShankDia/2);
	AddSurfaceTriangles(&shank, uParts, 1);

	//holder
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen+itsTaperLen+itsShankLen), CVector3D(0,0,1));
	ang = chordalAngle(itsHolderDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder holder(ax, itsHolderLen, itsHolderDia/2);
	AddSurfaceTriangles(&holder, uParts, 1);

	//holder step;
	ax = CAxisSystem(CPoint3D(0,0,itsBallRad+itsBodyLen+itsTaperLen+itsShankLen+itsHolderLen), CVector3D(0,0,1));
	ang = chordalAngle(50, chordalError);
	uParts = (2*PI)/ang;
	CCylinder hstep(ax, 20, 50);
	AddSurfaceTriangles(&hstep, uParts, 1);
	// End Holder
    }
    // ******* Square Nose Tool ********
    else if(itsType == MILL_CYLINDRICAL)
    {
	//Body 
	CAxisSystem ax(CPoint3D(0,0,0), CVector3D(0,0,1));
	double ang = chordalAngle(itsBodyDia/2, chordalError);
	double uParts = (2*PI)/ang;
	CCylinder body(ax, itsBodyLen, itsBodyDia/2);
	AddSurfaceTriangles(&body, uParts, 1);

	//Taper
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen), CVector3D(0,0,1));
	CCone taper(ax,itsTaperLen,itsTaperDiaA/2,itsTaperDiaB/2);
	ang = chordalAngle((itsTaperDiaA>itsTaperDiaB)?itsTaperDiaA/2:itsTaperDiaB/2, chordalError);
	uParts = (2*PI)/ang;
	AddSurfaceTriangles(&taper, uParts, 1);

	//Shank
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen+itsTaperLen), CVector3D(0,0,1));
	ang = chordalAngle(itsShankDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder shank(ax, itsShankLen, itsShankDia/2);
	AddSurfaceTriangles(&shank, uParts, 1);

	//holder
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen+itsTaperLen+itsShankLen), CVector3D(0,0,1));
	ang = chordalAngle(itsHolderDia/2, chordalError);
	uParts = (2*PI)/ang;
	CCylinder holder(ax, itsHolderLen, itsHolderDia/2);
	AddSurfaceTriangles(&holder, uParts, 1);

	//holder step;
	ax = CAxisSystem(CPoint3D(0,0,itsBodyLen+itsTaperLen+itsShankLen+itsHolderLen), CVector3D(0,0,1));
	ang = chordalAngle(50, chordalError);
	uParts = (2*PI)/ang;
	CCylinder hstep(ax, 20, 50);
	AddSurfaceTriangles(&hstep, uParts, 1);
	
	// End Holder
    }
	*/
}

void MillingCutter::AddSurfaceTriangles(Surface* pSurf, const double& uParts, const double& vParts)
{
    Point3D curP1;
    double istep, jstep;
    double fUPar, lUPar, fVPar, lVPar;
    double i, j;

    fUPar = pSurf->FirstUParameter();
    lUPar = pSurf->LastUParameter();
    fVPar = pSurf->FirstVParameter();
    lVPar = pSurf->LastVParameter();

    istep = fabs(lUPar-fUPar)/uParts;
    jstep = fabs(lVPar-fVPar)/vParts;	

    Point3D P1, P2, P3, P4;

    for(j = fVPar; j < lVPar; j += jstep)
    {
	for(i = fUPar; i < lUPar; i += istep)
	{
	    P1 = pSurf->PointAtPara(i, j);
	    P2 = pSurf->PointAtPara(i, j+jstep);
	    P3 = pSurf->PointAtPara(i+istep, j+jstep);
	    P4 = pSurf->PointAtPara(i+istep, j);
	    Triangle T1(P2, P1, P3);
	    myTriangleList->Append(T1); ++numTriangles;
	    Triangle T2(P1, P3, P4);
	    myTriangleList->Append(T2); ++numTriangles;
	}		
    }
}

void MillingCutter::RebuildDisplayLists()
{
    glDeleteLists(cutterList, 1);
    InitDisplayLists();
}

void MillingCutter::SetColor(const GLubyte& red, const GLubyte& green, const GLubyte& blue)
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

