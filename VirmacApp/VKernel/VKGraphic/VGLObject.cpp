// GLObject.cpp: implementation of the CGLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int VGLObject::glObjCount = 0;

VGLObject::VGLObject()
{
    displayMode = GLWIREFRAME;

    //matl
    itsMaterial = VGLMaterial(ALUMINIUM);
    ambiMat[0] = itsMaterial.GetAmbient().GetRed();
    ambiMat[1] = itsMaterial.GetAmbient().GetGreen();
    ambiMat[2] = itsMaterial.GetAmbient().GetBlue();
    ambiMat[3] = itsMaterial.GetAmbientCoeff();

    diffMat[0] = itsMaterial.GetDiffuse().GetRed();
    diffMat[1] = itsMaterial.GetDiffuse().GetGreen();
    diffMat[2] = itsMaterial.GetDiffuse().GetBlue();
    diffMat[3] = itsMaterial.GetDiffuseCoeff();

    specMat[0] = itsMaterial.GetSpecular().GetRed();
    specMat[1] = itsMaterial.GetSpecular().GetGreen();
    specMat[2] = itsMaterial.GetSpecular().GetBlue();
    specMat[3] = itsMaterial.GetSpecularCoeff();

    emisMat[0] = 0.0f;
    emisMat[1] = 0.0f;
    emisMat[2] = 0.0f;
    emisMat[3] = 0.0f;

    coloMat[0] = ambiMat[0]*1.2;
    coloMat[1] = ambiMat[1]*1.2;
    coloMat[2] = ambiMat[2]*1.2;
    coloMat[3] = ambiMat[3]*1.2;

    shine = itsMaterial.GetShininessCoeff();
    //end matl
    
    itsRed = 205;
    itsGreen = 205;
    itsBlue = 25;
    itsTransparency = 255;
    itsBox.SetLimits(-1, 1, -1, 1, -1, 1);
    glObjCount++;
    MakeHidden(false);
    firstTime = true;
}

VGLObject::~VGLObject()
{
    glObjCount--;
}

GLObjectType VGLObject::GLObjType() const
{
    return glObjType;
}

bool VGLObject::IsOfType(const GLObjectType& type) const
{
    GLObjectType typ = type;
    bool b = (glObjType == typ);
    return b;
}

void VGLObject::SetDisplayMode(const GLDisplayMode& mode)
{
    displayMode = mode;
    DefineDisplay();
}

GLDisplayMode VGLObject::GetDisplayMode() const
{
    return displayMode;
}

void VGLObject::SetMaterial(const GLMaterialName& matName)
{
    SetMaterial(VGLMaterial(matName));
}

void VGLObject::SetMaterial(const VGLMaterial& mat)
{
    itsMaterial = mat;
    ambiMat[0] = itsMaterial.GetAmbient().GetRed();
    ambiMat[1] = itsMaterial.GetAmbient().GetGreen();
    ambiMat[2] = itsMaterial.GetAmbient().GetBlue();
    ambiMat[3] = itsMaterial.GetAmbientCoeff();

    diffMat[0] = itsMaterial.GetDiffuse().GetRed();
    diffMat[1] = itsMaterial.GetDiffuse().GetGreen();
    diffMat[2] = itsMaterial.GetDiffuse().GetBlue();
    diffMat[3] = itsMaterial.GetDiffuseCoeff();

    specMat[0] = itsMaterial.GetSpecular().GetRed();
    specMat[1] = itsMaterial.GetSpecular().GetGreen();
    specMat[2] = itsMaterial.GetSpecular().GetBlue();
    specMat[3] = itsMaterial.GetSpecularCoeff();

    emisMat[0] = 0.0f;
    emisMat[1] = 0.0f;
    emisMat[2] = 0.0f;
    emisMat[3] = 0.0f;

    coloMat[0] = ambiMat[0]*1.2;
    coloMat[1] = ambiMat[1]*1.2;
    coloMat[2] = ambiMat[2]*1.2;
    coloMat[3] = ambiMat[3]*1.2;

    shine = itsMaterial.GetShininessCoeff();
    firstTime = true;
}

VGLMaterial VGLObject::GetMaterial() const
{
    return itsMaterial;
}

void VGLObject::ApplyMaterial()
{
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambiMat);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffMat);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specMat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiMat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
    glEnable(GL_LIGHT0);
}

void VGLObject::SetColor(const GLubyte& red, const GLubyte& green, const GLubyte& blue)
{
    itsRed = red;
    itsGreen = green;
    itsBlue = blue;
    firstTime = true;
    DefineDisplay();
}

void VGLObject::SetColor(const VGLColor& color)
{
    itsRed = (GLubyte)color.GetRed()*255;
    itsGreen = (GLubyte)color.GetGreen()*255;
    itsBlue = (GLubyte)color.GetBlue()*255;
    firstTime = true;
    DefineDisplay();
}

void VGLObject::GetColor(GLubyte* colVect) const
{
    colVect = new GLubyte[3];
    colVect[0] = itsRed;
    colVect[1] = itsGreen;
    colVect[2] = itsBlue;
}

VGLColor VGLObject::GetColor() const
{
    VGLColor color(itsRed/255.0, itsBlue/255.0, itsGreen/255.0);
    return color;
}

void VGLObject::SetBoundingBox(const BoundingBox& B)
{
    itsBox = B;
}

BoundingBox VGLObject::GetBoundingBox() const
{
    return itsBox;
}


//helper function to draw torus removes 'glut' dependency
void drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius)
{
    double majorStep = 2.0 * M_PI / numMajor;
    double minorStep = 2.0 * M_PI / numMinor;
    int i, j;

    for (i = 0; i < numMajor; ++i) {
	double a0 = i * majorStep;
	double a1 = a0 + majorStep;
	GLfloat x0 = cos(a0);
	GLfloat y0 = sin(a0);
	GLfloat x1 = cos(a1);
	GLfloat y1 = sin(a1);

	glBegin(GL_TRIANGLE_STRIP);
	for (j = 0; j <= numMinor; ++j) {
	    double b = j * minorStep;
	    GLfloat c = cos(b);
	    GLfloat r = minorRadius * c + majorRadius;
	    GLfloat z = minorRadius * sin(b);

	    glNormal3f(x0 * c, y0 * c, z / minorRadius);
	    glTexCoord2f(i / (GLfloat) numMajor, j / (GLfloat) numMinor);
	    glVertex3f(x0 * r, y0 * r, z);

	    glNormal3f(x1 * c, y1 * c, z / minorRadius);
	    glTexCoord2f((i + 1) / (GLfloat) numMajor, j / (GLfloat) numMinor);
	    glVertex3f(x1 * r, y1 * r, z);
	}
	glEnd();
    }
}

