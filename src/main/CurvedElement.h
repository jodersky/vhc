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

/** Classe de base pour elements courbes. En plus de posseder les proprietes generales d'un element,
 *  un element courbe une courbure et un centre de courbure.
 *  La courbure est donnee par l'inverse du rayon de courbure dont le signe indique le sens de courbure par
 *  rapport à l’orientation donnée par l’opposé de l’axe vertical (Vector3D::k);
 *
 *  Le centre de courbure est calcule avec la courbure et les positions des faces d'entree et de sortie d'un element.
 *
 *  <b>ATTENTION:</b> un element courbe ne peut faire plus d'un demi tour! */
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

	/** Destructeur virtuel. */
	virtual ~CurvedElement();

	virtual bool isBefore(const Vector3D& position) const;

	virtual bool isBeside(const Vector3D& position) const;

	virtual bool isAfter(const Vector3D& position) const;

	/** Retourne la courbure. */
	double getCurvature() const;

	/** Retourne le centre de courbure. */
	Vector3D getCurvatureCenter() const;

	/** Retourne l'angle entre la position d'entree, le centre de courbure et la position de sortie. */
	double getAngle() const;

	/** Retourne le type ("Cuved Element") de cet élément.*/
	virtual std::string getType() const;

	/** Retourne cet élément courbe sous forme de chaîne de caractères.*/
	virtual std::string toString() const;

};

}

#endif /* CURVEDELEMENT_H_ */
