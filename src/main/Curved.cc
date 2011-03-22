/*
 * Curved.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include "Curved.h"

namespace vhc {

Curved::Curved(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvatureRadius, Element* next = NULL):
		entryPosition(entry),
		exitPosition(exit),
		sectionRadius(sectionRadius),
		next(next) {

		double orientation = signum(curvatureRadius);
		Vector3D bisector = getDiagonal().cross(Vector3D::k);
		double halfLength = (getDiagonal() / 2).norm();
		Vector3D midpoint = getEntryPoisition() + getDiagonal() / 2;

		centerOfCurvature = midpoint + bisector.unit() *
				sqrt(curvatureRadius * curvatureRadius - halfLength * halfLength) *
				orientation;
};

}
