/*
 * Quadrupole.h
 *
 *  Created on: Mar 29, 2011
 *      Author: jakob
 */

#ifndef QUADRUPOLE_H_
#define QUADRUPOLE_H_

#include <string>
#include "StraightElement.h"
#include "Vector3D.h"
#include "ElementVisitor.h"

namespace vhc {

class Quadrupole: public StraightElement {

private:
	double focusingCoefficient;

public:
	Quadrupole(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double focusingCoefficient, Element* next = NULL):
		StraightElement(entry, exit, sectionRadius, next),
		focusingCoefficient(focusingCoefficient)
	{};

	virtual ~Quadrupole() {};

	virtual Vector3D magneticFieldAt(const Vector3D& position) {
		Vector3D x = position - getEntryPosition();
		Vector3D d = getDiagonal().unit();
		Vector3D y = x - x.dot(d) * d;
		Vector3D u = Vector3D::k.cross(d);
		return focusingCoefficient * (y.dot(u) * Vector3D::k + position.getZ() * u);
	}

	double getFocusingCoefficient() const {
		return focusingCoefficient;
	}

	void setFocusingCoefficient(double value) {
		focusingCoefficient = value;
	}

	virtual std::string getType() const {return "Quadrupole";}

	virtual void accept(ElementVisitor& v) {v.visit(this);}

	virtual Quadrupole* clone() const {return new Quadrupole(getEntryPosition(), getExitPosition(), getSectionRadius(), focusingCoefficient);}
};

}

#endif /* QUADRUPOLE_H_ */
