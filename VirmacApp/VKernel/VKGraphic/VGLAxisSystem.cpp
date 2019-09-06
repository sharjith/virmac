// GLAxisSystem.cpp: implementation of the CGLAxisSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLAxisSystem.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLAxisSystem::VGLAxisSystem(const AxisSystem& Ax, const int& length, const int& arrow) : itsAxis(Ax), 
											   itsLength(length), itsArrow(arrow)
{
    glObjType = GLAXIS;
    glObjID = (int)glObjType + VGLObject::GetCount();
    itsRed = 125;
    itsGreen = 125;
    itsBlue = 220;
    ComputeBoundLimits();
}

VGLAxisSystem::~VGLAxisSystem()
{

}

VGLObject* VGLAxisSystem::Copy() const
{
    VGLAxisSystem* O = new VGLAxisSystem(itsAxis, itsLength, itsArrow);
    O->SetColor(itsRed, itsGreen ,itsBlue);
    O->glObjID = glObjID;
    return O;
}

Geometry* VGLAxisSystem::GetGeometry() const
{
    AxisSystem* Ax = new AxisSystem(itsAxis.GetPosition(), itsAxis.GetDirection());
    return Ax;
}

void VGLAxisSystem::DefineDisplay()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    OneAxis zAx(itsAxis.GetPosition(), itsAxis.GetDirection());
    OneAxis xAx(itsAxis.GetPosition(), itsAxis.GetXDirection());
    OneAxis yAx(itsAxis.GetPosition(), itsAxis.GetYDirection());

    glColor3ub(itsRed, itsGreen, itsBlue);
    DrawArrow(xAx);
    DrawArrow(yAx);
    glColor3ub(itsRed, GLubyte((double)itsGreen/(double)1.5), GLubyte((double)itsBlue/(double)1.5));
    DrawArrow(zAx);
}

void VGLAxisSystem::Display(const GLDisplayMode&)
{
    DefineDisplay();
}

void VGLAxisSystem::Hilight(const GLDisplayMode&)
{	
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    DefineDisplay();
}

void VGLAxisSystem::ComputeBoundLimits()
{
    Point3D P = itsAxis.GetPosition();
    Point3D P1 = P, P2 = P, P3 = P;
    OneAxis zAx(itsAxis.GetPosition(), itsAxis.GetDirection());
    OneAxis xAx(itsAxis.GetPosition(), itsAxis.GetXDirection());
    OneAxis yAx(itsAxis.GetPosition(), itsAxis.GetYDirection());
    P1.Translate(xAx, itsLength);
    P2.Translate(yAx, itsLength);
    P3.Translate(zAx, itsLength);
    itsBox.SetLimits(P.GetX(), P1.GetX(), P.GetY(), P2.GetY(), P.GetZ(), P3.GetZ());
}

void VGLAxisSystem::DrawArrow(const OneAxis& theAxis)
{
    Point3D pos = theAxis.GetPosition();
    pos.Translate(theAxis, itsLength-(itsArrow/2));
    AxisSystem CordSys(pos, theAxis.GetDirection());
    int part=20;
    double step, uParam=0, vParam=0;
    step =2*PI/part;
    Vector3D P, P1, P2;
    double R = itsArrow/3;

    vParam = itsArrow*2;

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLE_FAN);

    double c = cos(uParam);
    double s = sin(uParam);
    P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
	    CordSys.GetYDirection()*s)*0+CordSys.GetDirection()*(vParam);

    glVertex3d(P.GetX(),P.GetY(),P.GetZ());

    vParam = 0;
    for(uParam=0; uParam<=2*PI+2; uParam+=step)
    {		


	double c = cos(uParam);
	double s = sin(uParam);
	P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
		CordSys.GetYDirection()*s)*R+CordSys.GetDirection()*(vParam);

	glVertex3d(P.GetX(),P.GetY(),P.GetZ());
    }
    glEnd();

    Point3D O = theAxis.GetPosition();
    Point3D D = O;
    D.Translate(theAxis, itsLength);
    glBegin(GL_LINES);
    glVertex3d(O.GetX(), O.GetY(), O.GetZ());
    glVertex3d(D.GetX(), D.GetY(), D.GetZ());
    glEnd();
}

