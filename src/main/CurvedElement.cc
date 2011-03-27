/*
 * CurvedElement.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include <assert.h>
#include <math.h>
#include "exceptions.h"
#include "CurvedElement.h"

namespace vhc {

<<<<<<< .mine
	/** Cf. CurvedElement.h */
	CurvedElement::CurvedElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next):

using namespace std;

CurvedElement::CurvedElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next):

		Element(entry, exit, sectionRadius, next),
		curvature(curvature),
		curvatureCenter(Vector3D::Null) {


		double k = curvature;

		//pas possible que le rayon de courbure soit plus petit la moitie
		//de la distance entre les points d'entree et de sortie
		if (1.0 / k < (exit - entry).norm() / 2) throw IllegalArgumentException("Invalid curvature radius.");

		Vector3D midpoint = (getEntryPosition() + getExitPosition())/ 2;
		curvatureCenter = midpoint + sqrt(1.0 - (k * k) / 4 * getDiagonal().normSquare()) * (getDiagonal().unit().cross(Vector3D::k));
}


	/* TODO print also Vecotr3D magnetic field
	* Schould we do as if curved element is an abstract class
	* and implement this method under the class 'MagneticCurvedElement'??
	*/
	/** Cf. CurvedElement.h */
	std::string CurvedElement::toString() const {

		std::stringstream s;
		s << "CurvedElement:"	<< "\n";
		s << "\tPosition of entry: 	 	 "	<< entryPosition	<< "\n";
		s << "\tPosition of exit: 	 	 "	<< exitPosition		<< "\n";
		s << "\tRadius of section: 	 	 "	<< sectionRadius	<< "\n";
		s << "\tRadius of curvature 1/k: "	<< 1/curvature		<< "\n";
		s << "\tCenter of curvature:	 "	<< curvatureCenter	<< "\n";
		s << "\t";
		return s.str();
	}

}
