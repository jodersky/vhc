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
#include "constants.h"

namespace vhc {

/** Classe representant une particule.
 * TODO poser question sur l'energie, gamma, qdm*/
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

	double energy;

public:


	Particle(const Vector3D& position, double mass, double charge):
			position(position),
			velocity(0, 0, 0),
			force(0, 0, 0),
			mass(mass),
			charge(charge)
	{};

	Particle(const Vector3D& position0, double energy, const Vector3D& direction, double mass, double charge):
		position(position),
		velocity(0, 0, 0),
		force(0, 0, 0),
		mass(mass),
		charge(charge) {

		velcocity = constants::c * sqrt(1 - (mass * mass) / (energy * energy));
	};


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

	//GeV
	double getEnergy() const {return energy;}

	double getGamma() const {return energy / (mass * constants::c2);}

	/** Retourne une representation en chaine de cette particule. */
	std::string toString() const {
		std::stringstream s;
		s << "Particle:"	<< "\n";
		s << "\tPosition: "	<< position	<< "\n";
		s << "\tVelocity: "	<< velocity	<< "\n";
		s << "\tMass: "		<< mass		<< "\n";
		s << "\tCharge: "	<< charge	<< "\n";
		s << "\tForce: "	<< force	<< "\n";
		return s.str();
	}

};

}

#endif /* PARTICLE_H_ */
