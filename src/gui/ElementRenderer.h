/*
 * ElementRenderer.h
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#ifndef ELEMENTRENDERER_H_
#define ELEMENTRENDERER_H_

#include "ElementVisitor.h"

namespace vhc {


class ElementRenderer: public ElementVisitor {

public:

	ElementRenderer();

	virtual ~ElementRenderer();

	virtual void visit(StraightElement* straight);

	virtual void visit(Quadrupole* quadrupole);

	virtual void visit(CurvedElement* curved);

	virtual void visit(Dipole* dipole);

};


}

#endif /* ELEMENTRENDERER_H_ */
