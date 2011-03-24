/*
 * BasicTest.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: jakob
 */

#include <iostream>
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
	try {
	CurvedElement(Vector3D(0,0,0), Vector3D(1,0,0), 0.2, 1.0 / 0.4);
	} catch (Exception& e) {
		cerr << e.toString() << endl;
	};


	return 0;
}

