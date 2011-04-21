/*
 * ParticleTest.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
#include "StraightElement.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "Particle.h"
#include "Vector3D.h"

using namespace vhc;
using namespace std;

Element* element = NULL;
Particle* particle = NULL;


void step(double h);

double toKg(double mGeV) {
	return constants::E / constants::C2 * 1E9 * mGeV;
}

int main() {
	Vector3D entry = Vector3D(0, 10, 0);
	Vector3D exit =  Vector3D(10, 0, 0);
	double sectionRadius = 0.2;
	double curvature = 0.1;
	Vector3D direction = entry.cross(Vector3D::k);

	double mass = 9.11E-31;
	double charge = constants::E;
	double energy = 1 * 1E9 * constants::E;


	particle = new Particle(entry, mass, charge, energy, direction);
	double Bz = particle->getGamma() * particle->getMass() * curvature * particle->getVelocity().norm() / particle->getCharge();
	cout << Bz << endl;
	element = new Dipole(entry, exit, sectionRadius, curvature, Vector3D::k * Bz);

	cout << *element << endl;
	double t = 0;
	double h = 1E-12;
	char c('0');
	bool hit = false;
	do {
		if (element->hasHit(*particle)) hit = true;
		cout << "t = " << t << endl;
		step(h);
		t += h;
		//cin.get(c);
	} while (false);

	if (hit) {
		cout << "Particle hit the wall!!!" << endl;
	}



	delete particle;
	delete element;
	return 0;
}

void step(double h) {
	cout << *particle << endl;
	particle->applyMagneticForce(element->magneticFieldAt(particle->getPosition()), h);

	Vector3D a = particle->getForce() / (particle->getGamma() * particle->getMass());
	particle->setVelocity(particle->getVelocity() + a * h);
	particle->setPosition(particle->getPosition() + particle->getVelocity() * h);
	particle->setForce(Vector3D::Null);
}

