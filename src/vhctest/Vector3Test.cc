/*
 * Vector3Test.cc
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */


#include <iostream>
#include <assert.h>
//TODO change relative include
#include "../vhc/Vector3.h"

using namespace std;
using namespace vhc;

/*#define ASSERT(x) \
	if (! (x)) { \
		cout << "ERROR!! Assert " << #x << " failed\n"; \
		cout << " on line " << __LINE__  << "\n"; \
		cout << " in file " << __FILE__ << "\n"; \
		error = true; \
	}*/

bool printTest();

int main() {
	cout << "Vector3: running tests..." << endl;
	cout << flush;

	//equality test
	assert(Vector3(1, 2, 3) == Vector3(1, 2, 3));

	//addition test
	assert(Vector3(1, -0.9, 57683) + Vector3(-1, 0.9, -57683) == Vector3::Null);

	//addition, mutliplication test
	assert(Vector3(4, 0, 16) / 4 == -Vector3(0.25, 0, 1) * -4);

	//print test
	//assert(printTest());

	//length test
	assert(Vector3(0,3,4).getLength() == 5);
	assert(Vector3(0.0, 3.0, 4.0).getUnit().getLength() == 1);

	//unit test
	Vector3 a = Vector3(0, 3, 4).getUnit();
	Vector3 b = Vector3(0, 0.6, 0.8);

	cout << "unit: " << a << " std: " << b << endl;
	cout << "x: " << (a.getX() == b.getX()) << endl;
	cout << "y: " << (a.getY() == b.getY()) << endl;
	cout << "z: " << (a.getZ() == b.getZ()) << endl;


	assert((Vector3(0, 3.0, 4.0).getUnit()) == Vector3(0, 0.6, 0.8));


	cout << "Vector3: tests completed successfully" << endl;

	return 0;
}

bool printTest() {
	cout << "PRINT TEST" << endl;
	cout << Vector3(1,2,3) << endl;
	char answer;
	do {
		cout << "Was 'Vector3(1,2,3)' displayed? (y/n)" << endl;
		cin >> answer;
	} while (answer != 'y' && answer != 'n');
	cout << "END PRINT TEST" << endl;

	if (answer == 'y') return true;
	else return false;
}
