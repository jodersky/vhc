/*
 * Beam.cc
 *
 *  Created on: May 6, 2011
 *      Author: jakob
 */

#include <math.h>
#include "Beam.h"
#include "Element.h"

using namespace std;

namespace vhc {

Beam::Beam(const Particle& referenceParticle, int quantity, int lambda):
		referenceParticle(referenceParticle),
		quantity(quantity),
		lambda(lambda) {}

Beam::~Beam() {
	clear();
}

void Beam::add(Particle* particle) {
	particles.push_back(particle);
	Publisher<ParticleAddedEvent>::publish(ParticleAddedEvent(this, particle));
}

void Beam::remove(Particle* particle) {
	Publisher<ParticleRemovedEvent>::publish(ParticleRemovedEvent(this, particle));
	delete particle;
	particle = NULL;
	particles.remove(particle);
}

Beam::ParticleCollection::iterator Beam::erase(Beam::ParticleCollection::iterator i) {
	Publisher<ParticleRemovedEvent>::publish(ParticleRemovedEvent(this, *i));
	delete *i;
	*i = NULL;
	return particles.erase(i);
}

void Beam::clear() {
	for (ParticleCollection::iterator i = particles.begin(); i != particles.end(); ++i) {
		i = erase(i);
		--i;
	}
	particles.clear();
}

int Beam::getQuantity() const {
	return quantity;
}

int Beam::getSize() const {
	return particles.size();
}

int Beam::getLambda() const {
	return lambda;
}

Particle& Beam::getReferenceParticle() {
	return referenceParticle;
}

Beam::ParticleCollection& Beam::getParticles() {return particles;}

const Beam::ParticleCollection& Beam::getParticles() const {return particles;}

void Beam::updateParticles() {
	for (ParticleCollection::iterator i = particles.begin(); i != particles.end(); ++i) {
		Particle& particle = **i;
		if (particle.getElement()->isAfter(particle)) {
			if (particle.getElement()->getNext() == NULL) {
				i = erase(i);
				--i;
				//cout << "Particle reached end of accelerator. Removed from simulation" << std::endl;
			} else particle.setElement(particle.getElement()->getNext());
		} else if (particle.getElement()->isBefore(particle)) {
			if (particle.getElement()->getPrevious() == NULL) {
				i = erase(i);
				--i;
				//cout << "Particle reached beginning of accelerator. Removed from simulation" << std::endl;
			} else particle.setElement(particle.getElement()->getPrevious());
		} else if (particle.getElement()->isBeside(particle)) {
			//std::cout << "Particle hit wall. Removed from simulation" << std::endl;
			i = erase(i);
			--i;
		}
	}
}

void Beam::step(double dt) {
	for (ParticleCollection::iterator i = particles.begin(); i != particles.end(); ++i) {
		Particle& particle = **i;

		particle.applyMagneticForce(particle.getElement()->magneticFieldAt(particle.getPosition()), dt);

		Vector3D a = particle.getForce() / (particle.getGamma() * particle.getMass());
		particle.setVelocity(particle.getVelocity() + a * dt);

		particle.translate(particle.getVelocity() * dt);

		particle.setForce(Vector3D::Null);
	}

	updateParticles();
}

double Beam::getVR2() const {
	double z2 = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		z2 += (**i).getPosition().getZ() * (**i).getPosition().getZ();
	}
	return sqrt(z2 / particles.size());
}

double Beam::getVV2() const {
	double v2 = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		v2 += (**i).getVelocity().getZ() * (**i).getVelocity().getZ();
	}
	return v2 / particles.size();
}

double Beam::getVRV2() const {
	double vz = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		vz += (**i).getPosition().getZ();
	}
	return (vz / particles.size()) * (vz / particles.size());
}

double Beam::getHR2() const {
	double r2 = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		Vector3D u = ((**i).getElement())->getHorizontalAt((**i).getPosition());
		r2 += (**i).getPosition().dot(u) * (**i).getPosition().dot(u);
	}
	return r2 / particles.size();
}

double Beam::getHV2() const {
	double v2 = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		Vector3D u = ((**i).getElement())->getHorizontalAt((**i).getPosition());
		v2 += (**i).getVelocity().dot(u) * (**i).getVelocity().dot(u);
	}
	return v2 / particles.size();
}

double Beam::getHRV2() const {
	double vr = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		Vector3D u = ((**i).getElement())->getHorizontalAt((**i).getPosition());
		vr += (**i).getPosition().dot(u) * (**i).getVelocity().dot(u);
	}
	return (vr / particles.size()) * (vr / particles.size());
}

double Beam::getAverageEnergy() const {
	double e = 0;
	for (list<Particle*>::const_iterator i = particles.begin(); i != particles.end(); ++i) {
		e += (**i).getEnergy();
	}
	return e / particles.size();
}

double Beam::getVerticalEmittance() const {
	return sqrt(getVR2() * getVV2() - getVRV2());
}

double Beam::getHorizontalEmittance() const {
	return sqrt(getHR2() * getHV2() - getHRV2());
}

double Beam::getVerticalA11() const {
	return getVR2() / getVerticalEmittance();
}

double Beam::getVerticalA12() const {
	return -getVRV2() / getVerticalEmittance();
}

double Beam::getVerticalA22() const {
	return getVV2() / getVerticalEmittance();
}

double Beam::getHorizontalA11() const {
	return getHR2() / getHorizontalEmittance();
}

double Beam::getHorizontalA12() const {
	return -getHRV2() / getVerticalEmittance();
}

double Beam::getHorizontalA22() const {
	return getHV2() / getHorizontalEmittance();
}

}
