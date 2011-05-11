/*
 * CompositeElement.h
 *
 *  Created on: Mar 23, 2011
 *      Author: jakob
 */

#ifndef COMPOSITEELEMENT_H_
#define COMPOSITEELEMENT_H_

#include <vector>
#include "Element.h"
#include "Vector3D.h"
#include "ElementVisitor.h"


namespace vhc {

/** Classe abstraite representant un element compose de differents elements.
 *  Cette classe est immuable publiquement, c'est a dire que les elements constituants de cet element compose
 *  ne peuvent pas etres reassignes, ajoutes ou supprimes depuis l'exterieur.
 *  Le but de cette contrainte est de faciliter la gestion de pointeurs, necessaires au polymorphisme. */
class CompositeElement: public Element {

protected:

	/** Elements composants de cet element compose. */
	std::vector < Element* > elements;

public:

	CompositeElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL);
	virtual ~CompositeElement();

	virtual bool isBefore(const Vector3D& position) const;

	virtual bool isBeside(const Vector3D& position) const;

	virtual bool isAfter(const Vector3D& position) const;

	virtual Vector3D magneticFieldAt(const Vector3D& position) const;

	virtual Vector3D electricFieldAt(const Vector3D& position) const;

	virtual Vector3D getHorizontalAt(const Vector3D& position) const;

	virtual void accept(const ElementVisitor& v) const;

	virtual std::string getType() const;

	virtual std::string toString() const;

};

}

#endif /* COMPOSITEELEMENT_H_ */
