/*
 * random.cc
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */
#include <math.h>
#include "random.h"

namespace vhc {

namespace random {

void seed(unsigned int s) {
    if (s == 0) {
    	srand(time(0));
    } else {
    	srand(s);
    }
}

double uniform(double a, double b) {
    return a + (rand() / double(RAND_MAX)) * (b - a);
}

double gaussian(double average, double standardDeviation) {
  double v1;
  double v2;
  double s ;

  do {
    v1 = uniform(-1.0, 1.0);
    v2 = uniform(-1.0, 1.0);
    s = v1*v1 + v2*v2;
  } while ((s >= 1.0) or (s == 0.0));

  double x(sqrt(-2.0 * log(s) / s));
  if (uniform(0.0, 1.0) > 0.5)
    x *= v1;
  else
    x *= v2;

  return average + standardDeviation * x;
}

} //random

} //vhc

