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

namespace vhc {

class CompositeElement: public Element {

	std::vector < Element* > elements;

public:

	CompositeElement(
		const Vector3D& entry,
		const Vector3D& exit,
		double sectionRadius,
		const std::vector<Element*> & elements0,
		Element* next = NULL):

		Element(entry, exit, sectionRadius, next),
		elements(0) {

		for (int i(0); i < elements0.size(); ++i) {
			elements.push_back(elements0[i]->copy());
		};
	}


	virtual ~CompositeElement() {
		for (int i(0); i < elements.size(); ++i) {
			delete elements[i];
			elements[i] = NULL;
		};
	}

	//TODO copy may not be alright (shallow)?
	virtual CompositeElement* copy() const {return new CompositeElement(*this);}

	virtual bool isOutside(const Particle& particle) const {
		for (int i(0); i < elements.size(); ++i) {
			if (elements[i]->isOutside(particle)) return true;
		}
		return false;
	}

	virtual bool isPast(const Particle& particle) const {
		if (elements[elements.size() - 1]->isPast(particle)) return true;
		else return false;
	}
};

}

#endif /* COMPOSITEELEMENT_H_ */
