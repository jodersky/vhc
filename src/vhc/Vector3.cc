/*
 * Vector3.cc
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#include <iostream>
#include "Vector3.h"

using namespace std;

namespace vhc {

Vector3 Vector3::Null = Vector3(0.0, 0.0, 0.0);
Vector3 Vector3::i = Vector3(1.0, 0.0, 0.0);
Vector3 Vector3::j = Vector3(0.0, 1.0, 0.0);
Vector3 Vector3::k = Vector3(0.0, 0.0, 1.0);

ostream& operator<< (ostream& output, const Vector3& v) {
	output << v.toString();
	return output;
}

}
