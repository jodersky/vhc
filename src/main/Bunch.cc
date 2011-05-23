/*
 * Bunch.cc
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */

#include <math.h>
#include "Bunch.h"
#include "random.h"
#include "Vector3D.h"
#include "Element.h"

namespace vhc {

Bunch::Bunch(const Particle& referenceParticle, int quantity, int lambda, double standardDeviation, double length, double targetEmittance, double A12, double A22):
		Beam(referenceParticle, quantity, lambda),
		standardDeviation(standardDeviation),
		length(length),
		targetEmittance(targetEmittance),
		A12(A12),
		A22(A22) {}

Bunch::~Bunch() {

}

void Bunch::initializeParticles() {
	create(getLength());

}

void Bunch::create(double dt) {
	random::seed(0);
	double debit = quantity / length;
	double fraction(debit * dt); // debit "vrai", mais a priori non entier
	int number(fraction);      // partie entière
	fraction -= number;        // partie fractionnaire
	// on ajoute 1 au  hasard, proportionnellement à la partie fractionnaire :
	if ( random::uniform(0.0, 1.0) < fraction ) ++number;

	//calculation des proprietes des particules
	for (int i = 0; i < quantity / lambda; ++i) {
		Particle* particle = getReferenceParticle().clone();

		double sa[2]; // = [r, z]
		double va[2]; // = [vr, vz]
		//calculation de r, vr, z et vz
		for (int i = 0; i < 2; ++i) {
			double A11 = getA11();
			double A12 = getA12();
			double A22 = getA22();

			double theta = atan(2 * A12 / (A11 - A22));
			double a = A11 * cos(theta) * cos(theta) + 2 * A12 * cos(theta) * sin(theta) + A22 * sin(theta) * sin(theta);
			double b = A11 * sin(theta) * sin(theta) + 2 * A12 * cos(theta) * sin(theta) + A22 * cos(theta) * cos(theta);

			double x = random::gaussian(0, sqrt(getTargetEmittance() / a));
			double y = random::gaussian(0, sqrt(getTargetEmittance() / b));

			sa[i] = cos(theta) * x + sin(theta) * y;
			va[i] = -sin(theta) * x + cos(theta) * y;
		}

		double r = sa[0];
		double vr = va[0];

		double z = sa[1];
		double vz = va[1];

		double norm = random::gaussian(getReferenceParticle().getVelocity().norm(), getStandardDeviation());

		Vector3D u = getReferenceParticle().getElement()->getHorizontalAt(getReferenceParticle().getPosition());
		Vector3D v = vr * u  + vz * Vector3D::k + sqrt(norm * norm - vr * vr - vz * vz) * u.cross(Vector3D::k);

		//composante s de position
		double s = random::gaussian(0, getLength());

		//ecart de position
		Vector3D dp = r * u + z * Vector3D::k + s * u.cross(Vector3D::k);

		particle->setMass(getReferenceParticle().getMass() * getLambda());
		particle->setCharge(getReferenceParticle().getCharge() * getLambda());
		particle->translate(dp);

		particles.push_back(particle);
	}

}

Bunch* Bunch::clone() const {
	return new Bunch(*this);
}


double Bunch::getA11() const {
	return (1 + getA12() * getA12() ) / getA22();
}

double Bunch::getA12() const {
	return A12;
}

double Bunch::getA22() const {
	return A22;
}

double Bunch::getStandardDeviation() const {
	return standardDeviation;
}

double Bunch::getLength() const {
	return length;
}

double Bunch::getTargetEmittance() const {
	return targetEmittance;
}

}
