/*
 * ElementRenderer.h
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#ifndef ELEMENTRENDERER_H_
#define ELEMENTRENDERER_H_

#include <stdlib.h>
#include "ElementVisitor.h"

namespace vhc {


class ElementRenderer: public ElementVisitor {

private:
	static const int SLICES = 100;
	static const int STACKS_PER_LENGTH = 20;

public:

	ElementRenderer();

	virtual ~ElementRenderer();

	virtual void visit(StraightElement* straight);

	virtual void visit(Quadrupole* quadrupole);

	virtual void visit(Dipole* dipole);

};


}

#endif /* ELEMENTRENDERER_H_ */
