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

Stage::Stage(QWidget* parent):
		QGLWidget (parent),
		accelerator(NULL),
		camera(),
		elementRenderer(new ElementRenderer),
		particleRenderer(),
		displayMode(FILL),
		keys(0) {

	timer = new QTimer(this);


	connect(timer, SIGNAL(timeout()), this, SLOT(foo()));
	timer->start(1);

	setMouseTracking(true);
}

Stage::~Stage() {
	delete elementRenderer; elementRenderer = NULL;
	delete timer; timer = NULL;
};

void Stage::initializeGL () {
	glEnable (GL_DEPTH_TEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glClearColor (0, 0, 0, 1.0);
}

void Stage::resizeGL (int width, int height) {
	setCursor(QCursor(Qt::CrossCursor));
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 1.0 * width / height, 0.1, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void Stage::paintGL() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.setView();
	renderText(0,12,QString("camera coordinates:") + camera.getPosition().toString().c_str());
	axes();

	glPushMatrix();
	glScaled(10, 10, 10);
	glColor3d(0.5, 0.5, 0.5);
	grid(20);
	glPopMatrix();


	center = QWidget::mapToGlobal(QPoint(this->size().width() / 2, this->size().height() / 2));
	QCursor::setPos(center);

//	glScaled (100.0, 100.0, 100.0);


	switch (displayMode) {
	case FILL:
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		break;
	case WIREFRAME:
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		break;
	case POINTS:
		glPolygonMode(GL_FRONT, GL_POINT);
		glPolygonMode(GL_BACK, GL_POINT);
		break;
	default:
		break;
	}

	if (accelerator != NULL){
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		for (unsigned int i = 0; i < accelerator->getElements().size(); ++i) {
			accelerator->getElements()[i]->accept(*elementRenderer);
		}
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

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
	update();
}

void Stage::keyPressEvent (QKeyEvent* event) {
	Vector3D mv = Vector3D::Null;
	switch (event->key()) {
		case Qt::Key_Escape:
			qApp->quit();
			break;
		case Qt::Key_A:
			keys |= 1;
			break;
		case Qt::Key_W:
			keys |= 2;
			break;
		case Qt::Key_D:
			keys |= 4;
			break;
		case Qt::Key_S:
			keys |= 8;
			break;
		case Qt::Key_PageUp:
			keys |= 16;
			break;
		case Qt::Key_PageDown:
			keys |= 32;
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
		case Qt::Key_1:
			displayMode = FILL;
			break;
		case Qt::Key_2:
			displayMode = WIREFRAME;
			break;
		case Qt::Key_3:
			displayMode = POINTS;
			break;
		default:
			break;
	}

	if (keys & 1) mv = mv - 0.1 * Vector3D::j;
	if (keys & 2) mv = mv - 0.1 * Vector3D::i;
	if (keys & 4) mv = mv + 0.1 * Vector3D::j;
	if (keys & 8) mv = mv + 0.1 * Vector3D::i;
	if (keys & 16) mv = mv + 0.1 * Vector3D::k;
	if (keys & 32) mv = mv - 0.1 * Vector3D::k;
	camera.move(mv);


	update();
}

void Stage::keyReleaseEvent (QKeyEvent* event) {
	switch (event->key()) {
			case Qt::Key_A:
				keys &= ~1;
				break;
			case Qt::Key_W:
				keys &= ~2;
				break;
			case Qt::Key_D:
				keys &= ~4;
				break;
			case Qt::Key_S:
				keys &= ~8;
				break;
			case Qt::Key_PageUp:
				keys &= ~16;
				break;
			case Qt::Key_PageDown:
				keys &= ~32;
				break;
			default:
				break;
	}
}

}
