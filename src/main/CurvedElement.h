/*
 * CurvedElement.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef CURVEDELEMENT_H_
#define CURVEDELEMENT_H_

#include <math.h>
#include "Element.h"
#include "Particle.h"
#include "Vector3D.h"
#include "ElementVisitor.h"


namespace vhc {

/** Represente un element courbe. En plus de posseder les proprietes generales d'un element,
 *  un element courbe a de plus une courbure et un centre de courbure.
 *  ==> TODO ajouter explication de la courbure
 *  Le centre de courbure est calcule avec la courbure et les positions des faces d'entree et de sortie d'un element. */
class CurvedElement: public Element {

protected:

	/** Courbure. */
	double curvature;

	/** Centre de courbure de cet element. (coord. abs. ) */
	Vector3D curvatureCenter;

public:

	/** Constructeur d'elements courbes.
	 *  @param entry position de la face d'entree
	 *  @param exit position de face de sortie
	 *  @param sectionRadius rayon de section de la chambre a vide
	 *  @param curvature courbure de cet element
	 *  @param next pointeur sur l'element suivant */
	CurvedElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, Element* next = NULL);


	virtual ~CurvedElement() {};
	//virtual CurvedElement* copy() const {return new CurvedElement(*this);}

	virtual bool isOutside(const Particle& particle) const {
		Vector3D x(particle.getPosition() - entryPosition);
		if (x == Vector3D::Null) return false;
		else return (x - Vector3D(x.getX(), x.getY(), 0).unit() / fabs(curvature)).norm() > sectionRadius;
	}

	virtual bool isPast(const Particle& particle) const {
		Vector3D out = (entryPosition - curvatureCenter).cross(exitPosition - curvatureCenter).cross(entryPosition - curvatureCenter);
		return (particle.getPosition() - exitPosition).dot(out) > 0;
	}

	/** Retourne la courbure. */
	double getCurvature() const {return curvature;}

	/** Retourne le centre de courbure. */
	Vector3D getCurvatureCenter() const {return curvatureCenter;}

	/** Retourne l'angle entre la position d'entree, le centre de courbure et la position de sortie. */
	double getAngle() const {return acos((entryPosition - curvatureCenter).unit().dot((exitPosition - curvatureCenter).unit()));}

	virtual std::string getType() const {return "Curved Element";}
	virtual std::string toString() const {
		std::stringstream s;
		s << Element::toString() << "\n";
		s << "\tcurvature: "		<< getCurvature() 		<< "\n";
		s << "\tcurvature radius: "	<< 1.0 / getCurvature() << "\n";
		s << "\tcurvature center: "	<< getCurvatureCenter();
		return s.str();
	}

};

}

#endif /* CURVEDELEMENT_H_ */
