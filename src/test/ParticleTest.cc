/*
 * ParticleTest.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#include <iostream>
#include <string>
#include <vector>
#include "StraightElement.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "Particle.h"
#include "Vector3D.h"

using namespace vhc;
using namespace std;

Particle particle(Vector3D(0,0,0), 0.2, constants::e, 450, Vector3D::i);
Element* element;


void step(double h);

int main() {
	//Particle p(Vector3D::Null, 0, 0);
	//cout << p << endl;
	element = new Dipole(Vector3D::Null, Vector3D::i-Vector3D::j, 0.2, 1.0, Vector3D(0, 0, 1) * particle.getGamma() * particle.getMass() * 1 * particle.getVelocity().norm() / particle.getCharge());
	cout << *element << endl;

	double t = 0;
	double h = 1E-9;
	char c('0');
	bool hit = false;
	do {
		//if (element->isOutside(particle)) hit = true;
		cout << particle << endl;
		step(h);
		t += h;
		cin.get(c);
	} while (c != 'x' && !hit);

	if (hit) {
		cout << "Particle hit the wall!!!" << endl;
	}


	delete element;
	return 0;
}

void step(double h) {
	particle.applyMagneticForce(element->magneticFieldAt(particle.getPosition()), h);

	Vector3D a = particle.getForce() / (particle.getGamma() * particle.getMass());
	particle.setVelocity(particle.getVelocity() + a * h);
	particle.setPosition(particle.getPosition() + particle.getVelocity() * h);

}

