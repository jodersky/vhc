/*
 * Curved.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef CURVED_H_
#define CURVED_H_

#include <math.h>
//#include <cmath.h>
#include "Element.h"
#include "Particle.h"
#include "Vector3D.h"

namespace vhc {

//TODO implement abstract methods of Element
class Curved: public Element {

protected:

	Vector3D curvatureCenter;
	double curvature;

public:

	Curved(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next = NULL):
			Element(entry, exit, sectionRadius, next),
			curvature(curvature),
			curvatureCenter(Vector3D::Null) {

			double k = curvature;
			Vector3D midpoint = (getEntryPosition() + getExitPosition())/ 2;
			curvatureCenter = midpoint + sqrt(1.0 - (k * k) / 4 * getDiagonal().normSquare()) * (getDiagonal().unit().cross(Vector3D::k));
	};

	virtual bool isOutside(const Particle& particle) const {
		Vector3D x(particle.getPosition() - getEntryPosition());
		return (x - Vector3D(x.getX(), x.getY(), 0).unit() / fabs(curvature)).norm() > sectionRadius;
	}

	virtual bool isPast(const Particle& particle) const {
		Vector3D out = (getEntryPosition() - curvatureCenter).cross(getExitPosition() - curvatureCenter).cross(getEntryPosition() - curvatureCenter);
		return (particle.getPosition() - getExitPosition()).dot(out) > 0;
	}

};

}

#endif /* CURVED_H_ */
