/*
 * Element.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */


#include <sstream>
#include <iomanip>
#include "Element.h"

using namespace std;

namespace vhc {

Element::Element(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next):
		entryPosition(entry),
		exitPosition(exit),
		sectionRadius(sectionRadius),
		previous(NULL),
		next(next)
		{}

Element::~Element() {};

bool Element::isAfter(const Particle& particle) const {return isAfter(particle.getPosition());}

bool Element::isBefore(const Particle& particle) const {return isBefore(particle.getPosition());}

bool Element::isBeside(const Particle& particle) const {return isBeside(particle.getPosition());}

bool Element::contains(const Vector3D& position) const {
	return !(isAfter(position) || isBefore(position) || isBeside(position));
}

bool Element::contains(const Particle& particle) const {
	return contains(particle.getPosition());
}

Vector3D Element::magneticFieldAt(const Vector3D& position) const {return Vector3D::Null;}

Vector3D Element::electricFieldAt(const Vector3D& position) const {return Vector3D::Null;}

Vector3D Element::getDiagonal() const {return exitPosition - entryPosition;}

Vector3D Element::getEntryPosition() const {return entryPosition;}

Vector3D Element::getExitPosition() const {return exitPosition;}

double Element::getSectionRadius() const {return sectionRadius;}

Element* const Element::getPrevious() const {return previous;}

void Element::setPrevious(Element* p) {previous = p;}

Element* const Element::getNext() const {return next;}

void Element::setNext(Element* n) {next = n;}

bool Element::isConnected() const {return next != NULL;}

string Element::getType() const {return "Element";}

string Element::toString() const {
	stringstream s;
	s << left << setfill(' ') << setw(20) << getType() << ": ";
	s << "in = " << getEntryPosition() << " ; "
	  << "out = " << getExitPosition()	<<	" ; "
	  << "Rs = " << getSectionRadius();
	return s.str();
}

} //vhc
