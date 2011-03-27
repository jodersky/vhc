/*
 * StraightElement.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#ifndef STRAIGHTELEMENT_H_
#define STRAIGHTELEMENT_H_

#include "Vector3D.h"
#include "Element.h"
#include "Particle.h"

namespace vhc {


class StraightElement: public Element {

public:

	StraightElement(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL):
		Element(entry, exit, sectionRadius, next)
	{};

	// TODO avec cette mauvaise méthode, tous les éléments pointent vers l'origine...
	/** Constructeur d'une section, où l'on donne une position d'entrée et une longueur. */
	StraightElement(const Vector3D& entry, double l, double sectionRadius,const Vector3D& exit=Vector3D::Null, Element* next = NULL):
		Element(entry, exit, sectionRadius, next)
	{ this->setLength(l); };

	/* Affecte un longueur à la section droite, à partir de la position d'entrée. */
	void setLength (double l) {
		setExitPosition( entryPosition + ( l * (~(exitPosition - entryPosition))));
	}

	//TODO ! why can't you access protected variables, i.e. entryPosition won't work?!

	virtual StraightElement* copy() const {return new StraightElement(*this);}


	virtual bool isOutside(const Particle& particle) const {
		Vector3D a(particle.getPosition() - entryPosition);
		const Vector3D b = (particle.getPosition() - entryPosition);
		return (a.cross(b)).norm() / getDiagonal().norm() > sectionRadius;
	};

	virtual bool isPast(const Particle& particle) const {
		const Vector3D v(particle.getPosition() - entryPosition);
		return getDiagonal().dot(v) > getDiagonal().dot(getDiagonal());
	}

	/* Retourne une chaîne de caractères de cet élément droit. */
	virtual std::string toString () const;

	virtual std::string getType() const {return "Straight Element";}
	virtual std::string toString() const {
		std::stringstream s;
		s << Element::toString();
		return s.str();
	}

};

}

#endif /* STRAIGHTELEMENT_H_ */
