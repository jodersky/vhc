/*
 * Particle.cc
 *
 *  Created on: Mar 9, 2011
 *      Author: jakob
 */

#include "Particle.h"

namespace vhc {

Particle::Particle(const Vector3D& position, double mass, double charge):
		position(position),
		velocity(0, 0, 0),
		force(0, 0, 0),
		mass(mass),
		charge(charge),
		element(NULL)
	{};


Particle::Particle(const Vector3D& position, double mass, double charge, double energy, const Vector3D& direction):
		position(position),
		velocity(constants::C * sqrt(1 - (mass * mass * constants::C2 * constants::C2) / (energy * energy)) * direction.unit()),
		gamma(energy / (mass * constants::C2)),
		force(0, 0, 0),
		mass(mass),
		charge(charge),
		element(NULL)
	{};

Vector3D Particle::getPosition() const {return position;}

void Particle::setPosition(const Vector3D& pos) {position = pos;}

void Particle::translate(const Vector3D& dx) {position += dx;}

Vector3D Particle::getForce() const {return force;}

void Particle::setForce(const Vector3D& f) {force = f;}

void Particle::applyForce(const Vector3D& f) {force += f;}

void Particle::applyMagneticForce(const Vector3D& b, double dt) {
	if (dt != 0 && b != Vector3D::Null) {
		Vector3D f = charge * velocity.cross(b);
		applyForce(f.rotate(velocity.cross(f), asin(1.0 * (dt * f.norm()) / (2 * gamma * mass * velocity.norm()))));
	}
}

double Particle::getMass() const {return mass;}

void Particle::setMass(double m) {
	mass = m;
}

double Particle::getCharge() const {return charge;}

void Particle::setCharge(double q) {
	charge = q;
}


Vector3D Particle::getVelocity() const {return velocity;}

void Particle::setVelocity(const Vector3D& v) {
	velocity = v;
	gamma = 1.0 / sqrt(1.0 - v.normSquare() / constants::C2);
}

double Particle::getEnergy() const {return gamma * mass * constants::C2;}

double Particle::getGamma() const {return gamma;}

std::string Particle::toString() const {
	std::stringstream s;
	s << "Particle:"	<< "\n";
	s << "\tposition: "	<< position	<< "\n";
	s << "\tvelocity: "	<< velocity;
	s << "\tnorm: "		<< velocity.norm() << "\n";
	s << "\tenergy:   "	<< getEnergy()	<< "\n";
	s << "\tforce:    "	<< force << "\n";
	s << "\tgamma: "	<< gamma << "\n";
	s << "\tmass:     "	<< mass		<< "\n";
	s << "\tcharge:   "	<< charge	<< "\n";
	return s.str();
}

Particle* Particle::clone() const {return new Particle(*this);}

Element* Particle::getElement() const {return element;}

void Particle::setElement(Element* element) {this->element = element;}


} //vhc
