/*
 * StraightElement.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include "StraightElement.h"

namespace vhc {

StraightElement::StraightElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next):
		Element(entry, exit, sectionRadius, next)
	{};

StraightElement::~StraightElement() {};

bool StraightElement::isBefore(const Vector3D& position) const {
	const Vector3D v(position - exitPosition);
	return (-getDiagonal()).dot(v) > getDiagonal().normSquare();
}

bool StraightElement::isBeside(const Vector3D& position) const {
	Vector3D X = Vector3D(position - entryPosition);
	Vector3D d = getDiagonal().unit();
	return (X - X.dot(d) * d).norm() > sectionRadius;
};

bool StraightElement::isAfter(const Vector3D& position) const {
	const Vector3D v(position - entryPosition);
	return getDiagonal().dot(v) > getDiagonal().normSquare();
}

std::string StraightElement::getType() const {return "Straight Element";}
std::string StraightElement::toString() const {
	return Element::toString();
}

void StraightElement::accept(const ElementVisitor& v) const {v.visit(this);}

StraightElement* StraightElement::clone() const {return new StraightElement(getEntryPosition(), getExitPosition(), getSectionRadius());}

}
