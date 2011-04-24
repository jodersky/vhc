/*
 * CompositeElement.cc
 *
 *  Created on: Mar 23, 2011
 *      Author: jakob
 */

#include <iomanip>
#include "CompositeElement.h"

using namespace std;
namespace vhc {

CompositeElement::CompositeElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next):
				Element(entry, exit, sectionRadius, next),
				elements(0) {};

CompositeElement::~CompositeElement() {};

bool CompositeElement::isBefore(const Vector3D& position) const {
	return elements.front()->isBefore(position);
}

bool CompositeElement::isBeside(const Vector3D& position) const {
	for (int i(0); i < elements.size(); ++i) {
		if (elements[i]->isBeside(position)) return true;
	}
	return false;
}

bool CompositeElement::isAfter(const Vector3D& position) const {
	return elements.back()->isAfter(position);
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

std::string CompositeElement::getType() const {return "CompositeElement";}

std::string CompositeElement::toString() const {
	std::stringstream s;
	s << Element::toString() << ":\n";
	for (int i(0); i < elements.size(); ++i) {
		s << "\t" << elements[i]->toString();
		if (i != elements.size() - 1) s << "\n";
	}
	return s.str();
}


} //vhc
