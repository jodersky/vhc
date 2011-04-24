/*
 * Printable.h
 *
 *  Created on: Mar 16, 2011
 *      Author: jakob
 */

#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <string>

namespace vhc {

/** Classe abstraite héritée par tout objet imprimable. */
class Printable {

public:

	virtual ~Printable();

	/** Retourne une représentation en chaîne de caractères de cet objet imprimable. */
	virtual std::string toString() const = 0;

};

/** Ajoute la représentation en chaîne de <code>p</code> à <code>output</code>. */
std::ostream& operator<< (std::ostream& output, const Printable& p);

}

#endif /* PRINTABLE_H_ */
