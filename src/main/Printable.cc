/*
 * Printable.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#include "Printable.h"
#include <iostream>

using namespace std;

namespace vhc {

std::ostream& operator<< (ostream& output, const Printable& p) {
	output << p.toString();
	return output;
}

}
