/*
 * Printable.cc
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#include "Printable.h"
#include <iostream>

namespace vhc {

Printable::~Printable() {};

//c.f. header
std::ostream& operator<< (std::ostream& output, const Printable& p) {
	output << p.toString();
	return output;
}

}
