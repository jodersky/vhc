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

class Accelerator {
protected:
	vector <Element> elementCollec;
	vector <Particle> particleCollec;
public:

	/* Constructeur d'un accélérateur.
	 * Todo améliorer l'instanciation des attributs à l'aide d'une fonction. */
	Accelerator (const vector<Element>& eCollec, const vector<Particle>& pCollec):
		elementCollec=eCollec,
		particle=pCollec
	{};

	/* Retourne un pointeur sur un élément de l'accélérateur,
	 * il n'y a pas besoin d'avoir l'élément lui-même.
	 * Question : où mettre le 'delete' ? */
	Element* getElement (int rank) const { return elementCollec[rank-1]; }

	/* Retourne un pointeur sur une particule de l'accélérateur,
	 * il n'y a pas besoin d'avoir la particule elle-même.
	 * Question : où mettre le 'delete' ? */
	Particle* getParticle(int matricle) const { return particleCollec[matricle-1]; }
};

}

#endif /* ACCELERATOR_H_ */
