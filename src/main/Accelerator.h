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
#include <limits>
#include "exceptions.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

/** Représente un accélérateur. Cette classe contient en particulier une méthode
 *  qui fait évoluer les particules qu'elle contient. */
class Accelerator: public Printable{
private :

	/** Constructeur de copie ne faisant rien. */
	Accelerator (Accelerator const& other) {}

	/** Opérateur '=' ne faisant rien. */
	void operator= (Accelerator const& other) const {}

protected:

	/*Attributs d'un accélérateur : une collection d'éléments, et une de particules. */

	/** Collection d'elements contenus dans cet accelerateur. */
	std::vector< Element * > elementCollec;

	/** Collection de particules contenus danc cet accelerateur. */
	std::vector< Particle *> particleCollec;

public:

	/** Constructeur d'un accélérateur. */
	Accelerator ():
		elementCollec(0),
		particleCollec(0)
	{};

	virtual ~Accelerator() {clear();}

	/** Retourne un pointeur sur un élément de l'accélérateur.*/
	Element *const getElement(int rank) const { return elementCollec[rank];}

	/* Retourne un pointeur sur une particule de l'accélérateur.*/
	Particle *const getParticle(int rank) const { return particleCollec[rank];}

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;

	/** Copie un élément dans l'accélérateur. */
	Element *const add(const Element& element) {
		Element* e = element.clone();
		elementCollec.push_back(e);
		return e;
	}

	/** Copie une particule dans l'accélérateur. */
	Particle *const add(const Particle& particle){
		Particle* p = particle.clone();
		particleCollec.push_back(p);
		return p;
	}

	/** Ferme l'accelerateur. */
	void close() {
		for (int i = 0; i < elementCollec.size(); ++i) {
			//element i
			Element* current = elementCollec[i];

			//element i+1
			Element* next = elementCollec[(i+1) % elementCollec.size()];

			// est-ce que les elements se suivent?
			if (Vector3D::ae(current->getExitPosition(), next->getEntryPosition())) {
				current->setNext(next);
				next->setPrevious(current);
			} else throw UnsupportedOperationException("Cannot close accelerator. Two succeeding elements are not physically connected! (not close enough)");
		}


		//rajouter les particules dans leurs elements respectifs
		for (int i = 0; i < particleCollec.size(); ++i) {

			for (int j = 0; j < elementCollec.size(); ++j) {

				if (elementCollec[j]->contains(*particleCollec[i])) {
					particleCollec[i]->setElement(elementCollec[j]);
					break;
				}
			}

			//si une particule n'est pas contenue dans un element elle est supprimee
			if (particleCollec[i]->getElement() == NULL) {
				delete particleCollec[i];
				particleCollec[i] = particleCollec[particleCollec.size() - 1];
				particleCollec.pop_back();
				--i;
			}

		}

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
			Particle& particle = *particleCollec[i];

			particle.applyMagneticForce(particle.getElement()->magneticFieldAt(particle.getPosition()), dt);

			Vector3D a = particle.getForce() / (particle.getGamma() * particle.getMass());
			particle.setVelocity(particle.getVelocity() + a * dt);

			particle.setPosition(particle.getPosition() + particle.getVelocity() * dt);
			particle.setForce(Vector3D::Null);

			//if (particle.getElement()->isBeside(particle)) std::cout << "Particle hit wall!" << std::endl;
			if (particle.getElement()->isAfter(particle)) { // si la particule est passee, qui sait si elle est dans l'element suivant?
				if (!particle.getElement()->isConnected()) throw Exception("Element in accelerator not connected.");
				else particle.setElement(particle.getElement()->getNext());
			}
		}

	}

	/*
	void* stepMonteCarlo();

	void* stepDeterministBackUp();

	void* stepDeterminist();
*/
};

}

#endif /* ACCELERATOR_H_ */
