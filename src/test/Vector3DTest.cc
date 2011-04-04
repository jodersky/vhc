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
#include "exception.h"
#include "Vector3D.h"

using namespace std;
using namespace vhc;


bool printTest();

int main() {
	//equality test
	assert(Vector3D(1, 2, 3) == Vector3D(1, 2, 3));
	assert(Vector3D(1, 2.4, 3) != Vector3D(1, 2, 3));

	//addition test
	assert(Vector3D(1, -0.9, 57683) + Vector3D(-1, 0.9, -57683) == Vector3D::Null);

	//addition, multiplication test
	assert(Vector3D(4, 0, 16) / 4 == -Vector3D(0.25, 0, 1) * -4);

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

bool printTest() {
	cout << "PRINT TEST" << endl;
	cout << Vector3D(1,2,3) << endl;
	char answer;
	do {
		cout << "Was 'Vector3D(1,2,3)' displayed? (y/n)" << endl;
		cin >> answer;
	} while (answer != 'y' && answer != 'n');
	cout << "END PRINT TEST" << endl;

	if (answer == 'y') return true;
	else return false;
}
