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

CurvedElement::CurvedElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next):
		Element(entry, exit, sectionRadius, next),
		curvature(curvature),
		curvatureCenter(Vector3D::Null) {


		double k = curvature;

		//pas possible que le rayon de courbure soit plus petit la moitie
		//de la distance entre les points d'entree et de sortie
		if (fabs(1.0 / k) < (exit - entry).norm() / 2) throw IllegalArgumentException("Invalid curvature radius: too small.");

		Vector3D outDirection = (entryPosition - curvatureCenter).cross(exitPosition - curvatureCenter).cross(exitPosition - curvatureCenter);
		if ((entryPosition - exitPosition).dot(outDirection) > 0) throw IllegalArgumentException("A curved element cannot be more than half a turn.");


		Vector3D midpoint = (getEntryPosition() + getExitPosition())/ 2;
		curvatureCenter = midpoint + 1 / k * sqrt(1.0 - (k * k) / 4 * getDiagonal().normSquare()) * (getDiagonal().unit().cross(Vector3D::k));
}

CurvedElement::~CurvedElement() {};

double CurvedElement::getCurvature() const {return curvature;}

Vector3D CurvedElement::getCurvatureCenter() const {return curvatureCenter;}

double CurvedElement::getAngle() const {
	return acos((entryPosition - curvatureCenter).unit().dot((exitPosition - curvatureCenter).unit()));
}

bool CurvedElement::isBefore(const Vector3D& position) const {
	Vector3D out = (exitPosition - curvatureCenter).cross(entryPosition - curvatureCenter).cross(entryPosition - curvatureCenter);
	return (position - entryPosition).dot(out) > 0;
}

bool CurvedElement::isBeside(const Vector3D& position) const {
	Vector3D X(position - curvatureCenter);
	Vector3D u = (X - position.getZ() * Vector3D::k).unit();
	return (X - fabs(1.0 / curvature) * u).norm() > sectionRadius;
}

bool CurvedElement::isAfter(const Vector3D& position) const {
	Vector3D out = (entryPosition - curvatureCenter).cross(exitPosition - curvatureCenter).cross(exitPosition - curvatureCenter);
	return (position - exitPosition).dot(out) > 0;
}

double CurvedElement::getLength() const {
	return getAngle() / getCurvature();
}

Vector3D CurvedElement::getHorizontalAt(const Vector3D& position) const {
	Vector3D X(position - curvatureCenter);
	return (X - position.getZ() * Vector3D::k).unit();
}

std::string CurvedElement::getType() const {return "Curved Element";}
std::string CurvedElement::toString() const {
	std::stringstream s;
	s << Element::toString() << " "
	  << "k = "	<< getCurvature() << " ; "
	  << "Cc =  " << getCurvatureCenter();
	return s.str();
}

} //vhc
