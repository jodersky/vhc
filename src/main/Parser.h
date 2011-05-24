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
#include "Accelerator.h"
#include "Vector3D.h"
#include "exceptions.h"

#ifndef PARSER_H_
#define PARSER_H_

namespace vhc {


typedef tag string;
typedef tagStat static tag;

class Parser {
public:
	Parser(string);
	virtual ~Parser(){}
	Accelerator* extract(string);
private:
	string nameOfFile;
//===========================================balises ouvrantes==========================================================================

	//balises ouvrantes d'un système
	tagStat system;
	tagStat accelerator;
	tagStat comment;

	//balises ouvrantes d'une particule
	tagStat particle;
	tagStat position;
	tagStat mass;
	tagStat charge;
	tagStat energy;
	tagStat direction;

	//balises ouvrantes d'un Element
	tagStat entryPos;
	tagStat exitPos;
	tagStat sectionRadius;

	//balises ouvrantes d'un dipole
	tagStat dipole;
	tagStat curvature;
	tagStat magneticField;

	//balise ouvrantes commune aux quadrupoles et aux fodo
	tagStat focCoeff;

	//balises ouvrantes d'une FODO
	tagStat fodo;
	tagStat straightLength;

	//balises ouvrante d'un quadrupole
	tagStat quadrupole;

	//balises ouvrantes d'une straightElement
	tagStat straightElement;

//===================================================balises fermantes==================================================================

	//balises fermantes d'un système
	tagStat systemCl;
	tagStat acceleratorCl;
	tagStat commentCl;

	//balises fermantes d'une particule
	tagStat particleCl;
	tagStat positionCl;
	tagStat massCl;
	tagStat chargeCl;
	tagStat energyCl;
	tagStat directionCl;

	//balises fermantes d'un Element
	tagStat entryPosCl;
	tagStat exitPosCl;
	tagStat sectionRadiusCl;

	//balises fermantes d'un dipole
	tagStat dipoleCl;
	tagStat curvatureCl;
	tagStat magneticFieldCl;

	//balise fermantes commune aux quadrupoles et aux fodo
	tagStat focCoeffCl;

	//balises fermantes d'une FODO
	tagStat fodoCl;
	tagStat straightLengthCl;

	//balises fermantes d'un quadrupole
	tagStat quadrupoleCl;

	//balises fermantes d'une straightElement
	tagStat straightElementCl;

//======================================================autres méthodes=================================================================

	//méthodes de lectures génériques
	string readFile(ifstream& file);

	//méthodes gestion balises
	tag readOpeningBalise(ifstream& file);
	tag readClosingBalise(ifstream& file);
	tag findNextBalise(ifstream& file);

	//méthode pour commentaire
	void jumpComment(ifstream& file);

	//méthodes atomiques de lecture
	char readOneChar(ifstream& file);
	int readOneInt(ifstream& file);
	double readOneDouble(ifstream& file);
	Vector3D readOnePosition(ifstream& file);

};

}
#endif /* PARSER_H_ */
