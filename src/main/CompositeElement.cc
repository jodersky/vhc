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

bool CompositeElement::hasHit(const Particle& particle) const {
	for (int i(0); i < elements.size(); ++i) {
		if (elements[i]->hasHit(particle)) return true;
	}
	return false;
}

bool CompositeElement::isPast(const Particle& particle) const {
	if (elements[elements.size() - 1]->isPast(particle)) return true;
	else return false;
}

Vector3D CompositeElement::magneticFieldAt(const Vector3D& position) const {
	Vector3D b = Vector3D::Null;
	for (int i(0); i < elements.size(); i++) {
		b = b + elements[i]->magneticFieldAt(position);
	}
	return b;
}

Vector3D CompositeElement::electricFieldAt(const Vector3D& position) const {
	Vector3D e = Vector3D::Null;
	for (int i(0); i < elements.size(); i++) {
		e = e + elements[i]->electricFieldAt(position);
	}
	return e;
}

void CompositeElement::accept(const ElementVisitor& v) const {
	for (int i(0); i < elements.size(); ++i) {
		elements[i]->accept(v);
	}
}

std::string CompositeElement::toString() const {
	std::stringstream s;
	for (int i(0); i < elements.size(); ++i) {
		s << elements[i]->toString() << "\n";
	}
	return s.str();
}


} //vhc
