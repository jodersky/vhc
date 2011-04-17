/*
 * ElementVisitor.h
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#ifndef ELEMENTVISITOR_H_
#define ELEMENTVISITOR_H_

namespace vhc {

class StraightElement;
class Quadrupole;
class Dipole;


class ElementVisitor {

public:
	ElementVisitor();
	virtual ~ElementVisitor();

	virtual void visit(const StraightElement* straight) const = 0;

	virtual void visit(const Quadrupole* quadrupole) const = 0;

	virtual void visit(const Dipole* dipole) const = 0;
};

}

#endif /* ELEMENTVISITOR_H_ */
