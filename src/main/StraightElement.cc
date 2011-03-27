/*
 * StraightElement.cc
 *
 *  Created on: Mar 22, 2011
 *      Author: jakob
 */

#include "StraightElement.h"

namespace vhc {

	// TODO finish implementing abstract methods of Element (toString)
	// Print also magnetic field
	// Same question as in CurvedElement.cc

	/** Cf. StraightElement.h */
	std::string StraightElement::toString() const {

		std::stringstream s;
		s << "StraightElement:"	<< "\n";
		s << "\tPosition of entry: 	 	 "	<< entryPosition << "\n";
		s << "\tPosition of exit: 	 	 "	<< exitPosition	 << "\n";
		s << "\tRadius of section: 	 	 "	<< sectionRadius << "\n";
		s << "\t";
		return s.str();
	}


}
