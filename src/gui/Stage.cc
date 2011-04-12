/*
 * Stage.cc
 *
 *  Created on: Apr 6, 2011
 *      Author: jakob
 */


#include "Stage.h"

namespace vhc {

Stage::Stage(QWidget* parent): QGLWidget (parent), elements(0), camera(), elementRenderer(new ElementRenderer), particleRenderer(), wireframe(false) {
	setMouseTracking(true);
}

Stage::~Stage() {
	delete elementRenderer; elementRenderer = NULL;
};

void Stage::initializeGL () {
	glEnable (GL_DEPTH_TEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	gluPerspective(65.0, 1.6, 0.1, 10000.0);
	glClearColor (0, 0, 0, 1.0);
}

void Stage::resizeGL (int width, int height) {
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 1, 1.0, 10000.0);
	glMatrixMode (GL_MODELVIEW);
}



}
