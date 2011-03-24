/*
 * ElectricElement.h
 *
 *  Created on: Mar 24, 2011
 *      Author: jakob
 */

#ifndef ELECTRICELEMENT_H_
#define ELECTRICELEMENT_H_

#include "Vector3D.h"
#include "Element.h"

namespace vhc {

class ElectricElement: public Element {

public:

	ElectricElement();

	virtual ~ElectricElement();

	Vector3D electricField(const Vector3D& position) const = 0;

	virtual std::string getType() const {return "Electric Element";}

};

}

#endif /* ELECTRICELEMENT_H_ */
