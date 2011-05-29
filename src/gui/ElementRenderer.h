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

/** Dessinateur d'elements. Implemente une interface de visiteur d'elements.
 *  @see ElementVisitor
 *  @see http://fr.wikipedia.org/wiki/Visiteur_%28motif_de_conception%29 */
class ElementRenderer: public ElementVisitor, public Renderer<Element> {

private:
	/** Cotes laterales des cylindres. */
	static const int SLICES = 100;

	/** Divisions des cylindres. */
	static const int STACKS_PER_LENGTH = 20;

	/** Dessine un element droit. */
	void drawStraight(const StraightElement* straight) const;

public:

	ElementRenderer();

	virtual ~ElementRenderer();

	/** Dessine un element. */
	virtual void render(const Element& element) const;

	/** Visite un element droit (le dessine dans ce cas). */
	virtual void visit(const StraightElement* straight) const ;

	/** Visite un quadrupole(le dessine dans ce cas). */
	virtual void visit(const Quadrupole* quadrupole) const;

	/** Visite un dipole (le dessine dans ce cas). */
	virtual void visit(const Dipole* dipole) const;

};


}

#endif /* ELEMENTRENDERER_H_ */
