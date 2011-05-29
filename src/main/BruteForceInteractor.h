/*
 * BruteForceInteractor.h
 *
 *  Created on: May 26, 2011
 *      Author: jakob
 */

#ifndef BRUTEFORCEINTERACTOR_H_
#define BRUTEFORCEINTERACTOR_H_

#include <list>
#include "Interactor.h"
#include "Particle.h"

namespace vhc {

/** Represente un interacteur de particules a force brute.
 *  Cet interacteur considere les interactions entre tous les particules. Il n'est donc pas tres efficace (compexite O(n^2)). */
class BruteForceInteractor: public Interactor {

private:

	/** Particules simules par cet interacteur. */
	std::list<Particle*> particles;

public:
	BruteForceInteractor();
	virtual ~BruteForceInteractor();

	virtual void applyInteractions();

	/** Appelee lors de l'ajout d'une particule. Ajoute la particule au particules simules par cet interacteur. */
	virtual void react(const ParticleAddedEvent& event);

	/** Appelee lors de l'enlevement d'une particule. Enleve la particule des particules simules par cet interacteur. */
	virtual void react(const ParticleRemovedEvent& event);
};

}

#endif /* BRUTEFORCEINTERACTOR_H_ */
