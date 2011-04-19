/*
 * FODO.h
 *
 *  Created on: Mar 29, 2011
 *      Author: jakob
 */

#ifndef FODO_H_
#define FODO_H_

#include "Quadrupole.h"
#include "CompositeElement.h"
#include "Vector3D.h"

namespace vhc {

/** Représente une maille FODO, qui est un composé d'éléments constitué
 * 		-d'un quadrupole focalisant;
 * 		-de deux éléments droits;
 * 		-à la sortie, d'un quadrupole défocalisant. */
class FODO: public CompositeElement {

private:
	double straightLength;
	double focalizingCoefficient;
	Quadrupole* focalizingQuadrupole;
	Quadrupole* defocalizingQuadrupole;
	StraightElement* straightElement1;
	StraightElement* straightElement2;

public:
	/** Constructeur d'une maille FODO.*/
	FODO(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double straightLength, double focalizingCoefficient,  Element* next = NULL);

	/** Destructeur virtuel.*/
	virtual ~FODO();

	// TODO expl.
	virtual FODO* clone() const;
};

}

#endif /* FODO_H_ */
