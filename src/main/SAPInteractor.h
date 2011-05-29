/*
 * SAPInteractor.h
 *
 *  Created on: May 29, 2011
 *      Author: jakob
 */

#ifndef SAPINTERACTOR_H_
#define SAPINTERACTOR_H_

#include <vector>
#include <map>
#include "Interactor.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

/** Sweep and Prune Interactor. Interacteur de particules qui utilise une methode de "sweep and prune" pour determiner
 *  les interactions entre particules. Cette methode consiste a:
 *  <ol>
 *  <li> Projetter les particules le long de l'accelerateur. </li>
 *  <li> Trier les particules en fonction de leur position lineaire, obtenue au point precedent. </li>
 *  <li> Parcourir les particules deux a deux et verifier si ils sont proches dans un rayon d'interaction.
 *       Bien que cette methode semble avoir une complexite de O(n^2), en realite il faut faire beaucoup moins de tests.
 *       Ceci car les particules sont tries en fonction de leur position lineaire et on peut donc arreter de tester des qu'on rencontre une
 *       particules qui est plus loin que la premiere. </li>
 *  </ol>
 *  La partie la plus couteuse de cet algorithme est le tri. Or en utilisant la methode de trie quicksort, on obtient une complexite de O(n log n).
 *  Une amelioration possible et assez facile serait d'utiliser un insert sort apres avoir utilise le quicksort quelues temps.
 *  L'idee est qu'un insert sort est presque de complexite lineaire pour une collection presque entierement triee. On ferait donc l'assomption que
 *  l'ordre des particules ne changerait plus beaucoup apres quelque temps dans l'accelerateur. Cette methode donnerait une complexite de presque O(n) */
class SAPInteractor: public Interactor {
protected:

	/** Contient une particule et sa position lineaire associee. */
	class LinearParticleContainer {
	private:
		Particle *const particle;
		double linear;
	public:
		LinearParticleContainer(Particle *const particle, double linear = 0);
		Particle *const getParticle() const;
		double getLinear() const;
		void setLinear(double value);
	};

	/** Particules geres par cet interacteur. */
	std::vector<LinearParticleContainer*> particles;

	/** Dictionnaire associant un element a sa position lineaire. */
	std::map<Element*, double> elementLinears;

	/** Projette tous les particules sur l'accelerateur afin de les lineariser. */
	void linearizeParticles();

	/** Compare la position lineaire de deux particules.
	 *  @return true si la position lineaire de la premiere particules est plus petite que la deuxieme */
	static bool compare(LinearParticleContainer *const p1, LinearParticleContainer *const p2);

	/** Rayon d'interaction. */
	double interactionRadius;

public:

	/** Rayon d'interaction par defaut. */
	static const double DEFAULT_INTERACTION_RADIUS;

	SAPInteractor();
	virtual ~SAPInteractor();

	/** Retourne le rayon d'interaction. L'interaction entre particules separes de plus de deux fois ce rayon,
	 *  selon leur projection, est neglige. */
	double getInteractionRadius() const;

	/** Affect le rayon d'interaction. */
	void setInteractionRadius(double value);

	/** Appelee quand l'accelerateur contenant cet interacteur est ferme. */
	virtual void acceleratorClosed(const Accelerator& acc);

	/** Appelee lors de l'ajout d'une particule. Ajoute la particule au particules simules par cet interacteur. */
	virtual void react(const ParticleAddedEvent& event);

	/** Appelee lors de l'enlevement d'une particule. Enleve la particule des particules simules par cet interacteur. */
	virtual void react(const ParticleRemovedEvent& event);

	virtual void applyInteractions();
};

}

#endif /* SAPINTERACTOR_H_ */
