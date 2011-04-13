/*
 * Stage.cc
 *
 *  Created on: Apr 6, 2011
 *      Author: jakob
 */

#include "util.h"
#include "Stage.h"

using namespace vhc::util;

namespace vhc {


Stage::Stage(QWidget* parent): QGLWidget (parent), accelerator(NULL), camera(), elementRenderer(new ElementRenderer), particleRenderer(), wireframe(false), keys(0) {
	setMouseTracking(true);
}

Stage::~Stage() {
	delete elementRenderer; elementRenderer = NULL;
};

void Stage::initializeGL () {
	glEnable (GL_DEPTH_TEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glClearColor (0, 0, 0, 1.0);
}

void Stage::resizeGL (int width, int height) {
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 1.0 * width / height, 1.0, 10000.0);
	glMatrixMode (GL_MODELVIEW);
}

void Stage::paintGL() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	camera.setView();

	glPushMatrix();
	glScaled(100, 100, 100);
	glColor3d(0.5, 0.5, 0.5);
	grid(20);
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


	if (accelerator != NULL){
		glColor3d(0.9, 0.4, 0);
		for (unsigned int i = 0; i < accelerator->getElements().size(); ++i) {
			accelerator->getElements()[i]->accept(*elementRenderer);
		}
		glColor3d(0, 0, 1);
		for (unsigned int i = 0; i < accelerator->getParticles().size(); ++i) {
			particleRenderer.render(*(accelerator->getParticles()[i]));
		}
	}



}

void Stage::mouseMoveEvent(QMouseEvent* event) {
	int dheading = -QCursor::pos().x() + center.x();
	int dpitch = -QCursor::pos().y() + center.y();
	camera.addHeading(1.0 * dheading / 200);
	camera.addPitch(1.0 * dpitch / 200);
	updateGL();
}

void Stage::keyPressEvent (QKeyEvent* event) {
	Vector3D mv = Vector3D::Null;
	switch (event->key()) {
		case Qt::Key_Escape:
			qApp->quit();
			break;
		case Qt::Key_A:
			//mv = mv - Vector3D::j;
			keys |= 1;
			break;
		case Qt::Key_W:
			//mv = mv - Vector3D::i;
			keys |= 2;
			break;
		case Qt::Key_D:
			//mv = mv + Vector3D::j;
			keys |= 4;
			break;
		case Qt::Key_S:
			//mv = mv + Vector3D::i;
			keys |= 8;
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

	if (keys & 1) mv = mv - Vector3D::j;
	if (keys & 2) mv = mv - Vector3D::i;
	if (keys & 4) mv = mv + Vector3D::j;
	if (keys & 8) mv = mv + Vector3D::i;

	camera.move(mv);
	updateGL();
}

void Stage::keyReleaseEvent (QKeyEvent* event) {
	switch (event->key()) {
			case Qt::Key_A:
				//mv = mv - Vector3D::j;
				keys &= ~1;
				break;
			case Qt::Key_W:
				//mv = mv - Vector3D::i;
				keys &= ~2;
				break;
			case Qt::Key_D:
				//mv = mv + Vector3D::j;
				keys &= ~4;
				break;
			case Qt::Key_S:
				//mv = mv + Vector3D::i;
				keys &= ~8;
				break;
			default:
				break;
	}
}

}
