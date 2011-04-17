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
	double focalizingCoefficient;

public:
	Quadrupole(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double focalizingCoefficient, Element* next = NULL);

	virtual ~Quadrupole();

	virtual Vector3D magneticFieldAt(const Vector3D& position);

	double getFocalizingCoefficient() const;

	void setFocalizingCoefficient(double value);

	virtual std::string getType() const;

	virtual void accept(const ElementVisitor& v) const;

	virtual Quadrupole* clone() const;
};

}

#endif /* QUADRUPOLE_H_ */
