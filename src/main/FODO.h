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

class FODO: public CompositeElement {
	Quadrupole* focalisingQuadrupole;
	Quadrupole* defocalisingQuadrupole;
	StraightElement* straightElement1;
	StraightElement* straightElement2;

public:
	FODO(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double straightLength, double focalisingCoefficient,  Element* next = NULL);

	virtual ~FODO();
};

}

#endif /* FODO_H_ */
