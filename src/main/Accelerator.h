/*
 * Accelerator.h
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
#include <list>
#include "Vector3D.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

/** Représente un accélérateur. Cette classe contient en particulier une méthode
 *  qui fait évoluer les particules qu'elle contient. */
class Accelerator: public Printable {
private:

	/** Constructeur de copie ne faisant rien. */
	Accelerator (Accelerator const& other) {}

	/** Opérateur '=' ne faisant rien. */
	void operator= (Accelerator const& other) {}

protected:

	typedef std::list<Particle*> ParticleCollection;
	typedef std::list<Element*>  ElementCollection;

	typedef ParticleCollection::iterator ParticleIterator;
	typedef ElementCollection::iterator ElementIterator;


	/** Collection d'elements contenus dans cet accelerateur. */
	ElementCollection elementCollec;

	/** Collection de particules contenus danc cet accelerateur. */
	ParticleCollection particleCollec;

	/** Autorise les accelerateurs lineaires.
	 *  @see enableLinear */
	bool allowLinear;

	/** Indique l'etat ferme de l'accelarateur.
	 *  @see close */
	bool closed;

	/** Initialize les particules en leur attribuant l'element dans lequel ils sont contenus.
	 *  Les particules non-contenus sont supprimes de l'accelerateur. */
	void initializeParticles();

	/** Met a jour les particules en leur attribuant l'element dans lequel ils sont contenus.
	 *  Contrairement a <code>initializeParticles()</code>, les elements consideres sont:
	 *  - l'element actuel de la particule
	 *  - l'element precedent
	 *  - l'element suivant
	 *  Si la particule se situe a cote de son element, elle est supprimee de l'accelerateur.
	 *  Attention: si la particule saute un element, elle est tout de meme consideree comme etant dans l'element suivant (ou precedent)! Ceci
	 *  peut survenir si un element est trop petit ou si la simulation est faite avec des pas de temps trop grands. */
	void updateParticles();

public:

	/** Cree un nouveau accelerateur vide.
	 *  */
	Accelerator ();

	virtual ~Accelerator();

	/** Copie un élément dans l'accélérateur.
	 *  L'accelerateur est ouvert en ajoutant un element. */
	Element& add(const Element& element);

	/** Copie une particule dans l'accélérateur. */
	Particle& add(const Particle& particle);

	/** Retourne la liste d'elements contenus dans cet accelerateur.
	 *  <b>ATTENTION:</b> les elements peuvent etre supprimes sans preavis par l'accelerateur! */
	const ElementCollection & getElements() const;

	/** Retourne la liste des particules contenus dans cet accelerateur.
	 *  <b>ATTENTION:</b> les particules peuvent etre supprimes sans preavis par l'accelerateur! */
	const ParticleCollection & getParticles() const;

	/** Ferme l'accelerateur.
	 *  En invoquant cette methode, la continuite des elements est verifiee et les particules sont attribues leurs elements respectifs.
	 *  @throws UnsupportedOperationException si les elements sauf le dernier ne sont pas continus
	 *  @throws UnsupportedOperationException si le dernier element n'est pas continu et que les accelerateurs
	 *  lineaires ne sont pas autorises. */
	void close();

	/** Efface tous les éléments et les particules.
	 *  Ouvre l'accelerateur. */
	void clear();

	/** Autorise ou interdit la linearite de cet accelerateur.
	 *  Un accelerateur lineaire peut ne pas etre continu en son dernier element. C'est-a-dire que ce n'est pas une boucle fermee. */
	void enableLinear(bool value);

	/** Fait évoluer l'accélérateur d'un laps de temps dt. */
	void step(double dt);

	/** Retourne une représentation en chaîne de caractères de cet accélérateur. */
	virtual std::string toString() const;
};

}

#endif /* ACCELERATOR_H_ */
