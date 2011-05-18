/*
 * Parser.h
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */
#include <iostream>
#include <string>
#include <vector>
#include <ifstream>
#include <ofstream>
#include "Vector3D.h"

#ifndef PARSER_H_
#define PARSER_H_

typedef balise string;
typedef balStat static balise;

class Parser {
public:
	Parser(string file);
	virtual ~Parser(){};
	void extract(string file);
private:
	balStat system;
	balStat accelerator;
	balStat constants;
	balStat curvedElement;
	balStat dipole;
	balStat fodo;
	balStat particle;
	balStat quadrupole;
	balStat straightElement;

	balStat systemCl;
	balStat acceleratorCl;
	balStat constantsCl;
	balStat curvedElementCl;
	balStat dipoleCl;
	balStat fodoCl;
	balStat particleCl;
	balStat quadrupoleCl;
	balStat straightElementCl;

	char readOneChar(ifstream& file);
	int readOneInt(ifstream& file);
	double readOneDouble(ifstream& file);
	Vector3D readOnePosition(ifstream& file);
	balise readOneBalise(ifstream& file);
	balise findNextBalise(ifstream& file);
	void jumpComment(ifstream& file);
	string readOneWord(ifstream& file);
	string readOneLine(ifstream& file);
	string readFile(ifstream& file);
};

#endif /* PARSER_H_ */
