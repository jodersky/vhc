/*
 * CurvedElement.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef CURVEDELEMENT_H_
#define CURVEDELEMENT_H_

#include <math.h>
//#include <cmath.h>
#include "Element.h"
#include "Particle.h"
#include "Vector3D.h"

namespace vhc {

//TODO implement abstract methods of Element
class CurvedElement: public Element {

protected:

	Vector3D curvatureCenter;
	double curvature;

public:

	CurvedElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next = NULL);

	virtual bool isOutside(const Particle& particle) const {
		Vector3D x(particle.getPosition() - entryPosition);
		return (x - Vector3D(x.getX(), x.getY(), 0).unit() / fabs(curvature)).norm() > sectionRadius;
	}

	virtual bool isPast(const Particle& particle) const {
		Vector3D out = (entryPosition - curvatureCenter).cross(exitPosition - curvatureCenter).cross(entryPosition - curvatureCenter);
		return (particle.getPosition() - exitPosition).dot(out) > 0;
	}

};

}

#endif /* CURVEDELEMENT_H_ */
