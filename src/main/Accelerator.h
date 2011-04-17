/*
 * Accelerator.h
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
#include <vector>
#include "Vector3D.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

// TODO Do we need any destructor ?
class Accelerator {
private :

	/** Constructeur de copie ne faisant rien. */
	Accelerator (Accelerator const& other) {}

	/** Opérateur '=' ne faisant rien. */
	void operator= (Accelerator const& other) const {}

protected:

	/* Attributs d'un accélérateur : une collection d'éléments, et une de particules. */
	std::vector< Element* > elementCollec;
	std::vector< Particle* > particleCollec;

public:

	/** Constructeur d'un accélérateur. */
	// Pour l'instant j'ai décidé que l'accélérateur possède deux containers (cf. slide35)
	Accelerator ():
		elementCollec(0),
		particleCollec(0)
	{};

	virtual ~Accelerator() {clear();}

	/* Retourne un pointeur sur un élément de l'accélérateur,
	 * il n'y a pas besoin d'avoir l'élément lui-même.
	 * Question : où mettre le 'delete' ? */
	Element* getElement(int rank) const { return elementCollec[rank]; }

	/* Retourne un pointeur sur une particule de l'accélérateur,
	 * il n'y a pas besoin d'avoir la particule elle-même.
	 * Question : où mettre le 'delete' ? */
	Particle* getParticle(int rank) const { return particleCollec[rank];}

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;

	/** Copie un élément dans l'accélérateur. */
	void add(const Element& element) {
		elementCollec.push_back(element.clone());
	}

	/** Copie une particule dans l'accélérateur. */
	void add(const Particle& particle){
		particleCollec.push_back(particle.clone());
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

	const std::vector< Element* >& getElements() const {
		return elementCollec;
	}

	const std::vector< Particle* >& getParticles() const {
		return particleCollec;
	}


	/** Fait évoluer l'accélérateur d'un lapse de temps dt. */
	void step(double dt) {

		for (int i = 0; i < particleCollec.size(); ++i) {
			Particle& particle = *(particleCollec[i]);
			particle.applyMagneticForce(particle.getElement()->magneticFieldAt(particle.getPosition()), dt);

			Vector3D a = particle.getForce() / (particle.getGamma() * particle.getMass());
			particle.setVelocity(particle.getVelocity() + a * dt);
		}

		for (int i = 0; i < particleCollec.size(); ++i) {
			Particle& particle = *(particleCollec[i]);
			particle.setPosition(particle.getPosition() + particle.getVelocity() * dt);
			particle.setForce(Vector3D::Null);
		}

	}


};

}

#endif /* ACCELERATOR_H_ */
