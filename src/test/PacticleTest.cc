/*
 * PacticleTest.cc
 *
 *  Created on: Apr 25, 2011
 *      Author: jakob
 */

#include <iostream>
#include "constants.h"
#include "Particle.h"
#include "Vector3D.h"

using namespace std;
using namespace vhc;
using namespace constants;

int main() {
	Particle p1 = Particle(Vector3D::Null, PROTON_MASS, E, 1 * GeV, Vector3D::i);
	Particle p2 = Particle(Vector3D(5,3,2), ELECTRON_MASS, E, 1.5 * GeV, Vector3D::j);
	Particle p3 = p1;

	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;


	return 0;
}
