/*
 * Curved.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef CURVED_H_
#define CURVED_H_

#include <math.h>
#include "Vector3D.h"

namespace vhc {

//TODO implement abstract methods of Element
class Curved: public Element {

protected:

	Vector3D centerOfCurvature;

public:

	Curved(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvatureRadius, Element* next = NULL);
};

}

#endif /* CURVED_H_ */
