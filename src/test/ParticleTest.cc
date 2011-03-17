/*
 * ParticleTest.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#include "Particle.h"
#include <iostream>
#include <string>
#include "Vector3D.h"

using namespace vhc;
using namespace std;
/** lance le test*/
int main() {
	Particle p(Vector3D::Null, 0, 0);
	cout << p << endl;
	return 0;
}
