/*
 * ParticleRenderer.cc
 *
 *  Created on: Apr 12, 2011
 *      Author: jakob
 */

#include <QtOpenGL>
#include "ParticleRenderer.h"
#include "util.h"

using namespace vhc::util;

namespace vhc {

ParticleRenderer::ParticleRenderer(): _drawSpheres(false) {

}

ParticleRenderer::~ParticleRenderer() {

}

void ParticleRenderer::render(const Particle& particle) const {

	double pos[] = {particle.getPosition().getX(), particle.getPosition().getY(), particle.getPosition().getZ()};

	if (!_drawSpheres) {
		glBegin(GL_POINTS);
		glVertex3dv(pos);
		glEnd();
	}
	else {
		glPushMatrix();
		glTranslated(pos[0], pos[1], pos[2]);
		util::sphere(0.01);
		glPopMatrix();
	}

}

void ParticleRenderer::enableDrawSpheres(bool value) {
	_drawSpheres = value;
}

bool ParticleRenderer::isDrawSpheresEnabled() const {
	return _drawSpheres;
}

}
