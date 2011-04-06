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

using namespace vhc;

void axes() {
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0); // origin of the line
	glVertex3d(1, 0, 0); // ending point of the line
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0); // origin of the line
	glVertex3d(0, 1, 0); // ending point of the line
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0); // origin of the line
	glVertex3d(0, 0, 1); // ending point of the line
	glEnd();
}

void grid() {
	int size = 10;
	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for (int i = 0; i <= 2 * size; ++i) {
		glVertex3d(1.0 * (i - size) / size, -1, 0);
		glVertex3d(1.0 * (i - size) / size, 1, 0);
	};
	glEnd();
	glBegin(GL_LINES);
	for (int i = 0; i <= 2 * size; ++i) {
		glVertex3d(-1, 1.0 * (i - size) / size, 0);
		glVertex3d(1, 1.0 * (i - size) / size, 0);
	};
	glEnd();

}


GLWidget::GLWidget (QWidget* parent)
	: QGLWidget (parent), wireframe(false), camera(), center()
{
	setMouseTracking(true);
	resize (sizeHint ());
}

GLWidget::~GLWidget () {}

QSize GLWidget::minimumSizeHint () const {
	return QSize (50, 50);
}

QSize GLWidget::sizeHint () const {
	return QSize (1000, 800);
}

void GLWidget::initializeGL () {
	glClearColor (0, 0, 0, 1.0);
	glEnable (GL_DEPTH_TEST);
	//gluPerspective(65.0, 4.0/3.0, 1.0, 10000.0);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void GLWidget::resizeGL (int width, int height) {
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 1, 1.0, 10000.0);
	glMatrixMode (GL_MODELVIEW);
}

void GLWidget::paintGL () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	camera.setView();
	glPushMatrix();
	glScaled(100, 100, 100);
	grid();
	axes();
	glPopMatrix();


	center = QWidget::mapToGlobal(QPoint(this->size().width() / 2, this->size().height() / 2));
	QCursor::setPos(center);

	glScaled (100.0, 100.0, 100.0);


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
	//se.draw()
	se2->accept(*er);
	delete se; se = NULL;
	delete se2; se2 = NULL;

	vhc::CurvedElement* ce = new vhc::Dipole(vhc::Vector3D(1,1,0), vhc::Vector3D::i * 2, 0.2, 1, vhc::Vector3D::Null);
	std::cout <<*ce << "\n";
	ce->accept(*er);
	delete er; er = NULL;

	delete ce; ce = NULL;

}



void GLWidget::mousePressEvent (QMouseEvent* event) {
}

void GLWidget::mouseReleaseEvent (QMouseEvent* event) {
}

void GLWidget::keyPressEvent (QKeyEvent* event) {
	Vector3D mv = Vector3D::Null;
	switch (event->key()) {
		case Qt::Key_Escape:
			qApp->quit();
			break;
		case Qt::Key_A:
			mv = mv - Vector3D::j;
			break;
		case Qt::Key_W:
			mv = mv - Vector3D::i;
			break;
		case Qt::Key_D:
			mv = mv + Vector3D::j;
			break;
		case Qt::Key_S:
			mv = mv + Vector3D::i;
			break;
		case Qt::Key_Up:
			camera.addPitch(2 *  M_PI / 100);
			break;
		case Qt::Key_Down:
			camera.addPitch(-2 *  M_PI / 100);
			break;
		case Qt::Key_Right:
			camera.addHeading(-2 *  M_PI / 100);
			break;
		case Qt::Key_Left:
			camera.addHeading(2 *  M_PI / 100);
			break;
		case Qt::Key_R:
			break;
		case Qt::Key_Space:
			wireframe = !wireframe;
			break;
		default:
			break;
	}
	camera.move(mv);
	updateGL();
	//repaint();
}

void GLWidget::keyReleaseEvent (QKeyEvent* event) {

}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
	int dheading = -QCursor::pos().x() + center.x();
	int dpitch = -QCursor::pos().y() + center.y();
	camera.addHeading(1.0 * dheading / 20);
	camera.addPitch(1.0 * dpitch / 20);
	updateGL();

}
