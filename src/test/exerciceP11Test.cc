/*
 * exerciceP11Test.cc
 *
 *  Created on: 5 mai 2011
 *      Author: christian
 */


#include <iostream>
#include "exceptions.h"
#include "Dipole.h"
#include "FODO.h"
#include "Accelerator.h"
#include "Particle.h"

using namespace std;
using namespace vhc;


// Construction par boucle à bannir car ne garantit pas que les entrées-sorties de séléments soient cohérents.
// De plus il n'extise aucune moyen d'initaliser ces attributs automatiquement.
Accelerator* creatAcc() {


	Accelerator* acc = new Accelerator();

	for(unsigned int i(0); i<4; ++i){

		FODO* fodo = new FODO(Vector3D(0,0,0),Vector3D(1, 0,0),	0.2	,	1.	,	1.2);
//									entry			exit		Re		l		b
		acc->add( *fodo );

		Dipole* d = new Dipole(Vector3D(0,0,0),Vector3D(1,2,0),	0.1,	1,	Vector3D(0,0,5.89158));
//								entry				exit				Re		Rc	B
		acc->add( *d );
	}
		acc->close();

	return acc;
}

Accelerator* creatAccChap() {

	Accelerator* acc = new Accelerator();

	FODO* fodo1 = new FODO(Vector3D(3,2,0),Vector3D(3,-2,0),		0.2	,	1.	,	1.2);
//									entry			exit			Re		l		b
	Dipole* d1 = new Dipole(Vector3D(3,-2,0),Vector3D(2,-3,0),		0.1,	1,	Vector3D(0,0,5.89158));
//									entry			exit			Re		Rc	B
	FODO* fodo2 = new FODO(Vector3D(2,-3,0),Vector3D(-2,-3,0),		0.2	,	1.	,	1.2);
//									entry			exit			Re		l		b
	Dipole* d2 = new Dipole(Vector3D(-2,-3,0),Vector3D(-3,-2,0),	0.1,	1,	Vector3D(0,0,5.89158));
//									entry			exit			Re		Rc	B
	FODO* fodo3 = new FODO(Vector3D(-3,-2,0),Vector3D(-3,2,0),		0.2	,	1.	,	1.2);
//									entry			exit			Re		l		b
	Dipole* d3 = new Dipole(Vector3D(-3,2,0),Vector3D(-2,3,0),		0.1,	1,	Vector3D(0,0,5.89158));
//									entry			exit			Re		Rc	B
	FODO* fodo4 = new FODO(Vector3D(-2,3,0),Vector3D(2,3,0),		0.2	,	1.	,	1.2);
//									entry			exit			Re		l		b
	Dipole* d4 = new Dipole(Vector3D(2,3,0),Vector3D(3,2,0),		0.1,	1,	Vector3D(0,0,5.89158));
//									entry			exit			Re		Rc	B

	acc->add(*fodo1); acc->add(*d1); acc->add(*fodo2); acc->add(*d2);
	acc->add(*fodo3); acc->add(*d3); acc->add(*fodo4); acc->add(*d4);

	acc->close();

	return acc;
}

void fillWithParts(Accelerator* acc){

	Particle* p1 = new Particle(
			Vector3D(3.01,0,0),//position
			constants::PROTON_MASS,//mass
			constants::E,//charge
			2*constants::GeV,//energy
			Vector3D(0,-1,0));//direction

	Particle* p2 = new Particle(
			Vector3D(2.99,0,0),//position
			constants::PROTON_MASS,//mass
			constants::E,//charge
			2*constants::GeV,//energy
			Vector3D(0,-1,0));//direction

	acc->add(*p1); acc->add(*p2);

	acc->close();

}

void makeTest(){

	Accelerator* a = creatAccChap();

	fillWithParts(a);


	cout<< *a << "\n";

	int it(4);

	cout<<"Beginning simulation...\n";

	for(unsigned int j(0); j<it; ++j){
		a->step(10E-11);
		cout<<"after "<<j+1<<" step :"<<endl<<"part 1 :"<< (a->getParticles().front()->toString()) <<endl;
		cout<<"after "<<j+1<<" step :"<<endl<<"part 2 :"<< (a->getParticles().back()->toString()) <<endl;
	}
}

int main() {

	makeTest();

	return 0;
}
