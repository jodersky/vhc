/*
 * ElementsSimulationTest.cc
 *
 *  Created on: 4 mai 2011
 *      Author: christian
 */


#include <iostream>
#include "exceptions.h"
#include "CurvedElement.h"
#include "Dipole.h"
#include "FODO.h"
#include "Quadrupole.h"
#include "Vector3D.h"
#include "Accelerator.h"
#include <vector>

using namespace std;
using namespace vhc;

Particle* standpart(Accelerator* acc){

	Particle* sp = new Particle(
			acc->getElements().front()->getExitPosition(),//position, on le met à la fin des éléments
			constants::PROTON_MASS,//mass
			constants::E,//charge
			2*constants::GeV,//energy
			Vector3D(1, 0,0));//direction

	return sp;
};

// Ce fichier teste les simulations de chaque type différent d'Element existant.
int main() {

	Dipole* d = new Dipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.2, 0.2, Vector3D::Null, NULL);
	Accelerator* a1 = new Accelerator();
	a1->add(*d);

	Quadrupole* fq = new Quadrupole(Vector3D(0,0,0), Vector3D(1, 0, 0), 0.1, 1.2);
	Accelerator* a2 = new Accelerator();
	a2->add(*fq);

	FODO* fodo = new FODO(Vector3D(0,0,0), Vector3D(1, 0,0), 0.2, 0.2, 3);
	Accelerator* a3 = new Accelerator();
	a3->add(*fodo);

	vector < Accelerator* > va;
	va.push_back(a1); va.push_back(a2); va.push_back(a3);

	// on va mettre dans chaque accélérateur une particule d'attributs standards,
	// mais toutes situées à l'entrée de chaque accélérateur.
	for(unsigned int i(0); i<va.size(); ++i){

		//on construit trois fois une particule standard initialisée au début de chaque accélérateur
		Particle* p = standpart( va[i] );

		//on met ensuite ces particules dans les accélérateurs
		va[i]->add(*p);

		va[i]->enableLinear(true);

		va[i]->close();

		//nbr d'iterations de la simulation
		int it(14);

		//etat initial
		cout<<*va[i]<<endl;

		//test de simulation
		for(unsigned int j(0); j<it; ++j){
			va[i]->step(10E-11);
			if(!(va[i]->getParticles()->empty())){
				cout<<"after "<<j+1<<" step :"<<endl << (va[i]->getParticles()->front()->toString())<<endl;
			}
		}

	}

	return 0;
}

