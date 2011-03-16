/*
 * Particle.h
 *
 *  Created on: Mar 9, 2011
 *      Author: jakob
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <sstream>
#include "Vector3D.h"
#include "Printable.h"

namespace vhc {

/** Classe representant une particule.
 *  TODO ajouter facteur gamma, energie, constructeur etc...*/
class Particle: public Printable {

private:

	/** Position de cette particule. */
	Vector3D position;

	/** Vitesse de cette particule. */
	Vector3D velocity;

	/** Force resultante sur cette particule. */
	Vector3D force;

	/** Masse de cette particlue. */
	double mass;

	/** Charge de cette particule. */
	double charge;

public:


	Particle(const Vector3D& position0, double mass, double charge):
			position(position0),
			velocity(0, 0, 0),
			force(0, 0, 0),
			mass(mass),
			charge(charge)
	{};


	/** Retourne la position de cette particule. */
	Vector3D getPosition() const {return position;}

	/** Affecte la position de cette particule. */
	void setPosition(const Vector3D& pos) {position = pos;}

	/** Retourne la force resultante sur cette particule. */
	Vector3D getForce() const {return force;}

	/** Affecte la force resultante sur cette particule. */
	void setForce(const Vector3D& f) {force = f;}

	/** Applique une force sur cette particule. */
	void applyForce(const Vector3D& f) {force = force + f;}

	/** Retourne la masse de cette particule. */
	double getMass() const {return mass;}

	/** Retourne la charge de cette particule. */
	double getCharge() const {return charge;}

	/** Retourne la vitesse de cette particule. */
	Vector3D getVelocity() const {return velocity;}

	/** Retourne une representation en chaine de ce vecteur. */
	std::string toString() const {
		std::stringstream s;
		s << "Particle:" << "\n";
		s << "\tPosition: " << position << "\n";
		s << "\tVelocity: " << velocity << "\n";
		s << "\tMass: " << mass << "\n";
		s << "\tCharge: " << charge << "\n";
		s << "\tForce: " << force << "\n";
		return s.str();
	}

};

}

#endif /* PARTICLE_H_ */
