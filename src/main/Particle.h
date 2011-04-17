/*
 * Particle.h
 *
 *  Created on: Mar 9, 2011
 *      Author: jakob
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <sstream>
#include <math.h>
#include "Vector3D.h"
#include "Printable.h"
#include "Cloneable.h"
#include "constants.h"

namespace vhc {

class Element; //forward declaration

/** Classe représentant une particule
 * TODO !!! changer le unites en SI pour la representation interne.
 * TODO poser question sur l'energie, gamma, qdm
 * TODO rajouter un pointeur sur l'element dans lequel la particule se trouve*/
class Particle: public Printable, public Cloneable {

private:

	/** Position de cette particule. [m] */
	Vector3D position;

	/** Vitesse de cette particule. [m/s] */
	Vector3D velocity;

	/** Force résultante sur cette particule. [N] */
	Vector3D force;

	/** Masse de cette particule. [kg] */
	double mass;

	/** Charge de cette particule. [C] */
	double charge;

	/** Facteur gamma de cette particule. [1] */
	double gamma;

	Element* element;

public:


	/** Cree une nouvelle particule, de vitesse nulle.
	 *  @param position position
	 *  @param mass masse <b>[kg]</b>
	 *  @param charge charge [C] */
	Particle(const Vector3D& position, double mass, double charge);

	/** Cree une nouvelle particule avec les parametres donnees.
	 *  @param position position
	 *  @param mass masse <b>[kg]</b>
	 *  @param charge charge [C]
	 *  @param energy energie <b>[J]</b>
	 *  @param direction direction de mouvement de la particule (la longueur du vecteur n'a aucune importance) */
	Particle(const Vector3D& position, double mass, double charge, double energy, const Vector3D& direction);


	/** Retourne la position de cette particule. [m] */
	Vector3D getPosition() const;

	/** Affecte la position de cette particule. [m] */
	void setPosition(const Vector3D& pos);

	/** Retourne la force résultante sur cette particule. [N] */
	Vector3D getForce() const;

	/** Affecte la force résultante sur cette particule. [N] */
	void setForce(const Vector3D& f);

	/** Applique une force sur cette particule. [N] */
	void applyForce(const Vector3D& f);

	/** Applique un champ magnetique sur cette particule durant un lapse de temps dt.
	 *  Cette application change la force resultante de la particule. [T], [s] */
	void applyMagneticForce(const Vector3D& b, double dt);

	/** Retourne la masse de cette particule. [kg] */
	double getMass() const;

	/** Retourne la charge de cette particule. [C] */
	double getCharge() const;

	/** Retourne la vitesse de cette particule. [m/s]*/
	Vector3D getVelocity() const;

	/** Affecte vitesse de cette particule. [m/s] */
	void setVelocity(const Vector3D& v);

	/** Retourne l'energie de cette particlue. [J] */
	double getEnergy() const;

	/** Retourne le facteur gamma de cette particule. [1] */
	double getGamma() const;

	/** Retourne une représentation en chaîne de cette particule. */
	virtual std::string toString() const;

	virtual Particle* clone() const;

	Element* getElement() const;
	void setElement(Element* element);

};

}

#endif /* PARTICLE_H_ */
