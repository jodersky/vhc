/*
 * ElementRenderer.h
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#ifndef ELEMENTRENDERER_H_
#define ELEMENTRENDERER_H_

#include "Renderer.h"
#include "ElementVisitor.h"
#include "Element.h"

namespace vhc {


class ElementRenderer: public ElementVisitor, public Renderer<Element> {

private:
	static const int SLICES = 100;
	static const int STACKS_PER_LENGTH = 20;

	void drawStraight(const StraightElement* straight) const;

public:

	ElementRenderer();

	virtual ~ElementRenderer();

	virtual void render(const Element& element) const;

	virtual void visit(const StraightElement* straight) const ;

	virtual void visit(const Quadrupole* quadrupole) const;

	virtual void visit(const Dipole* dipole) const;

};


}

#endif /* ELEMENTRENDERER_H_ */
