/*
 * BruteForceInteractor.cc
 *
 *  Created on: May 26, 2011
 *      Author: jakob
 */

#include <iostream>
#include "BruteForceInteractor.h"

using namespace std;

namespace vhc {

BruteForceInteractor::BruteForceInteractor(): particles(0) {}

BruteForceInteractor::~BruteForceInteractor() {}

void BruteForceInteractor::applyInteractions() {
	for (list< Particle* >::iterator i = particles.begin(); i != particles.end(); ++i) {
		for (list< Particle* >::iterator j = particles.begin(); j != particles.end(); ++j) if (i != j) {
			double r = ((**j).getPosition() - (**i).getPosition()).norm();
			if (r != 0) {
				Vector3D d = ((**j).getPosition() - (**i).getPosition()).unit();
				Vector3D force = d * (**i).getCharge() * (**i).getCharge() /
								(4 * M_PI * constants::EPSILON_ZERO * r * r * r * (**i).getGamma() * (**i).getGamma());
				(**i).applyForce(force);
				(**j).applyForce(-force);
			}
		}
	}
}
void BruteForceInteractor::acceleratorClosed() {}

void BruteForceInteractor::react(const ParticleAddedEvent& event) {
	particles.push_back(event.getParticle());
}
void BruteForceInteractor::react(const ParticleRemovedEvent& event) {
	particles.remove(event.getParticle());
}

}
