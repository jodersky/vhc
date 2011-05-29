/*
 * Interactor.h
 *
 *  Created on: May 26, 2011
 *      Author: jakob
 */

#ifndef INTERACTOR_H_
#define INTERACTOR_H_

#include "events.h"

namespace vhc {

class Accelerator;

/** Classe de base representant un moyen d'inclure les forces inter-particules dans la simulation.
 *  D'abord on souscrit un interacteur a une source d'evenements de paticules (typiquement des faisceaux).
 *  Lors de l'ajout d'une particule, l'interacteur a donc la possibilite d'inclure la particule dans
 *  la simulation de forces inter-particules.
 *  Quand la methode <code>applyInteractions()</code> est appelee, les forces inter-particules de tous
 *  les particules de cet interacteur sont appliques. */
class Interactor: public Listener< ParticleAddedEvent >, public Listener< ParticleRemovedEvent > {

public:
	Interactor();
	virtual ~Interactor();

	/** Simule tous les interactions entre particules. */
	virtual void applyInteractions() = 0;

	/** Appelee quand l'accelerateur contenant cet interacteur est ferme. */
	virtual void acceleratorClosed(const Accelerator& acc);

	/** Appelee lors de l'ajout d'une particule. Ajoute typiquement la particule au particules simules par cet interacteur. */
	virtual void react(const ParticleAddedEvent& event) = 0;

	/** Appelee lors de l'enlevement d'une particule. Enleve typiquement la particule des particules simules par cet interacteur. */
	virtual void react(const ParticleRemovedEvent& event) = 0;
};

}

#endif /* INTERACTOR_H_ */
