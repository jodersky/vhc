/*
 * constants.h
 *
 *  Created on: Mar 17, 2011
 *      Author: jakob
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace vhc {

/** Contient des constantes physiques. */
namespace constants {

/** Vitesse de la lumière dans le vide [m/s]. */
const double C = 299792458;

/** Vitesse de la lumière dans le vide au carré [m/s]. */
const double C2 = C * C;

/** Charge élémentaire [C]. */
const double E = 1.60217653E-19;

/** Masse d'un proton [kg]. */
const double PROTON_MASS = 1.672623E-27;

/** Masse d'un électron [kg]. */
const double ELECTRON_MASS = 9.109383E-31;

}

}

#endif /* CONSTANTS_H_ */
