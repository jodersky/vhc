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

	StraightElement(Vector3D(0,0,0), Vector3D(1,2,0), 0.2);

	try {
	CurvedElement(Vector3D(0,0,0), Vector3D(1,0,0), 0.2, 1.0 / 0.4);
	} catch (Exception& e) {
		cerr << e.toString() << endl;
	};

	return 0;
}

