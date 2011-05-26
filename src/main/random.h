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

/** Contient des methodes pour la generation de nombres aleatoires. */
namespace random {

/** Affecte la "graine" des nombres aleatoires generees par la suite.
 *  @param s graine (si zero, le temps actuel du systeme est utilise) */
void seed(unsigned int s);

/** Genere un nombre aleatoire de probabilite equivalente sur l'interval [a, b]. */
double uniform(double a, double b);

/** Genere un nombre aleatoire reparti de facon gausienne.
 *  @param average moyenne
 *  @param standardDeviation ecart-type */
double gaussian(double average, double standardDeviation);

} //random

} //vhc
#endif /* RANDOM_H_ */
