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
	/** Empeche la copie d'elements et facilite ainsi la gestion de pointeurs.
	 *  Pourquoi aurait-on besoin de copier un element? */
	Element(const Element& e);

protected:

	/** Position du centre de la face d'entree. */
	Vector3D entryPosition;

	/** Position du centre de la face de sortie. */
	Vector3D exitPosition;

	/** Rayon de la chambre a vide. */
	double radius;

	/** Pointeur sur l'element suivant. */
	Element *next;

public:
	Element();
	virtual ~Element();

	virtual bool isOutside(const Particle& p) const = 0;

	virtual bool isPast(const Particle& p) const = 0;

	Vector3D getEntryPosition() const {return entryPosition;}
	void setEntryPosition(const Vector3D& newPos) {entryPosition = newPos;}

	Vector3D getExitPosition() const {return exitPosition;}
	void setExitPosition(const Vector3D& newPos) {exitPosition = newPos;}

	double getRadius() const {return radius;}
	void setRadius(double r) {radius = r;}

	Element* getNext() const {return next;}

	//TODO use pointer?
	void setNext(Element& n) {next = &n;}

};

}

#endif /* ELEMENT_H_ */
