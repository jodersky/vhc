/*
 * Curved.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include "Curved.h"

namespace vhc {

Curved::Curved(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvatureRadius, Element* next = NULL):
		Element(entry, exit, sectionRadius, next),
		centerOfCurvature(Vector3D::Null) {

		Vector3D bisector = getDiagonal().cross(Vector3D::k);
		double halfLength = (getDiagonal() / 2).norm();
		Vector3D midpoint = getEntryPosition() + getDiagonal() / 2;

		centerOfCurvature = midpoint + bisector.unit() * copysign(
				sqrt(curvatureRadius * curvatureRadius - halfLength * halfLength),
				curvatureRadius);
};

}
