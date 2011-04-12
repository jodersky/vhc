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
	Particle* getParticle(int rank) const { return particleCollec[rank-1]; rank}

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;

	// TODO ou va le delete ?
	/** Ajoute un élément (non spécifié) à l'accélérateur. */
	void addElement() {
		ptr = new Element;
		elementCollec.push_back(ptr);
	}

	// TODO où va le delete?
	// TODO instanciation légale?
	/** Instancie une particule et l'ajoute à l'accélérateur. */
	void addParticle(){
		ptr = new Particle(newPart);
		particleCollec.push_back(ptr);
	}

	/** Efface tous les éléments (et les particules, logique). */
	void killAllElements(){
		for (vector<Element*>::iterator i(elementCollec.begin()); i != elementCollec.end(); ++i)
			elementCollec.erase(i);
		killAllParticles();
	}

	/** Efface toutes les particules. */
	void killAllParticles(){
		for (vector<Particle*>::iterator i(particleCollec.begin()); i != particleCollec.end(); ++i)
			particleCollec.erase(i);
	}

	/** Fait évoluer l'accélérateur (pas de temps fixe). */
	void step(){
		accelerator.bouge();
	}


};

}

#endif /* ACCELERATOR_H_ */
