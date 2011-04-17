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


bool StraightElement::hasHit(const Particle& particle) const {
	Vector3D a(particle.getPosition() - entryPosition);
	const Vector3D b = (particle.getPosition() - entryPosition);
	return (a.cross(b)).norm() / getDiagonal().norm() > sectionRadius;
};

bool StraightElement::isPast(const Particle& particle) const {
	const Vector3D v(particle.getPosition() - entryPosition);
	return getDiagonal().dot(v) > getDiagonal().dot(getDiagonal());
}

std::string StraightElement::getType() const {return "Straight Element";}
std::string StraightElement::toString() const {
	std::stringstream s;
	s << Element::toString();
	return s.str();
}

void StraightElement::accept(const ElementVisitor& v) const {v.visit(this);}

StraightElement* StraightElement::clone() const {return new StraightElement(getEntryPosition(), getExitPosition(), getSectionRadius());}

}
