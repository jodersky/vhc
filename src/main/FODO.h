/*
 * FODO.h
 *
 *  Created on: Mar 29, 2011
 *      Author: jakob
 */

#ifndef FODO_H_
#define FODO_H_

#include <string>
#include "Quadrupole.h"
#include "CompositeElement.h"
#include "Vector3D.h"

namespace vhc {

/** Représente une maille FODO, qui est un élément magnétique droit, composé d'un quadrupôle, d'une section droite, d'un autre quadrupôle «opposé», et d'une autre section droite.
 */
class FODO: public CompositeElement {

private:
	double straightLength;
	double focalizingCoefficient;
	Quadrupole* focalizingQuadrupole;
	Quadrupole* defocalizingQuadrupole;
	StraightElement* straightElement1;
	StraightElement* straightElement2;

public:
	FODO(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double straightLength, double focalizingCoefficient,  Element* next = NULL);

	virtual ~FODO();

	virtual std::string getType() const;

	virtual FODO* clone() const;
};

}

#endif /* FODO_H_ */
