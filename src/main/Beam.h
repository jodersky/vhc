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

namespace vhc {

class Beam {

protected:

	/** Particule de reference. */
	Particle referenceParticle;

	/** Particules contenus dans ce faisceau. */
	std::list<Particle*> particles;

	/** Coefficient des macrosparticules. */
	int lambda;

	int quantity;

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

	/** Initialise ce faisceau a partir de la particule de reference. Comme il s'agit d'une sorte de factory method (au sens vraiment large),
	 *  la responsabilite de gestion des particules appartient a ce faisceau (et non a la sous-classe). */
	virtual void init(const Particle& referenceParticle, int quantity, int lambda) = 0;


public:

	/** Cree un nouveau faisceaux.
	 *  <b>ATTENTION:</b> un `Beam' est abstrait et n'initialise pas les particules a partir de la reference.
	 *  C'est au client de faire cela! */
	Beam(const Particle& referenceParticle, int quantity, int lambda);

	virtual ~Beam();

	/** Retourne la quantite de particules contenus dans ce faisceau. */
	int getSize() const;

	/** Retourne le coefficient des macroparticules. */
	int getLambda() const;

	/** Retourne la particule de reference. */
	const Particle& getReferenceParticle() const;

	/** Retourne l'energie moyenne des particules dans ce faisceau. */
	double getAverageEnergy() const;

	/** Retourne l'emmitance verticale de ce faisceau. */
	double getVerticalEmittance() const;

	/** Retourne l'emmitance horizontale de ce faisceau. */
	double getHorizontalEmittance() const;

	/** Retourne coefficient des ellipses de phases vertical. */
	double getVerticalA11() const;

	/** Retourne coefficient des ellipses de phases vertical. */
	double getVerticalA12() const;

	/** Retourne coefficient des ellipses de phases vertical. */
	double getVerticalA22() const;

	/** Retourne coefficient des ellipses de phases horizontal. */
	double getHorizontalA11() const;

	/** Retourne coefficient des ellipses de phases horizontal. */
	double getHorizontalA12() const;

	/** Retourne coefficient des ellipses de phases horizontal. */
	double getHorizontalA22() const;

};

}

#endif /* BEAM_H_ */
