/*
 * Accelerator.h
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
#include <list>
#include <memory>
#include "Vector3D.h"
#include "Particle.h"
#include "Beam.h"
#include "Element.h"
#include "Interactor.h"

namespace vhc {

/** Représente un accélérateur. Cette classe contient en particulier une méthode
 *  qui fait évoluer les particules qu'elle contient. */
class Accelerator: public Printable {

public:

	typedef std::list<Particle*> ParticleCollection;
	typedef std::list<Element*>  ElementCollection;
	typedef std::list<Beam*> BeamCollection;

	typedef ParticleCollection::iterator ParticleIterator;
	typedef ElementCollection::iterator ElementIterator;

	/** Cree un nouveau accelerateur vide, avec un interacteur de particules a force brute. */
	Accelerator ();

	/** Cree un nouveau accelerateur vide.*/
	Accelerator (Interactor* interactor);

	virtual ~Accelerator();

	/** Copie un élément dans l'accélérateur.
	 *  L'accelerateur est ouvert en ajoutant un element. */
	Element& add(const Element& element);

	/** Copie un faisceau dans cet accelerateur. */
	Beam& add(const Beam& beam);

	/** Copie une particule dans cet accelerateur.
	 *  Comme un accelerateur ne contient plus explicitement des particules, un faisceau a une particule et cree.
	 *  Cet methode reste pour des raisons de compatibilites. */
	Beam& add(const Particle& particle);

	/** Retourne la liste d'elements contenus dans cet accelerateur.
	 *  <b>ATTENTION:</b> les elements peuvent etre supprimes sans preavis par l'accelerateur! */
	const ElementCollection & getElements() const;

	/** Retourne la liste des particules contenus dans cet accelerateur.
	 *  <b>ATTENTION:</b> les particules peuvent etre supprimes sans preavis par l'accelerateur! */
	std::auto_ptr<ParticleCollection> getParticles() const;

	/** Retourne tous les faisceaux de cet accelerateur. */
	const BeamCollection& getBeams() const;

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

private:

	/** Constructeur de copie ne faisant rien. */
	Accelerator (Accelerator const& other) {}

	/** Opérateur '=' ne faisant rien. */
	void operator= (Accelerator const& other) {}

protected:

	/** Collection d'elements contenus dans cet accelerateur. */
	ElementCollection elements;

	/** Collection de faisceaux contenus dans cet accelerateur. */
	BeamCollection beams;

	/** Interacteur de particules.
	 *  @see vhc::Interactor */
	Interactor* interactor;

	/** Autorise les accelerateurs lineaires.
	 *  @see enableLinear */
	bool allowLinear;

	/** Indique l'etat ferme de l'accelarateur.
	 *  @see close */
	bool closed;

	/** Initialize les faisceaux.
	 *  Les faisceaux dont la particule de refernce n'est pas contenue dans un element
	 *  sont supprimes de l'accelerateur. */
	void initializeBeams();

};

}

#endif /* ACCELERATOR_H_ */
