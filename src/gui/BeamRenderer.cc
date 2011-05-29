/*
 * BeamRenderer.cc
 *
 *  Created on: May 27, 2011
 *      Author: jakob
 */

#include <QtOpenGL>
#include "BeamRenderer.h"
#include "util.h"

namespace vhc {

BeamRenderer::BeamRenderer() {
	// TODO Auto-generated constructor stub

}

BeamRenderer::~BeamRenderer() {
	// TODO Auto-generated destructor stub
}

void BeamRenderer::render(const Beam& beam) const {
	const Beam::ParticleCollection& particles = beam.getParticles();

	if (_spheres) {
		for (Beam::ParticleCollection::const_iterator i = particles.begin(); i != particles.end(); ++i) {
			double pos[] = {(**i).getPosition().getX(), (**i).getPosition().getY(), (**i).getPosition().getZ()};
			glPushMatrix();
			glTranslated(pos[0], pos[1], pos[2]);
			util::sphere(0.01);
			glPopMatrix();
		}
	} else {
		glBegin(GL_POINTS);
		for (Beam::ParticleCollection::const_iterator i = particles.begin(); i != particles.end(); ++i) {
			double pos[] = {(**i).getPosition().getX(), (**i).getPosition().getY(), (**i).getPosition().getZ()};
			glVertex3dv(pos);
		}
		glEnd();

	}

}

void BeamRenderer::setSpheresEnabled(bool value) {
	_spheres = value;
}

bool BeamRenderer::getSpheresEnabled() const {
	return _spheres;
}

}
