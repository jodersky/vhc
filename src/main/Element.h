/*
 * Element.h
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Vector3D.h"
#include "Particle.h"

namespace vhc {

class Element {

private:
	/** Empêche la copie d'éléments et facilite ainsi la gestion de pointeurs.
	 *  Pourquoi aurait-on besoin de copier un élément? */
	Element(const Element& e);

protected:

	/** Position du centre de la face d'entrée. */
	Vector3D entryPosition;

	/** Position du centre de la face de sortie. */
	Vector3D exitPosition;

	/** Rayon de la chambre à vide. */
	double sectionRadius;

	/** Pointeur sur l'élément suivant. */
	Element *next;

	/* Intensité (constante) du champ.
		 * TODO à améliorer
		double fieldIntensity;
		Vector3D magneticField

		/** Direction du champ magnétique, invariant dans l'espace.
		Vector3D fieldDirection;
	 */

public:
	Element(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL):
		entryPosition(entry),
		exitPosition(exit),
		sectionRadius(sectionRadius),
		next(next)
	{};

	virtual bool isOutside(const Particle& p) const = 0;

	/* TODO Et si la valeur de retour était un pointeur? */
	virtual bool isPast(const Particle& p) const = 0;

	Vector3D getDiagonal() const {return exitPosition - entryPosition;}

	Vector3D getEntryPosition() const {return entryPosition;}
	void setEntryPosition(const Vector3D& newPos) {entryPosition = newPos;}

	Vector3D getExitPosition() const {return exitPosition;}
	void setExitPosition(const Vector3D& newPos) {exitPosition = newPos;}

	double getSectionRadius() const {return sectionRadius;}
	void setSectionRadius(double r) {sectionRadius = r;}

	Element* getNext() const {return next;}

	//TODO use pointer?
	void setNext(Element& n) {next = &n;}

};

}

#endif /* ELEMENT_H_ */
