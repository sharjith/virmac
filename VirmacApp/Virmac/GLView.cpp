#include "GLView.h"

GLView::GLView(QWidget *parent, const char * /*name*/ ) : QGLWidget(parent, 0)
{
    xRot = 45.0;
    yRot = 45.0;
    modelNum = 6;
    opacity = 1.0f;
    ambiLight[0] = 0.3;
    ambiLight[1] = 0.3;
    ambiLight[2] = 0.3;
    ambiLight[3] = 1.0;

    diffLight[0] = 0.7f;
    diffLight[1] = 0.7f;
    diffLight[2] = 0.7f;
    diffLight[3] = 1.0f;

    specLight[0] = 1.0f;
    specLight[1] = 1.0f;
    specLight[2] = 1.0f;
    specLight[3] = 1.0f;

    ambiMat[0] = 0.2;
    ambiMat[1] = 0.5;
    ambiMat[2] = 0.7;
    ambiMat[3] = opacity;

    diffMat[0] = 0.7f;
    diffMat[1] = 0.7f;
    diffMat[2] = 0.7f;
    diffMat[3] = opacity;

    specMat[0] = 1.0f;
    specMat[1] = 1.0f;
    specMat[2] = 1.0f;
    specMat[3] = opacity;

    specRef[0] =  1.0f;
    specRef[1] =  1.0f;
    specRef[2] =  1.0f;
    specRef[3] =  1.0f;

    shine = 128;

    hasTexture = false;

    sphere = gluNewQuadric();
    cone = gluNewQuadric();
    cylinder = gluNewQuadric();
    base = gluNewQuadric();
}

GLView::~GLView()
{
    gluDeleteQuadric(sphere);
    gluDeleteQuadric(cone);
    gluDeleteQuadric(cylinder);
    gluDeleteQuadric(base);	
}

void GLView::changeModel()
{
    modelNum++;
    if(modelNum > 6)
	modelNum = 1;
    updateGL();
}

void GLView::updateView()
{
    updateGL();
}

void GLView::setTexture(QImage img)
{
    tex1 = QGLWidget::convertToGLFormat( img );  // flipped 32bit RGBA
}

void GLView::initializeGL ()
{	
    // Set up the rendering context, define display lists etc.:
    /* Insert your OpenGL initialization code here */
    // Set background color
    qglClearColor(QColor("gray"));

    // Set drawing color to
    glColor3ub(255, 255, 255);

    if ( !buf.load( "textures/gllogo.bmp" ) )
    {	// Load first image from file
	qWarning( "Could not read image file, using single-color instead." );
	QImage dummy( 128, 128, (QImage::Format)5 );
	dummy.fill( Qt::white );
	buf = dummy;
    }

    tex1 = QGLWidget::convertToGLFormat( buf );  // flipped 32bit RGBA

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glEnable( GL_TEXTURE_2D );



}

void GLView::resizeGL ( int w, int h )
{
    GLdouble modelMatrix[16];
  GLdouble projMatrix[16];
  GLint viewport[4];

    // setup viewport, projection etc.:
    /* Prevent a divide by zero*/
    if(h == 0)
	h = 1;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (w <= h)
	glOrtho (-100.0f, 100.0f, -100.0f*h/w, 100.0f*h/w, -100.0f, 100.0f);
    else
	glOrtho (-100.0f*w/h, 100.0f*w/h, -100.0f, 100.0f, -100.0f, 100.0f);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    /* store limits for gradient background */
  glGetDoublev (GL_PROJECTION_MATRIX, projMatrix);
  glGetDoublev (GL_MODELVIEW_MATRIX, modelMatrix);
  glGetIntegerv (GL_VIEWPORT, viewport);
  gluUnProject (0, 0, 1, modelMatrix, projMatrix, viewport,
		&win_xmin, &win_ymin, &winz);
  gluUnProject (w, h, 1, modelMatrix, projMatrix, viewport,
		&win_xmax, &win_ymax, &winz);

}

void GLView::paintGL ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*gradient background */
  glDisable (GL_DEPTH_TEST);
  glDisable (GL_LIGHTING);
  glDisable (GL_TEXTURE_2D);
  glShadeModel (GL_SMOOTH);
  glBegin (GL_POLYGON);
  glColor3ub (51, 51, 101);
  glVertex3f (win_xmin, win_ymax, 100);
  glVertex3f (win_xmax, win_ymax, 100);
  glColor3ub (171, 172, 193);
  glVertex3f (win_xmax, win_ymin, 100);
  glVertex3f (win_xmin, win_ymin, 100);
  glEnd ();
  /*end gradient background */

  /*
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    glColor3ub(51, 51, 101);
    glVertex3f(-120, 120, 100);
    glVertex3f(120, 120, 100);
    glColor3ub(171, 172, 193);
    glVertex3f(120, -120, 100);
    glVertex3f(-120, -120, 100);
    glEnd();
    */

    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);
    // Enable lighting
    glEnable(GL_LIGHTING);

    GLfloat position[] = {0.0, 0.0, 3.0, 0.0};
    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};

    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    glEnable(GL_LIGHT0);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LESS);

    /* required for two side lighting in case of open objects
       if(modelNum == 4)
       glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
       else
       glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
     */

    //Setup Material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiMat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat);


    // All materials hereafter have full specular reflectivity
    // with a high shine
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specRef);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, shine);

    glShadeModel(GL_SMOOTH);

    if(hasTexture)
	glEnable( GL_TEXTURE_2D );
    else
	glDisable( GL_TEXTURE_2D );

    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex1.width(), tex1.height(), 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits() );

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    switch(modelNum)
    {
	case 1:
	    drawCube(80.0f);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_TEXTURE_2D);
	    glColor3f(1.0, 1.0, 1.0);
	    renderText(5, 15,  "Cube");
	    glEnable(GL_LIGHTING);
	    if(hasTexture)
		glEnable(GL_TEXTURE_2D);
	    break;
	case 2:
	    gluQuadricTexture( sphere, GL_TRUE );
	    gluSphere(sphere, 50, 50, 50);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_TEXTURE_2D);
	    glColor3f(1.0, 1.0, 1.0);
	    renderText(5, 15,  "Sphere");
	    glEnable(GL_LIGHTING);
	    if(hasTexture)
		glEnable(GL_TEXTURE_2D);
	    break;
	case 3:
	    drawTorus(50, 50, 50.0f, 20.0f);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_TEXTURE_2D);
	    glColor3f(1.0, 1.0, 1.0);
	    renderText(5, 15,  "Torus");
	    glEnable(GL_LIGHTING);
	    break;
	case 4:
	    gluQuadricOrientation(base, GLU_INSIDE);
	    gluQuadricTexture( cone, GL_TRUE );
	    gluCylinder(cone, 50, 0, 80, 50, 1);
	    gluQuadricTexture( base, GL_TRUE );
	    gluDisk(base, 0., 50, 50, 1);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_TEXTURE_2D);
	    glColor3f(1.0, 1.0, 1.0);
	    renderText(5, 15,  "Cone");
	    glEnable(GL_LIGHTING);
	    if(hasTexture)
		glEnable(GL_TEXTURE_2D);
	    break;
	case 5:
	    glPushMatrix();
	    glTranslatef(0.0, 0.0, -40.0);
	    gluQuadricTexture( cylinder, GL_TRUE );
	    gluCylinder(cylinder, 50, 50, 80, 50, 1);
	    gluQuadricTexture( base, GL_TRUE );
	    gluQuadricOrientation(base, GLU_INSIDE);
	    gluDisk(base, 0., 50, 50, 1);
	    glTranslatef(0.0, 0.0, 80.0);
	    gluQuadricOrientation(base, GLU_OUTSIDE);
	    gluDisk(base, 0., 50, 50, 1);
	    glPopMatrix();
	    glDisable(GL_LIGHTING);
	    glDisable(GL_TEXTURE_2D);
	    glColor3f(1.0, 1.0, 1.0);
	    renderText(5, 15,  "Cylinder");
	    glEnable(GL_LIGHTING);
	    if(hasTexture)
		glEnable(GL_TEXTURE_2D);
	    break;
	case 6:
	    glutSolidTeapot(50.0f);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_TEXTURE_2D);
	    glColor3f(1.0, 1.0, 1.0);
	    renderText(5, 15,  "Teapot");
	    glEnable(GL_LIGHTING);
	    if(hasTexture)
		glEnable(GL_TEXTURE_2D);
	    break;
	default:
	    break;
    }
    glDisable(GL_BLEND);
    glPopMatrix();
}

void GLView::slotXRotation(int rotX)
{
    xRot = -1.0*(GLfloat)rotX;
    updateGL();
}

void GLView::slotYRotation(int rotY)
{
    yRot = (GLfloat)rotY;
    updateGL();
}

void GLView::drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius)
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

void GLView::drawCube(float size)
{
    static GLfloat n[6][3] =
    {
	{-1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{1.0, 0.0, 0.0},
	{0.0, -1.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
	{0, 1, 2, 3},
	{3, 2, 6, 7},
	{7, 6, 5, 4},
	{4, 5, 1, 0},
	{5, 6, 2, 1},
	{7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
	glBegin(GL_QUADS);
	glNormal3fv(&n[i][0]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(&v[faces[i][0]][0]);
	glTexCoord2f(1.0, 0.0);
	glVertex3fv(&v[faces[i][1]][0]);
	glTexCoord2f(1.0, 1.0);
	glVertex3fv(&v[faces[i][2]][0]);
	glTexCoord2f(0.0, 1.0);
	glVertex3fv(&v[faces[i][3]][0]);
	glEnd();
    }
}

char* GLView::readShaderFile(char *FileName) {
	FILE *fp;
	char *DATA = NULL;

	int flength = 0;

	fp = fopen(FileName,"rt");

    fseek(fp, 0, SEEK_END);
    flength = ftell(fp);
    rewind(fp);

	DATA = (char *)malloc(sizeof(char) * (flength+1));
	flength = fread(DATA, sizeof(char), flength, fp);
	DATA[flength] = '\0';

	fclose(fp);

	return DATA;
}
void GLView::InitShader (void) {
	GLEW_ARB_vertex_shader;
	GLEW_ARB_fragment_shader;

	VertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	FragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	VertexShaderSource = readShaderFile("light-advanced.vert");
	FragmentShaderSource = readShaderFile("light-advanced.frag");

	const char * VS = VertexShaderSource;
	const char * FS = FragmentShaderSource;

	glShaderSourceARB(VertexShader, 1, &VS,NULL);
	glShaderSourceARB(FragmentShader, 1, &FS,NULL);

	free(VertexShaderSource);free(FragmentShaderSource);

	glCompileShaderARB(VertexShader);
	glCompileShaderARB(FragmentShader);

	ShaderProgram = glCreateProgramObjectARB();

	glAttachObjectARB(ShaderProgram,VertexShader);
	glAttachObjectARB(ShaderProgram,FragmentShader);

	glLinkProgramARB(ShaderProgram);
	glUseProgramObjectARB(ShaderProgram);
}

void GLView::DeInitShader (void)
{
	glDetachObjectARB(ShaderProgram,VertexShader);
	glDetachObjectARB(ShaderProgram,FragmentShader);

	glDeleteObjectARB(ShaderProgram);
}
