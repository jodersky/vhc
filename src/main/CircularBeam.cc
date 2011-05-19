/*
 * CircularBeam.cc
 *
 *  Created on: May 17, 2011
 *      Author: jakob
 */

#include "CircularBeam.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

CircularBeam::CircularBeam(const Particle& referenceParticle, int quantity, int lambda): Beam(referenceParticle, quantity, lambda) {

}

CircularBeam::~CircularBeam() {}

void CircularBeam::initializeParticles() {
	Element* element = referenceParticle.getElement();

	for (int i = 0; i < quantity / lambda; ++i) {

		particles.push_back(new Particle(
				element->getEntryPosition(),
				referenceParticle.getMass() * lambda,
				referenceParticle.getCharge() * lambda,
				referenceParticle.getEnergy(),
				element->getDiagonal()
				));

		element = element->getNext();
	}

}

CircularBeam* CircularBeam::clone() const {
	return new CircularBeam(referenceParticle, quantity, lambda);
}

}
