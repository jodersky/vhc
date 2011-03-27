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
	Accelerator (Accelerator const& autre) {}

	/** Opérateur '=' ne faisant rien. */
	bool operator= (Accelerator const& autre) const {}

protected:

	/** Attributs d'un accélérateur : une collection d'éléments, et une de particules. */
	std::vector< Element* > elementCollec;
	std::vector< Particle* > particleCollec;

public:

	/** Constructeur d'un accélérateur. */
	// Pour l'instant j'ai décidé que l'accélérateur possède deux containers (cf. slide35)
	Accelerator ():
		elementCollec(0),
		particleCollec(0)
	{};

	/* Retourne un pointeur sur un élément de l'accélérateur,
	 * il n'y a pas besoin d'avoir l'élément lui-même.
	 * Question : où mettre le 'delete' ? */
	Element* getElement (int rank) const { return elementCollec[rank-1]; }

	/* Retourne un pointeur sur une particule de l'accélérateur,
	 * il n'y a pas besoin d'avoir la particule elle-même.
	 * Question : où mettre le 'delete' ? */
	Particle* getParticle(int rank) const { return particleCollec[rank-1]; }

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;

	// TODO méthodes demandées dans la consigne
	/** Ajoute un élément à l'accélérateur. */
	void addElement();

	/** Ajoute une particule à l'accélérateur. */
	void addParticle();

	/** Efface tous les éléments. */
	void killAllElements();

	/** Efface toutes les particules. */
	void KillAllParticles();

	/** Fait évoluer l'accélérateur. */
	void play();


};

}

#endif /* ACCELERATOR_H_ */
