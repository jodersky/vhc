/*
 * BasicTest.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: jakob
 */

#include <iostream>
#include <assert.h>
#include "exceptions.h"
#include "CurvedElement.h"
#include "Dipole.h"
#include "FODO.h"
#include "Quadrupole.h"
#include "Vector3D.h"

using namespace std;
using namespace vhc;

int main() {

	//test d'affichage
	Dipole* d = new Dipole(Vector3D(0,0,0), Vector3D(1,2,0), 0.2, 0.2, Vector3D::Null, NULL);
	cout << *d << endl;
	delete d; d = NULL;

	FODO* fodo = new FODO(Vector3D(0,0,0), Vector3D(1, 0,0), 0.2, 0.2, 3);
	cout << *fodo << endl;
	delete fodo; fodo = NULL;

	//test d'initialisation illegale
	bool caught = false;
	try {
		Dipole(Vector3D(0,0,0), Vector3D(1,0,0), 0.2, 1.0 / 0.4, Vector3D(1,2,3));
		//                                                   ^ le rayon de courbure est trop petit
	} catch (Exception& e) {
		caught = true;
	};
	assert(caught);

	Quadrupole* fq = new Quadrupole(Vector3D(0,0,0), Vector3D(1, 0, 0), 0.1, 1.2);

	//containement test
	assert(fq->isBefore(Vector3D(-0.1,0,0)));
	assert(fq->isBefore(Vector3D(-0.1,0.2,0)));
	assert(fq->isBefore(Vector3D(-0.1,3,5)));

	assert(fq->isBeside(Vector3D(0.1,0.2,0)));
	assert(fq->isBeside(Vector3D(0.3,0,3)));
	assert(fq->isBeside(Vector3D(0.5,-2,-4)));

	assert(fq->isAfter(Vector3D(1.1,0,0)));
	assert(fq->isAfter(Vector3D(1.3,0.3,-0.2)));
	assert(fq->isAfter(Vector3D(1.001,-0.04,0.02)));

	assert(fq->contains(Vector3D(0.5,0,0)));
	assert(fq->contains(Vector3D(0.99,0.1, 0)));
	assert(fq->contains(Vector3D(0.1,0.02,-0.02)));

	delete fq; fq = NULL;


	return 0;
}

