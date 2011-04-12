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

	/** Determine si une particule a heurte le bord de cet element, donc d'un des elements composants. */
	virtual bool hasHit(const Particle& particle) const;

	/** Determine si une particule a passe cet element, donc passe le dernier element composant. */
	virtual bool isPast(const Particle& particle) const;

	virtual Vector3D magneticFieldAt(const Vector3D& position) const {
		Vector3D b = Vector3D::Null;
		for (int i(0); i < elements.size(); i++) {
			b = b + elements[i]->magneticFieldAt(position);
		}
		return b;
	}

	virtual Vector3D electricFieldAt(const Vector3D& position) const {
		Vector3D e = Vector3D::Null;
		for (int i(0); i < elements.size(); i++) {
			e = e + elements[i]->electricFieldAt(position);
		}
		return e;
	}

	virtual void accept(ElementVisitor& v) {
		for (int i(0); i < elements.size(); ++i) {
			elements[i]->accept(v);
		}
	}

	virtual std::string toString() {
		std::stringstream s;
		for (int i(0); i < elements.size(); ++i) {
			s << elements[i]->toString() << "\n";
		}
		return s.str();
	}

};

}

#endif /* COMPOSITEELEMENT_H_ */
