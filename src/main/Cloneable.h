/*
 * Cloneable.h
 *
 *  Created on: Apr 12, 2011
 *      Author: jakob
 */

#ifndef CLONEABLE_H_
#define CLONEABLE_H_

namespace vhc {

/** Une classe de base pour tout objet cloneable polymorphiquement.
 *  Cette classe declare un constructeur de copie virtuel pure, sous forme d'une methode <code>clone()</code>. */
class Cloneable {
public:
	Cloneable();
	virtual ~Cloneable();

	/** Renvoye un pointeur sur une copie de surface de cet objet cloneable.
	 *  Toute sous-classe devra implementer cette methode.
	 *  <b>ATTENTION</b>: comme <code>clone()</code> est une methode de fabrication, la responsabilite de gestion de memoire est transmise a l'appelant. */
	virtual Cloneable* clone() const = 0;

};

}

#endif /* CLONEABLE_H_ */
