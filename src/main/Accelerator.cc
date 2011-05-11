/*
 * Accelerator.cc
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#include <iostream>
#include "Accelerator.h"
#include "exceptions.h"

using namespace std;

namespace vhc {

Accelerator::Accelerator():
		elementCollec(0),
		particleCollec(0),
		allowLinear(false),
		closed(false)
	{};

Accelerator::~Accelerator() {
	clear();
}

void Accelerator::initializeParticles() {
	//rajouter les particules dans leurs elements respectifs
	for (ParticleIterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {

		for (ElementIterator j = elementCollec.begin(); j != elementCollec.end(); ++j) {
			if ((**j).contains(**i)) {
				(**i).setElement(*j);
				break;
			}
		}

		//si une particule n'est pas contenue dans un element elle est supprimee
		if ((**i).getElement() == NULL) {
			delete *i;
			i = particleCollec.erase(i);
			--i;
			//std::cout << "Particle hit wall. Removed from simulation" << std::endl;
		}
	}
}

Element& Accelerator::add(const Element& element) {
	Element* e = element.clone();
	elementCollec.push_back(e);
	closed = false;
	return *e;
}

Particle& Accelerator::add(const Particle& particle) {
	Particle* p = particle.clone();
	particleCollec.push_back(p);
	closed = false;
	return *p;
}

const Accelerator::ElementCollection& Accelerator::getElements() const { return elementCollec;}

const Accelerator::ParticleCollection& Accelerator::getParticles() const { return particleCollec;}

void Accelerator::close() {
	for (ElementIterator current = elementCollec.begin(); current != elementCollec.end(); ++current) {

		ElementIterator next = current;
		++next;
		if (next == elementCollec.end()) next = elementCollec.begin();


		// est-ce que les elements se suivent (sont connectes)?
		if (Vector3D::ae((*current)->getExitPosition(), (*next)->getEntryPosition())) {
			(**current).setNext(*next);
			(**next).setPrevious(*current);

		//sinon est-ce qu'il s'agit du dernier element?
		} else if (next == elementCollec.begin()) {
			if (!allowLinear) throw UnsupportedOperationException("Cannot close accelerator. Linear Accelerators are not allowed.");

		//sinon
		} else throw UnsupportedOperationException("Cannot close accelerator. Two succeeding elements are not physically connected. (not close enough)");
	}

	initializeParticles();

	closed = true;

}

void Accelerator::updateParticles() {
	for (ParticleIterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
		Particle& particle = **i;
		if (particle.getElement()->isAfter(particle)) {
			if (particle.getElement()->getNext() == NULL)
				if (allowLinear) {
					delete *i;
					i = particleCollec.erase(i);
					--i;
					//cout << "Particle reached end of accelerator. Removed from simulation" << std::endl;
				}
				else throw Exception("Element in accelerator not connected to next.");
			else particle.setElement(particle.getElement()->getNext());
		} else if (particle.getElement()->isBefore(particle)) {
			if (particle.getElement()->getPrevious() == NULL)
				if (allowLinear) {
					delete *i;
					i = particleCollec.erase(i);
					--i;
					//cout << "Particle reached beginning of accelerator. Removed from simulation" << std::endl;
				}
				else throw Exception("Element in accelerator not connected to previous.");
			else particle.setElement(particle.getElement()->getPrevious());
		} else if (particle.getElement()->isBeside(particle)) {
			//std::cout << "Particle hit wall. Removed from simulation" << std::endl;
			delete *i;
			i = particleCollec.erase(i);
			--i;
		}
	}
}

void Accelerator::clear() {
	for (ParticleIterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	particleCollec.clear();

	for (ElementIterator i = elementCollec.begin(); i != elementCollec.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	elementCollec.clear();

	closed = false;
}

void Accelerator::step(double dt) {
	if (!closed) close();

	for (ParticleIterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
		Particle& particle = **i;

		particle.setForce(Vector3D::Null);

		particle.applyMagneticForce(particle.getElement()->magneticFieldAt(particle.getPosition()), dt);

		Vector3D a = particle.getForce() / (particle.getGamma() * particle.getMass());
		particle.setVelocity(particle.getVelocity() + a * dt);

		particle.translate(particle.getVelocity() * dt);

	}


	updateParticles();
}

void Accelerator::enableLinear(bool value) {
	allowLinear = value;
}

/** Cf. Accelerator.h */
std::string Accelerator::toString() const {
	std::stringstream s;

	if (elementCollec.size() == 0) {
		s << "This accelerator doesn't contain anything."<<"\n";
	} else if (elementCollec.size()==1) {
		s << "This accelerator is made of the following element :" << "\n";
		s << elementCollec.front()->toString()<<"\n";
	} else {
		s << "This accelerator is made of the " << elementCollec.size() << " following elements :" << "\n";
		for (ElementCollection::const_iterator i = elementCollec.begin(); i != elementCollec.end(); ++i) {
			s << (*i)->toString() << "\n";
		}
	}

	if (particleCollec.size() == 0) {
		s << "This accelerator doesn't contain any particle." << "\n";
	} else if (particleCollec.size() == 1) {
		s << "This accelerator contains the following particle :" << "\n";
		s << particleCollec.front()->toString() << "\n";
	}else{
		s << "This accelerator contains the " << particleCollec.size() << " following particles :"<<"\n";
		for (list<Particle*>::const_iterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
					s << (*i)->toString() << "\n";
		}
	}

	return s.str();
}

} //vhc
