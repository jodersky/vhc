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

/** Classe représentant une particule.
 * TODO poser question sur l'energie, gamma, qdm
 * TODO rajouter un pointeur sur l'element dans lequel la particule se trouve*/
class Particle: public Printable {

private:

	/** Position de cette particule. */
	Vector3D position;

	/** Vitesse de cette particule. */
	Vector3D velocity;

	/** Force résultante sur cette particule. */
	Vector3D force;

	/** Masse de cette particule. */
	double mass;

	/** Charge de cette particule. */
	double charge;

	double gamma;

public:


	Particle(const Vector3D& position, double mass, double charge):
			position(position),
			velocity(0, 0, 0),
			force(0, 0, 0),
			mass(mass),
			charge(charge)
	{};

	Particle(const Vector3D& position, double mass, double charge, double energy, const Vector3D& direction):
		position(position),
		velocity(constants::c * sqrt(1 - (mass * mass) / (energy * energy)) * direction.unit()),
		gamma(energy / (mass * constants::c2)),
		force(0, 0, 0),
		mass(mass),
		charge(charge)
	{};


	/** Retourne la position de cette particule. */
	Vector3D getPosition() const {return position;}

	/** Affecte la position de cette particule. */
	void setPosition(const Vector3D& pos) {position = pos;}

	/** Retourne la force résultante sur cette particule. */
	Vector3D getForce() const {return force;}

	/** Affecte la force résultante sur cette particule. */
	void setForce(const Vector3D& f) {force = f;}

	/** Applique une force sur cette particule. */
	void applyForce(const Vector3D& f) {force = force + f;}

	void applyMagneticForce(const Vector3D& b, double dt) {
		if (b != Vector3D::Null) {
			Vector3D f = charge * velocity.cross(b);
			force = force + f.rotate(velocity.cross(f), (dt * f.norm()) / (2 * gamma * getMassKg() * velocity.norm()));
		}
	}

	/** Retourne la masse de cette particule en GeV. */
	double getMass() const {return mass;}

	/** Retourne la masse de cette particule en Kg. */
	double getMassKg() const {return mass * 1E-9 * constants::e / constants::c2;}

	/** Retourne la charge de cette particule. */
	double getCharge() const {return charge;}

	/** Retourne la vitesse de cette particule. */
	Vector3D getVelocity() const {return velocity;}

	void setVelocity(const Vector3D& v) {
		velocity = v;
		gamma = 1.0 / sqrt(1.0 - v.normSquare() / constants::c2);
	}

	//GeV
	double getEnergy() const {return gamma * mass * constants::c2;}

	double getGamma() const {return gamma;}

	/** Retourne une représentation en chaîne de cette particule. */
	virtual std::string toString() const {
		std::stringstream s;
		s << "Particle:"	<< "\n";
		s << "\tposition: "	<< position	<< "\n";
		s << "\tvelocity: "	<< velocity	<< "\n";
		s << "\t|v|: "		<< velocity.norm() << "\n";
		s << "\tgamma: "	<< gamma << "\n";
		s << "\tmass:     "	<< mass		<< "\n";
		s << "\tcharge:   "	<< charge	<< "\n";
		s << "\tforce:    "	<< force;
		return s.str();
	}



};

}

#endif /* PARTICLE_H_ */
