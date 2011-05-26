/*
 * ElementVisitor.h
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#ifndef ELEMENTVISITOR_H_
#define ELEMENTVISITOR_H_

namespace vhc {

class StraightElement; //forward declaration
class Quadrupole; //forward declaration
class Dipole; //forward declaration

/** Represente un visiteur d'elements.
 *  Le motif de conception des visiteurs est utilise pour ajouter des fonctionalites a des elements sans changer leur
 *  implementation. Il s'avere etre extremement utile pour des structures recursives, telles que les elements composees.
 *  @see http://fr.wikipedia.org/wiki/Visiteur_%28motif_de_conception%29 */
class ElementVisitor {

public:
	ElementVisitor();
	virtual ~ElementVisitor();

	/** Visite un element droit. */
	virtual void visit(const StraightElement* straight) const = 0;

	/** Visite un quadrupole. */
	virtual void visit(const Quadrupole* quadrupole) const = 0;

	/** Visite un dipole. */
	virtual void visit(const Dipole* dipole) const = 0;
};

}

#endif /* ELEMENTVISITOR_H_ */
