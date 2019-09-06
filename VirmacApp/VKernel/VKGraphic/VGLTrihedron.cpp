// GLTrihedron.cpp: implementation of the CGLTrihedron class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLTrihedron.h"
#include "MMath.h"

#include <string>
#include <cstring>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLTrihedron::VGLTrihedron(QGLWidget* view) : mView(view)
{
    glObjType = GLTRIHEDRON;
    coneObj = gluNewQuadric();
    gluQuadricOrientation(coneObj, GLU_OUTSIDE);
    gluQuadricDrawStyle(coneObj,GLU_SILHOUETTE);
    firstTime = true;
    triList = 0;
    InitDisplayLists();
}

VGLTrihedron::VGLTrihedron(QGLWidget* view, GLfloat size) : csSize(size), mView(view)
{
    glObjType = GLTRIHEDRON;
    coneObj = gluNewQuadric();
    gluQuadricOrientation(coneObj, GLU_OUTSIDE);
    gluQuadricDrawStyle(coneObj,GLU_SILHOUETTE);

    ComputeBoundLimits();
    glObjID = static_cast<ulong>(glObjType + VGLObject::GetCount());
    firstTime = true;
    triList = 0;
    InitDisplayLists();
}

VGLTrihedron::~VGLTrihedron()
{
    glDeleteLists(base, 96);
    glDeleteLists(triList, 1);
}

VGLObject* VGLTrihedron::Copy() const
{
    VGLTrihedron* T = new VGLTrihedron(mView, csSize);
    T->glObjID = glObjID;
    return T;
}

void VGLTrihedron::DefineDisplay()
{
    glCallList(triList);
}

void VGLTrihedron::InitDisplayLists()
{
    if(firstTime)
    {
        if(triList)
            glDeleteLists(triList, 1);
        triList = glGenLists(1);
        glNewList(triList, GL_COMPILE);
        firstTime = false;
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        //glDisable(GL_DEPTH_TEST);


        glColor3f(1.0f, 0, 0);
        //X Axis
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.8*csSize*0.5, 0.0f, 0.0f);
        glEnd();
        glPushMatrix();
        glTranslatef(0.8*csSize*0.5, 0.0f, 0.0f);
        glRotatef(90.0f,0.0f,1.0f,0.0f);
        gluCylinder(coneObj,0.027*csSize,0,0.09*csSize,10,10);
        glPopMatrix();


        glColor3f(0, 1.0f, 0);
        //Y Axis
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.8*csSize*0.5, 0.0f);
        glEnd();
        glPushMatrix();
        glTranslatef(0.0f, 0.8*csSize*0.5, 0.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluCylinder(coneObj,0.027*csSize,0,0.09*csSize,10,10);
        glPopMatrix();

        glColor3f(0, 0, 1.0f);
        //Z Axis
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.8*csSize*0.5);
        glEnd();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.8*csSize*0.5);
        gluCylinder(coneObj,0.027*csSize,0,0.09*csSize,10,10);
        glPopMatrix();

        glEndList();
    }
}

void VGLTrihedron::Display(const GLDisplayMode& /*dMode*/)
{
    mView->makeCurrent();
    //Axes' label
    glColor3ub(255, 255, 0);
    mView->renderText(0.5*csSize, 0, 0, "X");
    mView->renderText(0, 0.5*csSize, 0, "Y");
    mView->renderText(0, 0, 0.5*csSize, "Z");

    DefineDisplay();
}

void VGLTrihedron::Hilight(const GLDisplayMode& /*dMode*/)
{
}

void VGLTrihedron::SetSize(GLfloat size)
{
    csSize = size;
    firstTime = true;
    InitDisplayLists();
}


void VGLTrihedron::ComputeBoundLimits()
{
    itsBox.SetLimits(-csSize, csSize, -csSize, csSize, -csSize, csSize);
}
