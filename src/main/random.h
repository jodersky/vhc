/*
 * random.h
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */

#ifndef RANDOM_H_
#define RANDOM_H_
#include <cstdlib>
#include <time.h>

namespace vhc {

namespace random {

void seed(unsigned int s);

double uniform(double a, double b);

double gaussian(double average, double standardDeviation);

} //random

} //vhc
#endif /* RANDOM_H_ */
