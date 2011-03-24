/*
 * BasicTest.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: jakob
 */

#include <iostream>
#include <assert.h>
#include "Element.h"
#include "CurvedElement.h"
#include "StraightElement.h"
#include "Vector3D.h"

using namespace std;
using namespace vhc;

int main() {

	//test d'affichage
	StraightElement* s = new StraightElement(Vector3D(0,0,0), Vector3D(1,2,0), 0.2);
	cout << *s << endl;
	delete s; s = NULL;

	CurvedElement* c = new CurvedElement(Vector3D(0,1,0), Vector3D(1,0,0), 0.2, 1);
	cout << *c << endl;
	delete c; c = NULL;

	//test d'initialisation illegale
	bool caught = false;
	try {
		CurvedElement(Vector3D(0,0,0), Vector3D(1,0,0), 0.2, 1.0 / 0.4);
	} catch (Exception& e) {
		caught = true;
	};
	assert(caught);


	return 0;
}

