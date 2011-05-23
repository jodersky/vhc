/*
 * Stage.cc
 *
 *  Created on: Apr 6, 2011
 *      Author: jakob
 */

#include <iostream>
#include <list>
#include <algorithm>
#include "util.h"
#include "Stage.h"

using namespace std;
using namespace vhc::util;

namespace vhc {

Stage::Stage(QWidget* parent):
		QGLWidget (parent),
		camera(),
		keyManager(*this),
		accelerator(NULL),
		elementRenderer(),
		particleRenderer(),
		displayMode(FILL),
		frameTime(0),
		h(1E-12),
		paused(true) {

	timer = new QTimer(this);


	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(1);

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

void Stage::displayText(QString text[], int size) {
	for (int i = 0; i < size; ++i) {
		renderText(0, (i + 1) * 12, text[i]);
	}
}

void Stage::paintGL() {
	//time.start();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.setView();
	QString text[] = {
			QString("-----simulation-----"),
			QString("fps: ") + QString::number(1E3 / frameTime),
			QString("status: ") + (paused ? QString("paused") : QString("running")),
			QString("-----camera-----"),
			QString("coordinates: ") + camera.getPosition().toString().c_str(),
			QString("heading: ") + QString::number(camera.getHeading()),
			QString("pitch: ") + QString::number(camera.getPitch()),
			QString("-----accelerator-----"),
			QString("Elements: ") + QString::number(accelerator->getElements().size()),
			QString("Particles: ") + QString::number(accelerator->getParticles().size()),
			QString("") + accelerator->getParticles().front()->toString().c_str()
	};
	displayText(text, 11);
	//renderText(0,60,QString("") + accelerator->getParticle(0)->getElement()->magneticFieldAt(accelerator->getParticle(0)->getPosition()).toString().c_str());
	//renderText(0,72,QString("") + accelerator->getParticle(0)->toString().c_str());
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
		for (Accelerator::ElementCollection::const_iterator i = accelerator->getElements().begin(); i != accelerator->getElements().end(); ++i) {
			elementRenderer.render(**i);
		}

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		glColor3d(0, 0, 1);

		Accelerator::ParticleCollection particles = accelerator->getParticles();
		for (Accelerator::ParticleCollection::const_iterator i = particles.begin(); i != particles.end(); ++i) {
			particleRenderer.render(**i);
		}
	}

		double dt = frameTime;
		double s = 0.002;
		MutableVector3D mv = Vector3D::Null;
		if (keyManager.isPressed(Qt::Key_A)) mv -= Vector3D::j * dt * s;
		if (keyManager.isPressed(Qt::Key_W)) mv -= Vector3D::i * dt * s;
		if (keyManager.isPressed(Qt::Key_D)) mv += Vector3D::j * dt * s;
		if (keyManager.isPressed(Qt::Key_S)) mv += Vector3D::i * dt * s;
		if (keyManager.isPressed(Qt::Key_PageUp)) mv += Vector3D::k * dt * s;
		if (keyManager.isPressed(Qt::Key_PageDown)) mv -= Vector3D::k * dt * s;
		camera.move(mv);


	if (!paused) for (int i = 0; i < 30; ++i) accelerator->step(h);

	glColor3d(1,1,0);
	util::crosshair();

	frameTime = time.restart();
}


void Stage::mouseMoveEvent(QMouseEvent* event) {
	int dheading = -event->x() + center.x();
	int dpitch = -event->y() + center.y();
	camera.addHeading(1.0 * dheading * frameTime / 4000);
	camera.addPitch(1.0 * dpitch * frameTime / 4000);
	QCursor::setPos(QWidget::mapToGlobal(center));
}

void Stage::keyPressEvent (QKeyEvent* event) {
	keyManager.press(event->key());
}

void Stage::keyReleaseEvent (QKeyEvent* event) {
	keyManager.release(event->key());
}

Camera& Stage::getCamera() {
	return camera;
}

DisplayMode Stage::getDisplayMode() const {
	return displayMode;
}

void Stage::setDisplayMode(DisplayMode value) {
	displayMode = value;
}

bool Stage::isRunning() const {
	return !paused;
}

void Stage::setRunning(bool value) {
	paused = !value;
}

ElementRenderer& Stage::getElementRenderer(){
	return elementRenderer;
}

ParticleRenderer& Stage::getParticleRenderer() {;
	return particleRenderer;
}

}
