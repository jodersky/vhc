/*
 * exerciceP10.cc
 *
 *  Created on: 20 avr. 2011
 *      Author: christian
 */
#include "Accelerator.h"
#include "Dipole.h"
#include "StraightElement.h"
#include "Quadrupole.h"
#include "FODO.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace vhc;

//TODO erreur sur l'affichage de p1 ===> "NAN"  <========
/** Affiche la réponse de l'exercice P.10 de l'étape 5 (semaine 6) du projet.*/
int main() {

	Accelerator a;

	Dipole* d = new Dipole(
			Vector3D(1,0,0),
			Vector3D(0,-1,0),
			0.1,
			1,
			Vector3D(0,0,7),
			NULL);

	StraightElement* s = new StraightElement(
			Vector3D(0,-1,0),
			Vector3D(-1,-1,0),
			0.1);

	Quadrupole* q = new Quadrupole(
			Vector3D(-1,-1,0),
			Vector3D(-1,-2,0),
			0.1,
			1.2);

	FODO* f = new FODO(
			Vector3D(-1,-2,0),
			Vector3D(-1,0,0),
			0.1,
			1,
			1.2);

	Particle* p1 = new Particle(
			Vector3D( 1.00984,-0.191837,0 ),
			0.938272,
			1.60217653e-19,
			2,
			Vector3D(-210200,-2.64754e+08,0));

	Particle* p2 = new Particle(
			Vector3D(0.99016,-0.191837,0),
			0.938272,
			1.60217653e-19,
			2,
			Vector3D(210200,-2.64754e+08,0));

	a.add(*d);
	a.add(*s);
	a.add(*q);
	a.add(*f);
	a.add(*p1);
	a.add(*p2);

	a.enableLinear(true);
	a.close();

	cout << a << endl;
	a.clear();


	return 0;
}
