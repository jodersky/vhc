/*
 * exceptions.cc
 *
 *  Created on: Apr 17, 2011
 *      Author: jakob
 */

#include <sstream>
#include "exceptions.h"

namespace vhc {

Exception::Exception(): message("") {};

Exception::Exception(std::string message): message(message) {};

Exception::~Exception() {};

std::string Exception::getExceptionType() const {return "Exception";}

std::string Exception::getMessage() const {return message;}

std::string Exception::toString() const {
	std::stringstream s;
	s << getExceptionType() << ": " << getMessage();
	return s.str();
}


IllegalArgumentException::IllegalArgumentException(): Exception() {};
IllegalArgumentException::IllegalArgumentException(std::string message): Exception(message) {};

std::string IllegalArgumentException::getExceptionType() const {return "IllegalArgumentException";}



UnsupportedOperationException::UnsupportedOperationException(): Exception() {};
UnsupportedOperationException::UnsupportedOperationException(std::string message): Exception(message) {};

std::string UnsupportedOperationException::getExceptionType() const {return "UnsupportedOperationException";}

}

