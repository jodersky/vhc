#include <QtOpenGL>
#include "GLWidget.h"

GLWidget::GLWidget (QWidget* parent)
	: QGLWidget (parent)
{
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
	glClearColor (255, 255, 255, 1.0);
	glEnable (GL_DEPTH_TEST);
	gluPerspective(65.0, 4.0/3, 1.0, 1000.0);
}

void GLWidget::paintGL () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	//gluLookAt(0,0,0,
	//	0,0,0,
	//	0,0,1);
	//glTranslated (0.0, 0.0, -10.0);
	//glColor3d (0.0, 0.0, 1.0);
	//glScaled (300.0, 300.0, 300.0);

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
}

void GLWidget::resizeGL (int width, int height) {
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-width, width, -height, height, -100.0, 100.0);
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
			qApp->quit();
			break;
		default:
			break;
	}
}

void GLWidget::keyReleaseEvent (QKeyEvent* event) {
}
