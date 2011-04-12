/*
 * StraightElement.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef STRAIGHTELEMENT_H_
#define STRAIGHTELEMENT_H_

#include "Vector3D.h"
#include "Element.h"
#include "Particle.h"
#include "ElementVisitor.h"

namespace vhc {


class StraightElement: public Element {

public:

	StraightElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL):
		Element(entry, exit, sectionRadius, next)
	{};

	virtual ~StraightElement() {};

	//virtual StraightElement* clone() const {return new StraightElement(*this);}

	virtual bool isOutside(const Particle& particle) const {
		Vector3D a(particle.getPosition() - entryPosition);
		const Vector3D b = (particle.getPosition() - entryPosition);
		return (a.cross(b)).norm() / getDiagonal().norm() > sectionRadius;
	};

	virtual bool isPast(const Particle& particle) const {
		const Vector3D v(particle.getPosition() - entryPosition);
		return getDiagonal().dot(v) > getDiagonal().dot(getDiagonal());
	}

	virtual std::string getType() const {return "Straight Element";}
	virtual std::string toString() const {
		std::stringstream s;
		s << Element::toString();
		return s.str();
	}

	virtual void accept(ElementVisitor& v) {v.visit(this);}

	virtual StraightElement* clone() const {return new StraightElement(getEntryPosition(), getExitPosition(), getSectionRadius());}

};

}

#endif /* STRAIGHTELEMENT_H_ */
