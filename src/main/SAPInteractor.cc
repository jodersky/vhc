/*
 * SAPInteractor.cc
 *
 *  Created on: May 29, 2011
 *      Author: jakob
 */

#include <iostream>
#include <algorithm>
#include <math.h>
#include "SAPInteractor.h"
#include "Accelerator.h"
#include "Vector3D.h"

using namespace std;

namespace vhc {

SAPInteractor::LinearParticleContainer::LinearParticleContainer(Particle *const particle, double linear): particle(particle), linear(linear) {};

Particle *const SAPInteractor::LinearParticleContainer::getParticle() const {return particle;}

void SAPInteractor::LinearParticleContainer::setLinear(double value) {linear = value;}

double SAPInteractor::LinearParticleContainer::getLinear() const {return linear;}

SAPInteractor::SAPInteractor() {}

SAPInteractor::~SAPInteractor() {}

const double SAPInteractor::DEFAULT_INTERACTION_RADIUS = 3E-6;

double SAPInteractor::getInteractionRadius() const {return interactionRadius;}

void SAPInteractor::setInteractionRadius(double value) {interactionRadius = value;}

void SAPInteractor::acceleratorClosed(const Accelerator& acc) {
	//compteur de position lineaire
	double linear = 0;

	//elements
	const Accelerator::ElementCollection& elements = acc.getElements();

	//linearistaion des elements
	for (Accelerator::ElementCollection::const_iterator i = elements.begin(); i != elements.end(); ++i) {
		elementLinears.insert(pair<Element*, double>(*i, linear));
		linear += (**i).getDiagonal().norm();
	}
}


void SAPInteractor::react(const ParticleAddedEvent& event) {
	particles.push_back(new LinearParticleContainer(event.getParticle()));
}

void SAPInteractor::react(const ParticleRemovedEvent& event) {
	for (int i = 0; i < particles.size(); ++i) {
		if (particles[i]->getParticle() == event.getParticle()) {
			LinearParticleContainer* p = particles[i];
			particles[i] = particles.back();
			particles[particles.size() - 1] = p;
			delete particles.back();
			particles.pop_back();
			break;
		}
	}
}

void SAPInteractor::applyInteractions() {

	if (particles.size() == 0) return;

	//les particules sont linearises
	linearizeParticles();

	//les particules sont tries selon leur position lineaire [complexite O(N log N)]
	sort(particles.begin(), particles.end(), vhc::SAPInteractor::compare);

	for (int i = 0; i < particles.size(); ++i) {
		for (int j = i + i; j < particles.size(); ++j) {

			//comme les particules sont tries selon leur projection, si la deuxieme est plus loin de la premiere,
			//on sait que tous les autres le seront aussi, on arrete donc la recherche ici
			if (particles[j]->getLinear() + interactionRadius > particles[i]->getLinear() - interactionRadius) break;

			//sinon, si leur distance est plus petite que le rayon d'interaction, on applique un force d'interaction
			else if (fabs(particles[j]->getLinear() - particles[i]->getLinear()) <= interactionRadius) {
				Particle& p1 = *(particles[i]->getParticle());
				Particle& p2 = *(particles[j]->getParticle());

				double r = (p2.getPosition() - p1.getPosition()).norm();
				if (r != 0) {
					Vector3D d = (p2.getPosition() - p1.getPosition()).unit();
					Vector3D force = d * p1.getCharge() * p1.getCharge() /
							(4 * M_PI * constants::EPSILON_ZERO * r * r * r * p1.getGamma() * p1.getGamma());
					p1.applyForce(force);
					p2.applyForce(-force);
				}
			}
		}
	}

}

void SAPInteractor::linearizeParticles() {
	for (vector<LinearParticleContainer*>::iterator i = particles.begin(); i != particles.end(); ++i) {

		//element de la particule
		Element* element = (**i).getParticle()->getElement();

		LinearParticleContainer* p = (*i);

		//position locale de la particule a l'entree de son element
		Vector3D local = (**i).getParticle()->getPosition() - element->getEntryPosition();

		//projection de la particule sur la diagonale de l'element
		double proj = (element->getDiagonal().unit()).dot(local);

		//la position lineaire de l'element est donne par la projection locale plus la position lineaire de son element
		(**i).setLinear(elementLinears.find(element)->second + proj);


	}
}

bool SAPInteractor::compare(LinearParticleContainer *const p1, LinearParticleContainer *const p2) {
	return p1->getLinear() < p2->getLinear();
}

}
