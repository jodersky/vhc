/*
 * CurvedElement.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include <assert.h>
#include <math.h>
#include "exception.h"
#include "CurvedElement.h"

using namespace std;
namespace vhc {

	/** Cf. CurvedElement.h */
CurvedElement::CurvedElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next):

		Element(entry, exit, sectionRadius, next),
		curvature(curvature),
		curvatureCenter(Vector3D::Null) {


		double k = curvature;

		//pas possible que le rayon de courbure soit plus petit la moitie
		//de la distance entre les points d'entree et de sortie
		if (fabs(1.0 / k) < (exit - entry).norm() / 2) throw IllegalArgumentException("Invalid curvature radius.");

		Vector3D midpoint = (getEntryPosition() + getExitPosition())/ 2;
		curvatureCenter = midpoint + 1 / k * sqrt(1.0 - (k * k) / 4 * getDiagonal().normSquare()) * (getDiagonal().unit().cross(Vector3D::k));
}

}