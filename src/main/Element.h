/*
 * Element.h
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include <sstream>
#include "Vector3D.h"
#include "Particle.h"
#include "Printable.h"

namespace vhc {

/** Classe abstraite representant un element d'un accelerateur. */
class Element: public Printable {

private:

	/** Empêche la copie d'éléments par le constructeur de copie.
	 *  Si on veut explicitement copier un element utiliser <code>copy()</code>.*/
	//Element(const Element& e);

protected:

	/** Position du centre de la face d'entrée. */
	Vector3D entryPosition;

	/** Position du centre de la face de sortie. */
	Vector3D exitPosition;

	/** Rayon de la chambre à vide. */
	double sectionRadius;

	/** Pointeur sur l'élément suivant.
	 *  NULL si aucun element n'existe. */
	Element *next;

	/* Intensité (constante) du champ.
		 *  à améliorer
		double fieldIntensity;
		Vector3D magneticField

		* Direction du champ magnétique, invariant dans l'espace.
		Vector3D fieldDirection;
	 */

public:

	/** Constructeur d'elements.
	 *  @param entry position de la face d'entree
	 *  @param exit position de face de sortie
	 *  @param sectionRadius rayon de section de la chambre a vide
	 *  @param next pointeur sur l'element suivant */
	Element(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL):
		entryPosition(entry),
		exitPosition(exit),
		sectionRadius(sectionRadius),
		next(next) {};

	virtual ~Element() {};

	/** Copie l'element sur le heap et renvoye un pointeur sur la copie.
	 *  ATTENTION: La delocation de memoire est sous la responsabilite de l'appelant. */
	//virtual Element* copy() const = 0;

	/** Determine si la particule donnee a heurte le bord de cet element. */
	virtual bool isOutside(const Particle& particle) const = 0;

	/** Determine si la particule donnee a passe cet element. */
	virtual bool isPast(const Particle& particle) const = 0;

	/** Retourne le champ magnetique, a l'interieur de cet element a la position donnee. */
	virtual Vector3D magneticFieldAt(const Vector3D& position) const {
		return Vector3D::Null;
	}

	/** Retourne le champ electrique, a l'interieur de cet element a la position donnee. */
	virtual Vector3D electricFieldAt(const Vector3D& position) const {
		return Vector3D::Null;
	}

	/** Retourne la diagonale, c'est-a-dire le vecteur de la position d'entree
	 *  a la position de sortie. */
	Vector3D getDiagonal() const {return exitPosition - entryPosition;}

	/** Retourne la position d'entree. */
	Vector3D getEntryPosition() const {return entryPosition;}

	/** Assigne la position d'entree. */
	//void setEntryPosition(const Vector3D& newPos) {entryPosition = newPos;}

	/** Retourne la position de sortie. */
	Vector3D getExitPosition() const {return exitPosition;}

	/** Assigne la position de sortie. */
	//void setExitPosition(const Vector3D& newPos) {exitPosition = newPos;}

	/** Retourne le rayon de la section de cet element. */
	double getSectionRadius() const {return sectionRadius;}

	/** Assigne le rayon de la section de cet element. */
	void setSectionRadius(double r) {sectionRadius = r;}

	/** Retourne un pointeur l'element suivant. NULL s'il n'existe pas. */
	Element* getNext() const {return next;}

	/** Assigne un pointeur sur l'element suivant. */
	void setNext(Element* n) {next = n;}

	/** Retourne vrai si cet element est connecte a un element suivant, faux sinon. */
	bool isConnected() const {return next != NULL;}

	/** Retourne une representation en chaine du type de cet element, i.e. du nom de la classe.
	 *  Cette methode est utilisee principalement pour changer le comportement de <code>toString()</code>
	 *  dans des implementations concretes. */
	virtual std::string getType() const {return "Element";}

	virtual std::string toString() const {
		std::stringstream s;
		s << getType() << ":\n";
		s << "\tentry: " << getEntryPosition()	<<	"\n";
		s << "\texit: " << getExitPosition()	<<	"\n";
		s << "\tsection radius: " << getSectionRadius()	<<	"\n";
		s << "\tconnected: " << (isConnected() ? "true" : "false");
		return s.str();
	}

};

}

#endif /* ELEMENT_H_ */
