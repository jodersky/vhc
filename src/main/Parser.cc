/*
 * Parser.cc
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */

#include "Parser.h"

balise Parser::system = "<System>";
balise Parser::accelerator ="<Accelerator>";
balise Parser::constants ="<constants>";
balise Parser::curvedElement ="<CurvedElement>";
balise Parser::dipole ="<Dipole>";
balise Parser::fodo ="<FODO>";
balise Parser::particle ="<Particle>";
balise Parser::quadrupole ="<Quadrupole>";
balise Parser::straightElement ="<StraightElement>";
balise Parser::systemCl = "<\System>";
balise Parser::acceleratorCl ="<<Accelerator>";
balise Parser::constantsCl ="<\constants>";
balise Parser::curvedElementCl ="<\CurvedElement>";
balise Parser::dipoleCl ="<\Dipole>";
balise Parser::fodoCl ="<\FODO>";
balise Parser::particleCl ="<\Particle>";
balise Parser::quadrupoleCl ="<\Quadrupole>";
balise Parser::straightElementCl ="<\StraightElement>";

Parser::Parser(string file) {
	// TODO Auto-generated constructor stub

}

Parser::extract(string file) {

	//met le nom qu'on rajoute après le programme du fichier dans une string
	string nameOfFile;
	getline(cin, nameOfFile);

	//on déclare une flot d'entrée, ainsi qu'une sortie
	ifstream entry;
	//TODO
	ofstream exit;

	//TODO est-ce qu'un xml est un binaire? auquel cas rajouter l'argument ios::in|ios::binary
	//associe le flot d'entrée au fichier donné par l'utilisateur
	entry.open(nameOfFile.c_str());

	//test si l'association a bien pu se faire
	if(not entry.fail()){
		//met le premier mot du fichier dans une string temporaire
		string tmp = readOneWord(entry);
		//TODO encore plein de choses à faire
	}else{
		//si l'association du flot d'entrée avec le fichier n'a pas pu se faire, on lance une exception
		throw; //TODO une erreur
	}
}

//TODO use exceptions!

Parser::readOneChar(ifstream& file){};
Parser::readOneInt(ifstream& file){};
Parser::readOneDouble(ifstream& file){};
Parser::readOnePosition(ifstream& file){};
Parser::readOneBalise(ifstream& file){};
Parser::findNextBalise(ifstream& file){};
Parser::jumpComment(ifstream& file){};
Parser::readFile(ifstream& file){};

Parser::readOneWord(ifstream& file) {
	string tmp;
	file>>tmp;
	return tmp;
}

Parser::readOneLine(ifstream& file){
	string tmp;
	getline(file, tmp);
	return tmp;
}
