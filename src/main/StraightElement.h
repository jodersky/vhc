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

	StraightElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL);

	virtual ~StraightElement();

	virtual bool isBefore(const Vector3D& position) const;

	virtual bool isBeside(const Vector3D& position) const;

	virtual bool isAfter(const Vector3D& position) const;

	virtual std::string getType() const;
	virtual std::string toString() const;

	virtual void accept(const ElementVisitor& v) const;

	virtual StraightElement* clone() const;

};

}

#endif /* STRAIGHTELEMENT_H_ */
