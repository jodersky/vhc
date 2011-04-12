/*
 * CompositeElement.cc
 *
 *  Created on: Mar 23, 2011
 *      Author: jakob
 */

#include "CompositeElement.h"

namespace vhc {

CompositeElement::CompositeElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next):
				Element(entry, exit, sectionRadius, next),
				elements(0) {};

CompositeElement::~CompositeElement() {};

bool CompositeElement::isOutside(const Particle& particle) const {
	for (int i(0); i < elements.size(); ++i) {
		if (elements[i]->isOutside(particle)) return true;
	}
	return false;
}

bool CompositeElement::isPast(const Particle& particle) const {
	if (elements[elements.size() - 1]->isPast(particle)) return true;
	else return false;
}


}
