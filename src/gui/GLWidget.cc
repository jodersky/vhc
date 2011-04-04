#include <QtOpenGL>
#include <math.h>
#include <iostream>
#include "GLWidget.h"
#include "StraightElement.h"
#include "ElementRenderer.h"
#include "CurvedElement.h"
#include "Dipole.h"
#include "util.h"
#include "Vector3D.h"

void torus(int numc, int numt, double fraction = 1 , double R = 1, double r = 0.1) {
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * M_PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt / fraction ; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (R+r*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (R+r*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = r * sin(s * twopi / numc);
            glColor3d(0, s/numc, t/numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}



void axes() {
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0); // origin of the line
	glVertex3d(100, 0, 0); // ending point of the line
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0); // origin of the line
	glVertex3d(0, 100, 0); // ending point of the line
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0); // origin of the line
	glVertex3d(0, 0, 100); // ending point of the line
	glEnd();

}


GLWidget::GLWidget (QWidget* parent)
	: QGLWidget (parent), camera(10,0,0), wireframe(false)
{
	eyeX = 0;
	eyeY = 0;
	eyeZ = 10;
	resize (sizeHint ());
}

GLWidget::~GLWidget () {}

QSize GLWidget::minimumSizeHint () const {
	return QSize (50, 50);
}

QSize GLWidget::sizeHint () const {
	return QSize (800, 600);
}

void GLWidget::initializeGL () {
	glClearColor (0, 0, 0, 1.0);
	glEnable (GL_DEPTH_TEST);
	gluPerspective(65.0, 4.0/3, 1.0, 1000.0);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void GLWidget::paintGL () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	//gluLookAt(eyeX,eyeY,eyeZ,
		//0,0,0,
		//0,1,0);
	//glTranslated (0.0, 0.0, -10.0);
	//glColor3d (0.0, 0.0, 1.0);
	camera.setView();
	axes();

	glScaled (300.0, 300.0, 300.0);

	if (wireframe) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}

	vhc::ElementRenderer* er = new vhc::ElementRenderer;

	vhc::StraightElement* se = new vhc::StraightElement(vhc::Vector3D::j, vhc::Vector3D::j + vhc::Vector3D::i, 0.2);
	vhc::StraightElement* se2 = new vhc::StraightElement(vhc::Vector3D(2,0,0), vhc::Vector3D(2,-1,0), 0.2);
	se->accept(*er);
	se2->accept(*er);
	delete se; se = NULL;
	delete se2; se2 = NULL;

	vhc::CurvedElement* ce = new vhc::Dipole(vhc::Vector3D(1,1,0), vhc::Vector3D::i * 2, 0.2, 1, vhc::Vector3D::Null);
	std::cout <<*ce << "\n";
	ce->accept(*er);
	delete er; er = NULL;

	delete ce; ce = NULL;

/*
	glBegin (GL_POLYGON);
	glColor3d(1,0,0);
	glVertex3d (-300, -300, 0.0);
	glColor3d(0,1,0);
	glVertex3d (300 + 10, -300, 0.0);
	glColor3d(0,0,1);
	glVertex3d (0, 300, 0.0);
	glColor3d(1,1,1);
	glVertex3d (0, 0, 100);
	glColor3d(0,1,0);
	glVertex3d (300 + 10, -300, 0.0);
	glEnd ();


	axes();

	glColor3d(0,0,1);
	glScaled(300,300,300);

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	torus(12, 20, 4, 1, 0.1);

	vhc::util::cylinder(0.1, 0, 2, 12, 20);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);*/

}

void GLWidget::resizeGL (int width, int height) {
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-width, width, -height, height, -1000.0, 1000.0);
	glMatrixMode (GL_MODELVIEW);
}

void GLWidget::mousePressEvent (QMouseEvent* event) {
}

void GLWidget::mouseReleaseEvent (QMouseEvent* event) {
}

void GLWidget::keyPressEvent (QKeyEvent* event) {
	switch (event->key()) {
		case Qt::Key_Escape:
			qApp->quit();
			break;
		case Qt::Key_Up:
			//eyeZ += 10;
			camera.theta += 2 *  M_PI / 100;
			break;
		case Qt::Key_Down:
			//eyeZ -= 10;
			camera.theta -= 2 *  M_PI / 100;
			break;
		case Qt::Key_Right:
			//eyeX += 10;
			camera.phi += 2 *  M_PI / 100;
			break;
		case Qt::Key_Left:
			//eyeX -= 10;
			camera.phi -= 2 *  M_PI / 100;
			break;
		case Qt::Key_R:
			//eyeX = 0;
			//eyeY = 0;
			//eyeZ = 10;
			camera.r = 10;
			camera.phi = 0;
			camera.theta = 0;
			break;
		case Qt::Key_Space:
			wireframe = !wireframe;
			break;
		default:
			break;
	}
	repaint();
}

void GLWidget::keyReleaseEvent (QKeyEvent* event) {

}
