/*
 * Quadrupole.cc
 *
 *  Created on: Mar 29, 2011
 *      Author: jakob
 */

#include <iostream>
#include <sstream>
#include "Quadrupole.h"

namespace vhc {

Quadrupole::Quadrupole(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double focalizingCoefficient, Element* next):
		StraightElement(entry, exit, sectionRadius, next),
		focalizingCoefficient(focalizingCoefficient)
	{};

Quadrupole::~Quadrupole() {};

Vector3D Quadrupole::magneticFieldAt(const Vector3D& position) const {
	Vector3D x = position - getEntryPosition();
	Vector3D d = getDiagonal().unit();
	Vector3D y = x - x.dot(d) * d;
	Vector3D u = Vector3D::k.cross(d);
	return focalizingCoefficient * (y.dot(u) * Vector3D::k + position.getZ() * u);
}

double Quadrupole::getFocalizingCoefficient() const {
	return focalizingCoefficient;
}

void Quadrupole::setFocalizingCoefficient(double value) {
	focalizingCoefficient = value;
}

std::string Quadrupole::getType() const {return "Quadrupole";}
std::string Quadrupole::toString() const {
	std::stringstream s;
	s << Element::toString() << "\n";
	s << "\tfocalizing coefficient: " << focalizingCoefficient;
	return s.str();
}

void Quadrupole::accept(const ElementVisitor& v) const {v.visit(this);}

Quadrupole* Quadrupole::clone() const {return new Quadrupole(getEntryPosition(), getExitPosition(), getSectionRadius(), focalizingCoefficient);}


}
