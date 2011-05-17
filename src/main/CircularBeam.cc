/*
 * CircularBeam.cc
 *
 *  Created on: May 17, 2011
 *      Author: jakob
 */

#include "CircularBeam.h"

namespace vhc {

CircularBeam::CircularBeam(const Particle& referenceParticle, int quantity, int lambda): Beam(referenceParticle, quantity, lambda) {

}

CircularBeam::~CircularBeam() {}

CircularBeam::init(const Particle& referenceParticle, int quantity, int lambda) {

}
}
