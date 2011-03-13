/*
 * Particle.h
 *
 *  Created on: Mar 9, 2011
 *      Author: jakob
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector3D.h"

namespace vhc {

class Particle {

private:
	Vector3D position;
	Vector3D force;
	double mass;
	double charge;

public:

	void applyForce(const Vector3D& f) {force = force + f;}

	Vector3D getPosition() const {return position;}

	void setPosition(const Vector3D& pos) {position = pos;}

	Vector3D getForce() const {return force;}

	double getMass() const {return mass;}

	double getCharge() const {return charge;}


	/*
	Vector3D getPosition() {return position;}

	Vector3D getVelocity();

	Vector3D getEnergy();

	Vector3D getGamma();

	Vector3D getMomentum();
*/
	Particle(const Vector3D& position0, double mass, double charge):
		position(position0),
		force(0, 0, 0),
		mass(mass),
		charge(charge) {};

	virtual ~Particle();
};

}

#endif /* PARTICLE_H_ */
