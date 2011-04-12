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

public:


	/** Cree une nouvelle particule, de vitesse nulle.
	 *  @param position position
	 *  @param mass masse <b>[kg]</b>
	 *  @param charge charge [C] */
	Particle(const Vector3D& position, double mass, double charge):
			position(position),
			velocity(0, 0, 0),
			force(0, 0, 0),
			mass(mass),
			charge(charge)
	{};

	/** Cree une nouvelle particule avec les parametres donnees.
	 *  @param position position
	 *  @param mass masse <b>[kg]</b>
	 *  @param charge charge [C]
	 *  @param energy energie <b>[J]</b>
	 *  @param direction direction de mouvement de la particule (la longueur du vecteur n'a aucune importance) */
	Particle(const Vector3D& position, double mass, double charge, double energy, const Vector3D& direction):
		position(position),
		velocity(constants::c * sqrt(1 - (mass * mass * constants::c2 * constants::c2) / (energy * energy)) * direction.unit()),
		gamma(energy / (mass * constants::c2)),
		force(0, 0, 0),
		mass(mass),
		charge(charge)
	{};


	/** Retourne la position de cette particule. [m] */
	Vector3D getPosition() const {return position;}

	/** Affecte la position de cette particule. [m] */
	void setPosition(const Vector3D& pos) {position = pos;}

	/** Retourne la force résultante sur cette particule. [N] */
	Vector3D getForce() const {return force;}

	/** Affecte la force résultante sur cette particule. [N] */
	void setForce(const Vector3D& f) {force = f;}

	/** Applique une force sur cette particule. [N] */
	void applyForce(const Vector3D& f) {force = force + f;}

	/** Applique un champ magnetique sur cette particule durant un lapse de temps dt.
	 *  Cette application change la force resultante de la particule. [T], [s] */
	void applyMagneticForce(const Vector3D& b, double dt) {
		if (b != Vector3D::Null) {
			Vector3D f = charge * velocity.cross(b);
			force = force + f.rotate(velocity.cross(f), (dt * f.norm()) / (2 * gamma * mass * velocity.norm()));
		}
	}

	/** Retourne la masse de cette particule. [kg] */
	double getMass() const {return mass;}

	///** Retourne la masse de cette particule en Kg. */
	//double getMassGeV() const {return mass * 1E-9 * constants::e / constants::c2;}

	/** Retourne la charge de cette particule. [C] */
	double getCharge() const {return charge;}

	/** Retourne la vitesse de cette particule. [m/s]*/
	Vector3D getVelocity() const {return velocity;}

	/** Affecte vitesse de cette particule. [m/s] */
	void setVelocity(const Vector3D& v) {
		velocity = v;
		gamma = 1.0 / sqrt(1.0 - v.normSquare() / constants::c2);
	}

	/** Retourne l'energie de cette particlue. [J] */
	double getEnergy() const {return gamma * mass * constants::c2;}

	/** Retourne le facteur gamma de cette particule. [1] */
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

	virtual Particle* clone() const {return new Particle(*this);}


};

}

#endif /* PARTICLE_H_ */
