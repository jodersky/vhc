/*
 * FODO.cc
 *
 *  Created on: Mar 29, 2011
 *      Author: jakob
 */

#include "FODO.h"
#include "CompositeElement.h"
#include "StraightElement.h"
#include "Quadrupole.h"
#include "Vector3D.h"
#include "exception.h"

namespace vhc {

FODO::FODO(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double straightLength, double focalisingCoefficient, Element* next):
	CompositeElement(entry, exit, sectionRadius, next),
	focalisingQuadrupole(NULL),
	defocalisingQuadrupole(NULL),
	straightElement1(NULL),
	straightElement2(NULL) {

	double L = straightLength;
	double l = getDiagonal().norm() / 2 - L;
	if (l < 0) throw IllegalArgumentException("Length of straight elements must be less than half of FODO length.");

	Vector3D d = getDiagonal().unit();
	focalisingQuadrupole = new Quadrupole(entry, entry + d * l, sectionRadius, focalisingCoefficient);
	elements.push_back(focalisingQuadrupole);
	straightElement1 = new StraightElement(focalisingQuadrupole->getExitPosition(), focalisingQuadrupole->getExitPosition() + d * L, sectionRadius);
	elements.push_back(straightElement1);
	defocalisingQuadrupole = new Quadrupole(straightElement1->getExitPosition(), straightElement1->getExitPosition() + d * l, sectionRadius, -focalisingCoefficient);
	elements.push_back(defocalisingQuadrupole);
	straightElement2 = new StraightElement(defocalisingQuadrupole->getExitPosition(), defocalisingQuadrupole->getExitPosition() + d * L, sectionRadius);
	elements.push_back(straightElement2);

	//connection des elements
	for (int i(0); i < elements.size() - 1; i++) {
		elements[i]->setNext(elements[i+1]);
	}

}

FODO::~FODO() {
	for (int i(0); i < elements.size(); i++) {
		delete elements[i];
		elements[i] = NULL;
	}
}

}
