/*
 * SingleBeam.cc
 *
 *  Created on: May 18, 2011
 *      Author: jakob
 */

#include "SingleBeam.h"
#include "iostream"

namespace vhc {

SingleBeam::SingleBeam(const Particle& particle): Beam(particle, 1, 1) {}

SingleBeam::~SingleBeam() {

}

void SingleBeam::initializeParticles() {
	particles.push_back(new Particle(referenceParticle));
}

SingleBeam* SingleBeam::clone() const {
	return new SingleBeam(referenceParticle);
}

}
