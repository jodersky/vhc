/*
 * testAccel1.cc
 *
 *  Created on: 23 mars 2011
 *      Author: christian
 */


#include "Accelerator.h"
#include "Dipole.h"
#include "FODO.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace vhc;

//TODO erreur sur l'affichage des particules en général  ===> "NAN"  <=========

/** Test d'affichage.*/
void printTest() {

	cout<<"This is the print test running."<<endl;

	Accelerator a;

	Dipole* d = new Dipole(Vector3D(1,0,0), Vector3D(0,-1,0), 0.1, 1, Vector3D(0,0,7), NULL);
	Particle* p1 = new Particle(
			Vector3D( 1.00984,-0.191837,0 ),//position
			constants::PROTON_MASS,//mass
			constants::E,//charge
			2*constants::GeV,//energy
			Vector3D(-1,-1,0));//direction

	Particle* p2 = new Particle(
			Vector3D(0.99016,-0.191837,0),
			constants::PROTON_MASS,//mass
			constants::E,//charge
			2*constants::GeV,//energy
			Vector3D(1,-1,0));//direction

	a.add(*d);
	a.add(*p1);
	a.add(*p2);

	Accelerator b;

	b.add(*d);

	Accelerator empty;


	//TODO la maille FODO n'est pas comptée comme un seul élément qui en contient d'autres, mais comme un seul.
	cout << "Inspecting first accelerator..." << endl
		 << a << endl
		 << "Inspecting second accelerator..." << endl
		 << b << endl
		 << "Inspecting third accelerator..." << endl
		 << empty << endl;

	a.clear();
	b.clear();
}

/** Construit un accélérateur standard sans particule et renvoie un pointeur dessus.*/
Accelerator* standardAccelerator() {
	FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.2, 1.0, 5.0);
	Dipole e2 = Dipole(e1.getExitPosition(), Vector3D(2, -3, 0), 0.2, 1);
	FODO e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.2, 1, 5.0);
	Dipole e4 = Dipole(e3.getExitPosition(), Vector3D(-3, -2, 0), 0.2, 1);
	FODO e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.2, 1.0, 5.0);
	Dipole e6 = Dipole(e5.getExitPosition(), Vector3D(-2, 3, 0), 0.2, 1);
	FODO e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.2, 1.0, 5.0);
	Dipole e8 = Dipole(e7.getExitPosition(), e1.getEntryPosition(), 0.2, 1);
	Accelerator* acc = new Accelerator();
	acc->add(e1);
	acc->add(e2);
	acc->add(e3);
	acc->add(e4);
	acc->add(e5);
	acc->add(e6);
	acc->add(e7);
	acc->add(e8);

	acc->close();

	return acc;
}

/** Test de simulateur.*/
void simulatorTest() {

	cout<<"This is the simulator test running."<<endl;

	Accelerator* a = standardAccelerator();

	Particle p1 (a->getElements().front()->getEntryPosition(), 9.11E-31, constants::E);

	a->step(1.);

	a->clear();

	delete a;
}

/** Lance les tests.*/
int main() {

	simulatorTest();

	printTest();

	return 0;
}
