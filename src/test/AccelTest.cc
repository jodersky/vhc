/*
 * testAccel1.cc
 *
 *  Created on: 23 mars 2011
 *      Author: christian
 */


#include "Accelerator.h"
#include "Dipole.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace vhc;
/** lance le test*/
//TODO erreur sur l'affichage de p1 ===> "NAN"  <=========
int main() {
	Accelerator a;

	Dipole* d = new Dipole(Vector3D(1,0,0), Vector3D(0,-1,0), 0.1, 1, Vector3D(0,0,7), NULL);
	Particle* p1 = new Particle(Vector3D( 1.00984,-0.191837,0 ), 0.938272, 1.60217653e-19, 2, Vector3D(-210200,-2.64754e+08,0));
	Particle* p2 = new Particle(Vector3D(0.99016,-0.191837,0), 0.938272, 1.60217653e-19, 2, Vector3D(210200,-2.64754e+08,0));

	a.add(*d);
	a.add(*p1);
	a.add(*p2);

	Accelerator b;

	b.add(*d);

	Accelerator empty;

	cout << "Inspecting first accelerator..." << endl
		 << a << endl
		 << "Inspecting second accelerator..." << endl
		 << b << endl
		 << "Inspecting third accelerator..." << endl
		 << empty << endl;

	a.clear();
	b.clear();

	return 0;
}
