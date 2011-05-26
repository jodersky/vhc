/*
 * Beam.h
 *
 *  Created on: May 6, 2011
 *      Author: jakob
 */
#ifndef BEAM_H_
#define BEAM_H_

#include <list>
#include "Cloneable.h"
#include "Particle.h"
#include "Vector3D.h"
#include "events.h"

namespace vhc {

/** Classe de base pour les faisceaux. */
class Beam: public Cloneable, public Publisher<ParticleAddedEvent>, public Publisher<ParticleRemovedEvent> {

public:

	typedef std::list<Particle*> ParticleCollection;

	/** Cree un nouveau faisceau.
	 *  @param refererenceParticle particule de reference (son element ne joue pas de role)
	 *  @param quantity la quantite de particules a generer
	 *  @param lambda le facteur de macroparticules (il y aura lambda fois moins de particules dans le faisceau mais a charges et masses lambdas fois plus grands)
	 *  <b>ATTENTION:</b> un `Beam' est abstrait et n'initialise pas les particules a partir de la reference.
	 *  C'est au client de faire cela! */
	Beam(const Particle& referenceParticle, int quantity, int lambda);

	virtual ~Beam();

	/** Retourne tous les particules contenus dans ce faisceau. */
	ParticleCollection& getParticles();

	/** Met a jour les particules en leur attribuant l'element dans lequel ils sont contenus.
	 *  Contrairement a <code>Accelerator::initializeBeams()</code>, les elements consideres sont:
	 *  - l'element actuel de la particule
	 *  - l'element precedent
	 *  - l'element suivant
	 *  Si la particule se situe a cote de son element, elle est supprimee de l'accelerateur.
	 *  Attention: si la particule saute un element, elle est tout de meme consideree comme etant dans l'element suivant (ou precedent)! Ceci
	 *  peut survenir si un element est trop petit ou si la simulation est faite avec des pas de temps trop grands. */
	void updateParticles();

	/** Initialise les particules de ce faisceau.
	 *  Cette methode est appelee par la classe Accelerator. */
	virtual void initializeParticles() = 0;

	/** Simule ce faisceau pendant un pas de temps dt. */
	void step(double dt);

	/** Retourne la quantite de particules contenus dans ce faisceau. */
	int getQuantity() const;

	/** Retourne la quantite de macroparticules contenus dans ce faisceau. */
	int getSize() const;

	/** Retourne le coefficient des macroparticules. */
	int getLambda() const;

	/** Retourne la particule de reference. */
	Particle& getReferenceParticle();

	/** Retourne l'energie moyenne des particules dans ce faisceau. */
	double getAverageEnergy() const;

	/** Retourne l'emmitance verticale de ce faisceau. */
	double getVerticalEmittance() const;

	/** Retourne l'emmitance horizontale de ce faisceau. */
	double getHorizontalEmittance() const;

	/** Vide ce faisceau en supprimant tous les particules. */
	void clear();

	virtual Beam* clone() const = 0;

	//-------------------------------------------------------------------

	/** Retourne coefficient des ellipses de phases vertical. */
	virtual double getVerticalA11() const;

	/** Retourne coefficient des ellipses de phases vertical. */
	virtual double getVerticalA12() const;

	/** Retourne coefficient des ellipses de phases vertical. */
	virtual double getVerticalA22() const;

	/** Retourne coefficient des ellipses de phases horizontal. */
	virtual double getHorizontalA11() const;

	/** Retourne coefficient des ellipses de phases horizontal. */
	virtual double getHorizontalA12() const;

	/** Retourne coefficient des ellipses de phases horizontal. */
	virtual double getHorizontalA22() const;

protected:

	/** Particule de reference. */
	Particle referenceParticle;

	/** Macroparticules contenus dans ce faisceau. */
	ParticleCollection particles;

	/** Coefficient des macrosparticules. */
	int lambda;

	/** Quantite de particules contenus dans ce faisceau. */
	int quantity;

	/** Methode qui doit etre appelee par toute sous-classe pour ajouter une particule au faisceau.
	 *  Publie un <code>ParticleAddedEvent</code>. */
	void add(Particle* particle);

	/** Methode qui doit etre appelee par toute sous-classe pour supprimer une particule du faisceau.
	 *  Publie un <code>ParticleRemovedEvent</code>. */
	void remove(Particle* particle);

	/** Methode qui doit etre appelee par toute sous-classe pour supprimer une particule du faisceau.
	 *  Publie un <code>ParticleRemovedEvent</code>. */
	ParticleCollection::iterator erase(ParticleCollection::iterator i);

	/** Retourne la moyenne de la distribution horizontale de la position des particules.
	 *  (<r^2> horizontal du complement) */
	double getHR2() const;

	/** Retourne la moyenne de la distribution horizontale de la vitesse des particules.
	 *  (<v^2> horizontal du complement) */
	double getHV2() const;

	/** Retourne la moyenne de la distribution horizontale du produit de la position et de la vitesse des particules.
	 *  (<r*v>^2 horizontal du complement) */
	double getHRV2() const;

	/** Retourne la moyenne de la distribution verticale de la position des particules.
	 *  (<r^2> vertical du complement) */
	double getVR2() const;

	/** Retourne la moyenne de la distribution verticale de la vitesse des particules.
	 *  (<v^2> vertical du complement) */
	double getVV2() const;

	/** Retourne la moyenne de la distribution verticale du produit de la position et de la vitesse des particules.
	 *  (<r*v>^2 vertical du complement) */
	double getVRV2() const;

};

}

#endif /* BEAM_H_ */
