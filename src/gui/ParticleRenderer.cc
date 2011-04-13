/*
 * ParticleRenderer.cc
 *
 *  Created on: Apr 12, 2011
 *      Author: jakob
 */

#include <QtOpenGL>
#include "ParticleRenderer.h"
#include "util.h"

namespace vhc {

ParticleRenderer::ParticleRenderer() {
	//Auto-generated constructor stub

}

ParticleRenderer::~ParticleRenderer() {
	//Auto-generated destructor stub
}

void ParticleRenderer::render(const Particle& particle) const {
	glPushMatrix();
	glTranslated(particle.getPosition().getX(), particle.getPosition().getY(), particle.getPosition().getZ());
	glBegin(GL_POINTS);
	//glVertex3d(0, 0, 0);
	util::sphere(0.01);
	glEnd();
	glPopMatrix();
}

}
