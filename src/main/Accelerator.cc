/*
 * Accelerator.cc
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#include <iostream>
#include "Accelerator.h"
#include "exceptions.h"
#include "SingleBeam.h"
#include "BruteForceInteractor.h"

using namespace std;

namespace vhc {

Accelerator::Accelerator(): elements(0), beams(0), allowLinear(false), closed(false), interactor(new BruteForceInteractor) {};

Accelerator::Accelerator(Interactor* interactor):
		elements(0),
		beams(0),
		allowLinear(false),
		closed(false),
		interactor(interactor) {}

Accelerator::~Accelerator() {
	clear();
}

void Accelerator::initializeBeams() {
	//pour chauqe faisceau (vide a priori)
	for (BeamCollection::iterator i = beams.begin(); i != beams.end(); ++i) {

		(**i).getReferenceParticle().setElement(NULL);

		//rajouter les particules de reference dans leurs elements respectifs
		for (ElementIterator j = elements.begin(); j != elements.end(); ++j) {
			if ((**j).contains((**i).getReferenceParticle())) {
				(**i).getReferenceParticle().setElement(*j);
				break;
			}
		}

		//si une particule de reference n'est pas contenue dans un element le faisceau est supprimee
		//et une exception est lancee
		if ((**i).getReferenceParticle().getElement() == NULL) {
			delete *i;
			i = beams.erase(i);
			--i;
		} else {
			//sinon, le faisceau est initialise
			(**i).clear();
			(**i).initializeParticles();

			//mettre chaque particule dans l'element respectif
			for (ParticleCollection::iterator j = (**i).getParticles().begin(); j != (**i).getParticles().end(); ++j) {
				(**j).setElement(NULL);
				for (ElementIterator k = elements.begin(); k != elements.end(); ++k) {
					if ((**k).contains(**j)) {
						(**j).setElement(*k);
						break;
					}
				}

				//supprimer la particule si elle n'est pas contenue dans un element
				if ((**j).getElement() == NULL) {
					delete *j;
					j = (**i).getParticles().erase(j);
					--j;
				}
			}
		}

	}
}


Element& Accelerator::add(const Element& element) {
	Element* e = element.clone();
	elements.push_back(e);
	closed = false;
	return *e;
}

Beam& Accelerator::add(const Beam& beam) {
	Beam* b = beam.clone();
	beams.push_back(b);
	b->Publisher<ParticleAddedEvent>::subscribe(interactor);
	b->Publisher<ParticleRemovedEvent>::subscribe(interactor);
	closed = false;
	return *b;
}

Beam& Accelerator::add(const Particle& particle) {
	return add(SingleBeam(particle));
}

const Accelerator::ElementCollection& Accelerator::getElements() const {
	return elements;
}

const Accelerator::BeamCollection& Accelerator::getBeams() const {
	return beams;
}

auto_ptr<Accelerator::ParticleCollection> Accelerator::getParticles() const {
	auto_ptr<ParticleCollection> particles(new ParticleCollection(0));
	for (BeamCollection::const_iterator i = beams.begin(); i != beams.end(); ++i) {
		particles->insert(particles->end(), (**i).getParticles().begin(), (**i).getParticles().end());
	}
	return particles;
}

void Accelerator::close() {
	for (ElementIterator current = elements.begin(); current != elements.end(); ++current) {

		ElementIterator next = current;
		++next;
		if (next == elements.end()) next = elements.begin();


		// est-ce que les elements se suivent (sont connectes)?
		if (Vector3D::ae((*current)->getExitPosition(), (*next)->getEntryPosition())) {
			(**current).setNext(*next);
			(**next).setPrevious(*current);

		//sinon est-ce qu'il s'agit du dernier element?
		} else if (next == elements.begin()) {
			if (!allowLinear) throw UnsupportedOperationException("Cannot close accelerator. Linear Accelerators are not allowed.");

		//sinon
		} else throw UnsupportedOperationException("Cannot close accelerator. Two succeeding elements are not physically connected. (not close enough)");
	}

	initializeBeams();
	interactor->acceleratorClosed(*this);

	closed = true;

}

void Accelerator::clear() {
	for (BeamCollection::iterator i = beams.begin(); i != beams.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	beams.clear();

	for (ElementCollection::iterator i = elements.begin(); i != elements.end(); ++i) {
		delete *i;
		*i = NULL;
	}
	elements.clear();

	closed = false;
}

void Accelerator::step(double dt) {
	if (!closed) close();

	interactor->applyInteractions();

	for (BeamCollection::iterator i = beams.begin(); i != beams.end(); ++i) {
		(**i).step(dt);
	}
}

void Accelerator::enableLinear(bool value) {
	allowLinear = value;
}

/** Cf. Accelerator.h */
std::string Accelerator::toString() const {
	std::stringstream s;

	if (elements.size() == 0) {
		s << "This accelerator doesn't contain anything."<<"\n";
	} else if (elements.size()==1) {
		s << "This accelerator is made of the following element :" << "\n";
		s << elements.front()->toString()<<"\n";
	} else {
		s << "This accelerator is made of the " << elements.size() << " following elements :" << "\n";
		for (ElementCollection::const_iterator i = elements.begin(); i != elements.end(); ++i) {
			s << (*i)->toString() << "\n";
		}
	}

	auto_ptr<ParticleCollection> particles = getParticles();

	if (particles->size() == 0) {
		s << "This accelerator doesn't contain any particle." << "\n";
	} else if (particles->size() == 1) {
		s << "This accelerator contains the following particle :" << "\n";
		s << particles->front()->toString() << "\n";
	}else{
		s << "This accelerator contains the " << particles->size() << " following particles :"<<"\n";
		for (ParticleCollection::const_iterator i = particles->begin(); i != particles->end(); ++i) {
					s << (**i).toString() << "\n";
		}
	}

	return s.str();
}


} //vhc
