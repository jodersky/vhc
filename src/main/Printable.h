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

/** Classes abstraite heritee par tout objet imprimable. */
class Printable {

public:

	/** Retourne une representation en chaine de cet objet imprimable. */
	virtual std::string toString() const = 0;

};

/** Ajoute la representation en chaine de <code>p</code> a <code>output</code>. */
std::ostream& operator<< (std::ostream& output, const Printable& p);

}

#endif /* PRINTABLE_H_ */
