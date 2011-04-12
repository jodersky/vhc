/*
 * Accelerator.cc
 *
 *  Created on: 22 mars 2011
 *      Author: christian
 */

#include "Accelerator.h"

namespace vhc {

/** Cf. Accelerator.h */
std::string Accelerator::toString() const {

	std::stringstream s;
	if (elementCollec.size() == 0) {
		s << "This accelerator doesn't contain anything."<<"\n";
	} else if (elementCollec.size()==1) {
		s << "This accelerator is made of the following element :" << "\n";
		s << elementCollec[0]->toString()<<"\n";
	} else {
		s << "This accelerator is made of the " << elementCollec.size() << " following elements :" << "\n";
		for (int i(0); i < elementCollec.size(); ++i){
			s << elementCollec[i]->toString() << "\n";
		}
	}


	if (particleCollec.size() == 0) {
		s << "This accelerator doesn't contain any particle." << "\n";
	} else if (particleCollec.size() == 1) {
		s << "This accelerator contains the following particle :" << "\n";
		s << particleCollec[0]->toString() << "\n";
	}else{
		s << "This accelerator contains the " << particleCollec.size() << " following particles :"<<"\n";
		for (int i(0); i < particleCollec.size(); ++i){
			s << particleCollec[i]->toString() << "\n";
		}
	}

	return s.str();
	};
}
