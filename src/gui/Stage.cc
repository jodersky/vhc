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
		elementRenderer(),
		particleRenderer(),
		displayMode(FILL),
		keys(0),
		frameTime(0) {

	timer = new QTimer(this);


	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000.0/60);

	setMouseTracking(true);
}

Stage::~Stage() {
	delete timer; timer = NULL;
};

void Stage::initializeGL () {
	glEnable (GL_DEPTH_TEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glClearColor (0, 0, 0, 1.0);
}

void Stage::resizeGL (int width, int height) {
	setCursor(QCursor(Qt::BlankCursor));
	center = QPoint(width / 2, height / 2);
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 1.0 * width / height, 0.01, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void Stage::paintGL() {
	//time.start();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.setView();
	renderText(0,12,QString("fps: ") + QString::number(1E3 / frameTime));
	renderText(0,24,QString("camera coordinates: ") + camera.getPosition().toString().c_str());
	renderText(0,36,QString("heading: ") + QString::number(camera.getHeading()));
	renderText(0,48,QString("pitch: ") + QString::number(camera.getPitch()));
	axes();


	glPushMatrix();
	glScaled(10, 10, 10);
	glColor3d(0.5, 0.5, 0.5);
	grid(20);
	glPopMatrix();

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
			elementRenderer.render(*(accelerator->getElements()[i]));
		}
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		glColor3d(0, 0, 1);
		for (unsigned int i = 0; i < accelerator->getParticles().size(); ++i) {
			particleRenderer.render(*(accelerator->getParticles()[i]));
		}
	}

	if (keys != 0) {
		double dt = frameTime;
		double s = 0.002;
		Vector3D mv = Vector3D::Null;
		if (keys & 1) mv = mv - Vector3D::j * dt * s;
		if (keys & 2) mv = mv - Vector3D::i * dt * s;
		if (keys & 4) mv = mv + Vector3D::j * dt * s;
		if (keys & 8) mv = mv + Vector3D::i * dt * s;
		if (keys & 16) mv = mv + Vector3D::k * dt * s;
		if (keys & 32) mv = mv - Vector3D::k * dt * s;
		camera.move(mv);
	}



	glColor3d(1,1,0);
	util::crosshair();

	frameTime = time.restart();
}


void Stage::mouseMoveEvent(QMouseEvent* event) {
	int dheading = -event->x() + center.x();
	int dpitch = -event->y() + center.y();
	camera.addHeading(1.0 * dheading * frameTime / 4000);
	camera.addPitch(1.0 * dpitch * frameTime / 4000);
	QCursor::setPos(center);
	update();
}

void Stage::keyPressEvent (QKeyEvent* event) {
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
