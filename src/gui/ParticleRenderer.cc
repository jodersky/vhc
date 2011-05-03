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
	glPushMatrix();
	glTranslated(particle.getPosition().getX(), particle.getPosition().getY(), particle.getPosition().getZ());

	if (_drawSpheres) {
		glBegin(GL_POINTS);
		glVertex3d(0, 0, 0);
		glEnd();
	}
	else {
		util::sphere(0.01);
	}
	glPopMatrix();
}

void ParticleRenderer::drawSpheres(bool value) {
	_drawSpheres = value;
}

}
