/*
 * Straight.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef STRAIGHT_H_
#define STRAIGHT_H_

#include "Vector3D.h"
#include "Element.h"
#include "Particle.h"

namespace vhc {


class Straight: public Element {

public:

	Straight(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL):
		Element(entry, exit, sectionRadius, next)
	{};

	//TODO ! why can't you access protected variables, i.e. entryPosition won't work?!
	virtual bool isOutside(const Particle& particle) const {
		Vector3D a(particle.getPosition() - entryPosition);
		const Vector3D b = (particle.getPosition() - entryPosition);
		return (a.cross(b)).norm() / getDiagonal().norm() > sectionRadius;
	};

	virtual bool isPast(const Particle& particle) const {
		const Vector3D v(particle.getPosition() - entryPosition);
		return getDiagonal().dot(v) > getDiagonal().dot(getDiagonal());
	}

};

}

#endif /* STRAIGHT_H_ */
