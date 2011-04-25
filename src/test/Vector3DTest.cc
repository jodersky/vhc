/*
 * Vector3DTest.cc
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <limits>
#include "exceptions.h"
#include "Vector3D.h"

using namespace std;
using namespace vhc;


int main() {
	Vector3D vect1(1.0, 2, -0.1);
	Vector3D vect2(2.6, 3.5, 4.1);
	Vector3D vect3 = vect1;

	cout << "Vecteur 1 :";
	cout << vect1;

	cout << "Vecteur 2 :";
	cout << vect2;

	cout << "Le vecteur 1 est ";
	if (Vector3D::ae(vect1, vect2)) {
	    cout << "egal au";
	} else {
	    cout << "différent du";
	}
	cout << " vecteur 2," << endl << "et est";
	if (Vector3D::ae(vect1, vect3)) {
	    cout << "egal au";
	} else {
	    cout << "différent du";
	}
	cout << " vecteur 3." << endl;


	//addition test
	assert(Vector3D::ae(Vector3D(1, -0.9, 57683) + Vector3D(-1, 0.9, -57683), Vector3D::Null));

	//addition, multiplication test
	assert(Vector3D::ae(Vector3D(4, 0, 16) / 4, -Vector3D(0.25, 0, 1) * -4));

	//length test
	assert(Vector3D(0,3,4).norm() == 5);

	bool caught = false;
	try {
		Vector3D n = ~Vector3D::Null;
	} catch (UnsupportedOperationException& ex) {
		caught = true;
	};
	assert(caught == true);

	//vector product test
	assert(Vector3D::i.cross(Vector3D::j)==Vector3D::k);
	assert(Vector3D::j.cross(Vector3D::k)==Vector3D::i);
	assert(Vector3D::k.cross(Vector3D::i)==Vector3D::j);
	assert(Vector3D::j.cross(Vector3D::i)==-Vector3D::k);

	cout << "Vector3D: tests completed successfully" << endl;

	return 0;
}
