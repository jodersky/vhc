/*
 * CurvedElement.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include <math.h>
#include <sstream>
#include "exceptions.h"
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

CurvedElement::~CurvedElement() {};

double CurvedElement::getCurvature() const {return curvature;}

Vector3D CurvedElement::getCurvatureCenter() const {return curvatureCenter;}

double CurvedElement::getAngle() const {
	return acos((entryPosition - curvatureCenter).unit().dot((exitPosition - curvatureCenter).unit()));
}

bool CurvedElement::hasHit(const Particle& particle) const {
	Vector3D x(particle.getPosition() - entryPosition);
	if (x == Vector3D::Null) return false;
	else return (x - Vector3D(x.getX(), x.getY(), 0).unit() / fabs(curvature)).norm() > sectionRadius;
}

bool CurvedElement::isPast(const Particle& particle) const {
	Vector3D out = (entryPosition - curvatureCenter).cross(exitPosition - curvatureCenter).cross(entryPosition - curvatureCenter);
	return (particle.getPosition() - exitPosition).dot(out) > 0;
}

std::string CurvedElement::getType() const {return "Curved Element";}
std::string CurvedElement::toString() const {
	std::stringstream s;
	s << Element::toString() << "\n";
	s << "\tcurvature: "		<< getCurvature() 		<< "\n";
	s << "\tcurvature radius: "	<< 1.0 / getCurvature() << "\n";
	s << "\tcurvature center: "	<< getCurvatureCenter();
	return s.str();
}

} //vhc
