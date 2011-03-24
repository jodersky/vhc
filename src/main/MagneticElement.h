/*
 * MagneticElement.h
 *
 *  Created on: Mar 23, 2011
 *      Author: jakob
 */

#ifndef MAGNETICELEMENT_H_
#define MAGNETICELEMENT_H_

#include "Element.h"
#include "Vector3D.h"

namespace vhc {

class MagneticElement: public Element {

public:

	virtual ~MagneticElement();

	virtual Vector3D magneticField(const Vector3D& position) = 0;
};

}

#endif /* MAGNETICELEMENT_H_ */
