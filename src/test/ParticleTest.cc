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
	return constants::e / constants::c2 * 1E9 * mGeV;
}

int main() {
	Vector3D entry = Vector3D(0, 10, 0);
	Vector3D exit =  Vector3D(10, 0, 0);
	double sectionRadius = 0.2;
	double curvature = 0.1;
	Vector3D direction = entry.cross(Vector3D::k);

	double mass = 5.1E-4; //GeV
	double charge = constants::e; //C
	double energy = 1; //GeV


	particle = new Particle(entry, mass, charge, energy, direction);
	double Bz = particle->getGamma() * particle->getMassKg() * curvature * particle->getVelocity().norm() / particle->getCharge();
	cout << Bz << endl;
	element = new Dipole(entry, exit, sectionRadius, curvature, Vector3D::k * Bz);

	cout << *element << endl;
	double t = 0;
	double h = 1E-12;
	char c('0');
	bool hit = false;
	do {
		if (element->isOutside(*particle)) hit = true;
		cout << "t = " << t << endl;
		step(h);
		t += h;
		cin.get(c);
	} while (c != 'c' && !hit);

	if (hit) {
		cout << "Particle hit the wall!!!" << endl;
	}



	delete particle;
	delete element;
	return 0;
}

void step(double h) {
	particle->applyMagneticForce(element->magneticFieldAt(particle->getPosition()), h);

	Vector3D a = particle->getForce() / (particle->getGamma() * particle->getMassKg());
	particle->setVelocity(particle->getVelocity() + a * h);
	particle->setPosition(particle->getPosition() + particle->getVelocity() * h);
	cout << *particle << endl;
	particle->setForce(Vector3D::Null);
}

