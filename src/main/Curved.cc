/*
 * Curved.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include <math.h>
#include "Curved.h"

namespace vhc {

Curved::Curved(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next):
		Element(entry, exit, sectionRadius, next),
		curvature(curvature),
		curvatureCenter(Vector3D::Null){} /*{

		double k = curvature;
		Vector3D midpoint = (getEntryPosition() + getExitPosition())/ 2;
		curvatureCenter = midpoint + sqrt(1.0 - (k * k) / 4 * getDiagonal().normSquare()) * (getDiagonal().unit().cross(Vector3D::k));
}*/

}
