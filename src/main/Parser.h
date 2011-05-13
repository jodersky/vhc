/*
 * Parser.h
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */

#include <string>

#ifndef PARSER_H_
#define PARSER_H_

class Parser {
public:
	Parser(string file);
	virtual ~Parser();
	void extract(string file);
};

#endif /* PARSER_H_ */
