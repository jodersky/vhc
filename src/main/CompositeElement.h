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

	CompositeElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL):
		Element(entry, exit, sectionRadius, next),
		elements(0) {};


	virtual ~CompositeElement();

	/*for (int i(0); i < elements.size(); ++i) {
				delete elements[i];
				elements[i] = NULL;
			};*/

	/** Determine si une particule a heurte le bord de cet element, donc d'un des elements composants. */
	virtual bool isOutside(const Particle& particle) const {
		for (int i(0); i < elements.size(); ++i) {
			if (elements[i]->isOutside(particle)) return true;
		}
		return false;
	}

	/** Determine si une particule a passe cet element, donc passe le dernier element composant. */
	virtual bool isPast(const Particle& particle) const {
		if (elements[elements.size() - 1]->isPast(particle)) return true;
		else return false;
	}

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

};

}

#endif /* COMPOSITEELEMENT_H_ */
