/*
 * Element.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */


#include <sstream>
#include "Element.h"

namespace vhc {

Element::Element(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next):
		entryPosition(entry),
		exitPosition(exit),
		sectionRadius(sectionRadius),
		next(next) {

}

Element::~Element() {};

Vector3D Element::magneticFieldAt(const Vector3D& position) const {return Vector3D::Null;}

Vector3D Element::electricFieldAt(const Vector3D& position) const {return Vector3D::Null;}

Vector3D Element::getDiagonal() const {return exitPosition - entryPosition;}

Vector3D Element::getEntryPosition() const {return entryPosition;}

Vector3D Element::getExitPosition() const {return exitPosition;}

double Element::getSectionRadius() const {return sectionRadius;}

Element* Element::getNext() const {return next;}

void Element::setNext(Element* n) {next = n;}

bool Element::isConnected() const {return next != NULL;}

std::string Element::getType() const {return "Element";}

std::string Element::toString() const {
	std::stringstream s;
	s << getType() << ":\n";
	s << "\tentry: " << getEntryPosition()	<<	"\n";
	s << "\texit: " << getExitPosition()	<<	"\n";
	s << "\tsection radius: " << getSectionRadius()	<<	"\n";
	s << "\tconnected: " << (isConnected() ? "true" : "false");
	return s.str();
}

} //vhc
