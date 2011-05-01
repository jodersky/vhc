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

Element& Accelerator::add(const Element& element) {
	Element* e = element.clone();
	elementCollec.push_back(e);
	return *e;
}

Particle& Accelerator::add(const Particle& particle) {
	Particle* p = particle.clone();
	particleCollec.push_back(p);
	return *p;
}

const list<Element*>& Accelerator::getElements() const { return elementCollec;}

const list<Particle*>& Accelerator::getParticles() const { return particleCollec;}

void Accelerator::close() {
	for (list<Element*>::iterator current = elementCollec.begin(); current != elementCollec.end(); ++current) {

		list<Element*>::iterator next = current;
		++next;
		if (next == elementCollec.end()) next = elementCollec.begin();


		// est-ce que les elements se suivent?
		if (Vector3D::ae((*current)->getExitPosition(), (*next)->getEntryPosition())) {
			(**current).setNext(*next);
			(**next).setPrevious(*current);
		} else
			throw UnsupportedOperationException("Cannot close accelerator. Two succeeding elements are not physically connected! (not close enough)");
	}

	//rajouter les particules dans leurs elements respectifs
	for (list<Particle*>::iterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {

		for (list<Element*>::iterator j = elementCollec.begin(); j != elementCollec.end(); ++j) {
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
			std::cout << "Particle hit wall. Removed from simulation" << std::endl;
		}

	}

}


void Accelerator::updateParticles() {
	for (list<Particle*>::iterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
		Particle& particle = **i;
		if (particle.getElement()->isBeside(particle)) {
			std::cout << "Particle hit wall. Removed from simulation" << std::endl;
			delete *i;
			i = particleCollec.erase(i);
			--i;
		} else if (particle.getElement()->isAfter(particle)) {
			if (particle.getElement()->getNext() == NULL) throw Exception("Element in accelerator not connected to next.");
			else particle.setElement(particle.getElement()->getNext());
		} else if (particle.getElement()->isBefore(particle)) {
			if (particle.getElement()->getPrevious() == NULL) throw Exception("Element in accelerator not connected to previous.");
			else particle.setElement(particle.getElement()->getPrevious());
		}
	}
}

void Accelerator::clear() {
	for (list<Particle*>::iterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	particleCollec.clear();

	for (list<Element*>::iterator i = elementCollec.begin(); i != elementCollec.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	elementCollec.clear();
}

void Accelerator::step(double dt) {

	for (list<Particle*>::iterator i = particleCollec.begin(); i != particleCollec.end(); ++i) {
		Particle& particle = **i;

		particle.applyMagneticForce(particle.getElement()->magneticFieldAt(particle.getPosition()), dt);

		Vector3D a = particle.getForce() / (particle.getGamma() * particle.getMass());
		particle.setVelocity(particle.getVelocity() + a * dt);

		particle.translate(particle.getVelocity() * dt);
		particle.setForce(Vector3D::Null);
	}


	updateParticles();
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
		for (list<Element*>::const_iterator i = elementCollec.begin(); i != elementCollec.end(); ++i) {
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
