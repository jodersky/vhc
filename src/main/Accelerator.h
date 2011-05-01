/*
 * Accelerator.h
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
#include <list>
#include "Vector3D.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

/** Représente un accélérateur. Cette classe contient en particulier une méthode
 *  qui fait évoluer les particules qu'elle contient. */
class Accelerator: public Printable {
private :

	/** Constructeur de copie ne faisant rien. */
	Accelerator (Accelerator const& other) {}

	/** Opérateur '=' ne faisant rien. */
	void operator= (Accelerator const& other) {}

protected:

	/** Collection d'elements contenus dans cet accelerateur. */
	std::list< Element * > elementCollec;

	/** Collection de particules contenus danc cet accelerateur. */
	std::list< Particle *> particleCollec;


public:

	/** Constructeur d'un accélérateur. */
	Accelerator ():
		elementCollec(0),
		particleCollec(0)
	{};

	virtual ~Accelerator() {clear();}

	/** Copie un élément dans l'accélérateur. */
	Element& add(const Element& element);

	/** Copie une particule dans l'accélérateur. */
	Particle& add(const Particle& particle);

	/** Retourne la liste d'elements contenus dans cet accelerateur. */
	const std::list<Element*> & getElements() const;

	/** Retourne la liste des particules contenus dans cet accelerateur. */
	const std::list<Particle*> & getParticles() const;

	/** Ferme l'accelerateur. */
	void close();

	/** Efface tous les éléments et les particules. */
	void clear();

	void updateParticles();

	/** Fait évoluer l'accélérateur d'un laps de temps dt. */
	void step(double dt);

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;
};

}

#endif /* ACCELERATOR_H_ */
