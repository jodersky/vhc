/*
 * Bunch.h
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */

#ifndef BUNCH_H_
#define BUNCH_H_

#include <string>
#include "Beam.h"

namespace vhc {

/** Un bunch est un faisceau genere par une source de particules. */
class Bunch: public Beam {
protected:

	/** Ecart-type voulu. */
	double standardDeviation;

	/** Longueur de ce bunch. */
	double length;

	/** Emittance voulue. */
	double targetEmittance;

	/** Coefficient A12 de l'ellipse de phase. */
	double A12;

	/** Coefficient A22 de l'ellipse de phase. */
	double A22;

public:

	/** Cree un nouveau bunch.
	 *  @param referenceParticle particule de reference
	 *  @param quantity quantite de particules a generer
	 *  @param lambda facteur lambda
	 *  @param standardDeviation ecart-type du bunch
	 *  @param length longueur du bunch [m]
	 *  @param targetEmittance emittance voulue
	 *  @param A12 coefficient A12 de l'ellipse de phase
	 *  @param A22 coefficient A22 de l'ellipse de phase */
	Bunch(const Particle& referenceParticle, int quantity, int lambda, double standardDeviation, double length, double targetEmittance, double A12, double A22);

	virtual ~Bunch();

	virtual void initializeParticles();

	virtual Bunch* clone() const;

	/** Cree un bunch genere pendant <code>dt</code>. */
	void create(double dt);

	/** Retourne le coefficient A12 de l'ellipse de phase. */
	double getA12() const;

	/** Retourne le coefficient A22 de l'ellipse de phase. */
	double getA22() const;

	/** Retourne le coefficient A11 de l'ellipse de phase. */
	double getA11() const;

	/** Retourne l'ecart-type de ce bunch. */
	double getStandardDeviation() const;

	/** Retourne la longueur de ce faisceau. */
	double getLength() const;

	/** Retourne l'emittance voulue de ce faisceau. */
	double getTargetEmittance() const;

};

}

#endif /* BUNCH_H_ */
