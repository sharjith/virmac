// GLOneAxis.cpp: implementation of the CGLOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLOneAxis.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLOneAxis::VGLOneAxis(const OneAxis& Ax, const int& length, const int& arrow) : itsAxis(Ax), 
															itsLength(length), itsArrow(arrow)
{
	glObjType = GLONEAXIS;
	glObjID = (int)glObjType + VGLObject::GetCount();
	itsRed = 125;
	itsGreen = 125;
	itsBlue = 220;
	ComputeBoundLimits();
}

VGLOneAxis::~VGLOneAxis()
{

}

VGLObject* VGLOneAxis::Copy() const
{
	VGLOneAxis* O = new VGLOneAxis(itsAxis, itsLength, itsArrow);
	O->SetColor(itsRed, itsGreen ,itsBlue);
	O->glObjID = glObjID;
	return O;
}

Geometry* VGLOneAxis::GetGeometry() const
{
	OneAxis* Ax = new OneAxis(itsAxis.GetPosition(), itsAxis.GetDirection());
	return Ax;

}

void VGLOneAxis::DefineDisplay()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(itsRed, itsGreen, itsBlue);
	DrawArrow(itsAxis);
}

void VGLOneAxis::Display(const GLDisplayMode&)
{
    DefineDisplay();
}

void VGLOneAxis::Hilight(const GLDisplayMode&)
{
	
	itsRed = 0; itsGreen = 255; itsBlue = 255;
	DefineDisplay();
}

void VGLOneAxis::ComputeBoundLimits()
{
	Point3D P1 = itsAxis.GetPosition();
	Point3D P2 = P1;
	P2.Translate(itsAxis, itsLength);
	itsBox.SetLimits(P1.GetX(), P2.GetX(), P1.GetY(), P2.GetY(), P1.GetZ(), P2.GetZ());
}

void VGLOneAxis::DrawArrow(const OneAxis& theAxis)
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
	glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_FAN);

	double c = cos(uParam);
	double s = sin(uParam);
	P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
					CordSys.GetYDirection()*s)*0+CordSys.GetDirection()*(vParam);

	glVertex3f(P.GetX(),P.GetY(),P.GetZ());

	vParam = 0;
	for(uParam=0; uParam<=2*PI+2; uParam+=step)
	{		

		double c = cos(uParam);
		double s = sin(uParam);
		P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
				CordSys.GetYDirection()*s)*R+CordSys.GetDirection()*(vParam);

		glVertex3f(P.GetX(),P.GetY(),P.GetZ());
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
