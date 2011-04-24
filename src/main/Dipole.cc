/*
 * Dipole.cc
 *
 *  Created on: Mar 28, 2011
 *      Author: jakob
 */

#include <sstream>
#include "Dipole.h"

namespace vhc {

Dipole::Dipole(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, const Vector3D& magneticField, Element* next):
		CurvedElement(entry, exit, sectionRadius, curvature, next),
				  _magneticField(magneticField) {

}

Dipole::~Dipole() {}

Vector3D Dipole::getMagneticField() const {return _magneticField;}

void Dipole::setMagneticField(const Vector3D& field) {_magneticField = field;}

Vector3D Dipole::magneticFieldAt(const Vector3D& position) const {return _magneticField;}

std::string Dipole::getType() const {return "Dipole";}

std::string Dipole::toString() const {
	std::stringstream s;
	s << CurvedElement::toString() << " ; ";
	s << "B = " << getMagneticField();
	return s.str();
}

void Dipole::accept(const ElementVisitor& v) const {v.visit(this);}

Dipole* Dipole::clone() const {
	return new Dipole(getEntryPosition(), getExitPosition(), getSectionRadius(), getCurvature(), _magneticField);
}

} //vhc
