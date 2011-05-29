/*
 * Element.h
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include "Vector3D.h"
#include "Particle.h"
#include "Printable.h"
#include "ElementVisitor.h"
#include "Cloneable.h"


namespace vhc {

/** Classe abstraite representant un element d'un accelerateur. */
class Element: public Printable, public Cloneable {

protected:

	/** Position du centre de la face d'entrée. */
	Vector3D entryPosition;

	/** Position du centre de la face de sortie. */
	Vector3D exitPosition;

	/** Rayon de la chambre à vide. */
	double sectionRadius;

	/** Pointeur sur l'élément precedent.
	 *  NULL si aucun element n'existe. */
	Element *previous;

	/** Pointeur sur l'élément suivant.
	 *  NULL si aucun element n'existe. */
	Element *next;



public:

	/** Constructeur d'elements.
	 *  @param entry position de la face d'entree
	 *  @param exit position de face de sortie
	 *  @param sectionRadius rayon de section de la chambre a vide
	 *  @param next pointeur sur l'element suivant */
	Element(const Vector3D& entry, const Vector3D& exit, double sectionRadius, Element* next = NULL);

	virtual ~Element();

	/** Copie l'element sur le heap et renvoye un pointeur sur la copie.
	 *  En copiant un element, le pointeur sur l'element suivant est remis a zero.
	 *  ATTENTION: La delocation de memoire est sous la responsabilite de l'appelant. */
	virtual Element* clone() const = 0;

	/** Retourne vrai si la position donnee se situe avant la face d'entree de cet element. */
	virtual bool isBefore(const Vector3D& position) const = 0;
	bool isBefore(const Particle& particle) const;

	/** Retourne vrai si la position donnee se situe a cote de cet element. */
	virtual bool isBeside(const Vector3D& position) const = 0;
	bool isBeside(const Particle& particle) const;

	/** Retourne vrai si la position donnee se situe apres la face de sortie de cet element. */
	virtual bool isAfter(const Vector3D& position) const = 0;
	bool isAfter(const Particle& particle) const;

	/** Retourne vrai si la position donnee se trouve a l'interieur de cet element (c'est-a-dire si elle n'est ni devnt ni derriere ni a cote de cet element). */
	bool contains(const Vector3D& position) const;
	bool contains(const Particle& particle) const;

	/** Retourne un vecteur horizontal pointant en oppose de l'origine (correspond au vecteur u du complement mathemmatique). */
	virtual Vector3D getHorizontalAt(const Vector3D& position) const = 0;

	/** Retourne le champ magnetique, a l'interieur de cet element a la position donnee. */
	virtual Vector3D magneticFieldAt(const Vector3D& position) const;

	/** Retourne le champ electrique, a l'interieur de cet element a la position donnee. */
	virtual Vector3D electricFieldAt(const Vector3D& position) const;

	/** Retourne la diagonale, c'est-a-dire le vecteur de la position d'entree
	 *  a la position de sortie. */
	Vector3D getDiagonal() const;

	/** Retourne la position d'entree. */
	Vector3D getEntryPosition() const;

	/** Assigne la position d'entree. */
	//void setEntryPosition(const Vector3D& newPos) {entryPosition = newPos;}

	/** Retourne la position de sortie. */
	Vector3D getExitPosition() const;

	/** Assigne la position de sortie. */
	//void setExitPosition(const Vector3D& newPos) {exitPosition = newPos;}

	/** Retourne le rayon de la section de cet element. */
	double getSectionRadius() const;

	/** Retourne la longueur de cet element. */
	virtual double getLength() const = 0;

	/** Assigne le rayon de la section de cet element. */
	//void setSectionRadius(double r) {sectionRadius = r;}

	/** Retourne un pointeur l'element suivant. NULL s'il n'existe pas. */
	Element* getPrevious() const;

	/** Assigne un pointeur sur l'element suivant. */
	void setPrevious(Element* p);

	/** Retourne un pointeur sur l'element suivant. NULL s'il n'existe pas. */
	Element* getNext() const;

	/** Assigne un pointeur sur l'element suivant. */
	void setNext(Element* n);

	/** Retourne vrai si cet element est connecte a un element precedent et suivant, faux sinon. */
	bool isConnected() const;

	/** Retourne une representation en chaine du type de cet element, i.e. du nom de la classe.
	 *  Cette methode est utilisee principalement pour changer le comportement de <code>toString()</code>
	 *  dans des implementations concretes. */
	virtual std::string getType() const;

	/** Retourne une représentation de cet élément sous forme de chaînes de caractères.*/
	virtual std::string toString() const;

	/** Accepte un visiteur d'elements.
	 *  @see ElementVisitor */
	virtual void accept(const ElementVisitor& v) const = 0;

};

}

#endif /* ELEMENT_H_ */
