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


	virtual ~CurvedElement();
	//virtual CurvedElement* clone() const {return new CurvedElement(*this);}

	virtual bool hasHit(const Particle& particle) const;

	virtual bool isPast(const Particle& particle) const;

	/** Retourne la courbure. */
	double getCurvature() const;

	/** Retourne le centre de courbure. */
	Vector3D getCurvatureCenter() const;

	/** Retourne l'angle entre la position d'entree, le centre de courbure et la position de sortie. */
	double getAngle() const;

	virtual std::string getType() const;
	virtual std::string toString() const;

};

}

#endif /* CURVEDELEMENT_H_ */
