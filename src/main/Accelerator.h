/*
 * Accelerator.h
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
#include <iostream>
#include <vector>
#include "exceptions.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

/** Représente un accélérateur. Cette classe contient en particulier une méthode
 *  qui fait évoluer les particules qu'elle contient. */
class Accelerator {
private :

	/** Constructeur de copie ne faisant rien. */
	Accelerator (Accelerator const& other) {}

	/** Opérateur '=' ne faisant rien. */
	void operator= (Accelerator const& other) const {}

protected:

	/** Attributs d'un accélérateur : une collection d'éléments, et une de particules. */
	std::vector< Element* > elementCollec;
	std::vector< Particle* > particleCollec;

public:

	/** Constructeur d'un accélérateur. */
	Accelerator ():
		elementCollec(0),
		particleCollec(0)
	{};

	virtual ~Accelerator() {clear();}

	/** Retourne un pointeur sur un élément de l'accélérateur.*/
	Element* getElement(int rank) const { return elementCollec[rank]; }

	/* Retourne un pointeur sur une particule de l'accélérateur.*/
	Particle* getParticle(int rank) const { return particleCollec[rank];}

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;

	/** Copie un élément dans l'accélérateur. */
	Element* add(const Element& element) {
		Element* e = element.clone();
		elementCollec.push_back(e);
		return e;
	}

	/** Copie une particule dans l'accélérateur. */
	Particle* add(const Particle& particle){
		Particle* p = particle.clone();
		particleCollec.push_back(p);
		return p;
	}

	/** Efface tous les éléments et les particules. */
	void clear() {
		for (unsigned int i = 0; i < particleCollec.size(); ++i) {
			delete particleCollec[i];
			particleCollec[i] = NULL;
		}
		particleCollec.clear();

		for (unsigned int i = 0; i < elementCollec.size(); ++i) {
			delete elementCollec[i];
			elementCollec[i] = NULL;
		}
		elementCollec.clear();
	}

	/** Retourne la liste des éléments de l'accélérateur.*/
	const std::vector< Element* >& getElements() const {
		return elementCollec;
	}

	/** Retourne la liste des particules de l'accélérateur.*/
	const std::vector< Particle* >& getParticles() const {
		return particleCollec;
	}


	/** Fait évoluer l'accélérateur d'un laps de temps dt. */
	void step(double dt) {

		for (int i = 0; i < particleCollec.size(); ++i) {
			Particle* particle = particleCollec[i];

			particle->applyMagneticForce(particle->getElement()->magneticFieldAt(particle->getPosition()), dt);

			Vector3D a = particle->getForce() / (particle->getGamma() * particle->getMass());
			particle->setVelocity(particle->getVelocity() + a * dt);
		}



		for (int i = 0; i < particleCollec.size(); ++i) {
			Particle& particle = *(particleCollec[i]);
			particle.setPosition(particle.getPosition() + particle.getVelocity() * dt);
			particle.setForce(Vector3D::Null);

			if (particle.getElement()->hasHit(particle)) std::cout << "Particle hit wall!" << std::endl;
			if (particle.getElement()->isPast(particle)) { // si la particule est passee, qui sait si elle est dans l'element suivant?
				if (!particle.getElement()->isConnected()) throw Exception("Element in accelerator not connected.");
				else particle.setElement(particle.getElement()->getNext());
			}
		}

	}


};

}

#endif /* ACCELERATOR_H_ */
