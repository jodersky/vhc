/*
 * Parser.cc
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */

#include "Parser.h"

namespace vhc {
/** Cf. header.**/
Parser::Parser(string file)
	:nameOfFile(file){}

//===========================================balises ouvrantes==========================================================================

//balises ouvrantes d'un système
tagStat Parser::system = "<System>";
tagStat Parser::accelerator ="<Accelerator>";
tagStat Parser::comment = "<--";

//balises ouvrantes d'une particule
tagStat Parser::particle ="<Particle>";
tagStat Parser::position = "<Position>";
tagStat Parser::mass = "<Mass>";
tagStat Parser::charge = "<Charge>";
tagStat Parser::energy = "<Energy>";
tagStat Parser::direction = "<Direction>";

//balises ouvrantes d'un Element
tagStat Parser::entryPos = "<EntryPosition>";
tagStat Parser::exitPos = "<ExitPosition>";
tagStat Parser::sectionRadius = "<SectionRadius>";

//balises ouvrantes d'un Dipole
tagStat Parser::dipole ="<Dipole>";
tagStat Parser::curvature = "<Curvature>";
tagStat Parser::magneticField = "<MagneticField>";

//balise ouvrante commune aux quadrupoles et aux fodo
tagStat Parser::focCoeff = "<FocalizingCoefficient>";

//balises ouvrantes d'une FODO
tagStat Parser::fodo ="<FODO>";
tagStat Parser::straightLength = "<StraightLenght>";

//balises ouvrantes d'un Quadrupole
tagStat Parser::quadrupole ="<Quadrupole>";

//balises ouvrantes d'un StraightElement
tagStat Parser::straightElement ="<StraightElement>";

//===================================================balises fermantes==================================================================

//balises fermantes d'un système
tagStat Parser::systemCl = "<\System>";
tagStat Parser::acceleratorCl ="<\Accelerator>";
tagStat Parser::commentCl = "-->";

//balises fermantes d'une particule
tagStat Parser::particleCl ="<\Particle>";
tagStat Parser::positionCl = "<\Position>";
tagStat Parser::massCl = "<\Mass>";
tagStat Parser::chargeCl = "<\Charge>";
tagStat Parser::energyCl = "<\Energy>";
tagStat Parser::directionCl = "<\Direction>";

//balises fermantes d'un Element
tagStat Parser::entryPosCl = "<\EntryPosition>";
tagStat Parser::exitPosCl = "<\ExitPosition>";
tagStat Parser::sectionRadiusCl = "<\SectionRadius>";

//balises fermantes d'un Dipole
tagStat Parser::dipoleCl ="<\Dipole>";
tagStat Parser::curvatureCl = "<\Curvature>";
tagStat Parser::magneticFieldCl = "<\MagneticField";

//balise fermantes commune aux quadrupoles et aux fodo
tagStat Parser::focCoeffCl = "<\FocalizingCoefficient>";

//balises fermantes d'une FODO
tagStat Parser::fodoCl ="<\FODO>";
tagStat Parser::straightLengthCl = "<\StraightLenght>";

//balises fermantes d'un Quadrupole
tagStat Parser::quadrupoleCl ="<\Quadrupole>";

//balises fermantes d'un StraightElement
tagStat Parser::straightElementCl ="<\StraightElement>";
//======================================================================================================================================
//======================================================================================================================================

//======================================================================================================================================
Parser::readOneChar(ifstream& file){
	char tmp;
	file>>tmp;
	return tmp;
}
Parser::readOneInt(ifstream& file){
	int tmp;
	file>>tmp;
	return tmp;
}
Parser::readOneDouble(ifstream& file){
	double tmp;
	file>>tmp;
	return tmp;
}
Parser::readVector3D(ifstream& file){

	double x = readOneDouble(file);
	readComma(file);
	double y = readOneDouble(file);
	readComma(file);
	double z = readOneDouble(file);

	return Vector3D(x,y,z);
}
Parser::readOneTag(ifstream& file){
	tag tmp;
	file>>tag;
	return tmp;
}
Parser::readComma(ifstream& file){
	char trash;
	file>>trash;
}
Parser::readClosingTag(ifstream& file){
	tag tmp;
	file>>tmp;
	if(tmp != *"Cl")
		throw ReadExceptionMessage("No closing tag found.");
}
Parser::findNextTag(ifstream& file){}
Parser::jumpComment(ifstream& file){}
//======================================================================================================================================
Parser::extract() {

	//on déclare une flot d'entrée, ainsi qu'une sortie
	ifstream entry;

	//associe le flot d'entrée au fichier donné par l'utilisateur
	entry.open(nameOfFile.c_str());

	//teste si l'association a bien pu se faire
	if(not entry.fail()){
		readFile(entry);
		//A la fin de la lecture, on ferme le flot
		entry.close();
	}else{
		//si l'association du flot d'entrée avec le fichier n'a pas pu se faire, on lance une exception
		throw IOException("Cannot open file. "+nameOfFile+" not found.");
	}
}


Parser::readTag(ifstream& file){
	try {

		tag tmp;

		//Tant qu'on n'est pas arrivé à la fin du fichier, on continue à le lire
		while(not file.eof()){

			tmp = readOneTag(file);

			//on teste si la ligne correspond à une des balises
			switch(tmp){

				case system :
					break;

				case accelerator :

					Accelerator* acc = new Accelerator;
					break;

				case dipole :

					try{
						tag tmp3;
						tmp=readOneTag(file);

						switch(tmp3){

						case entryPos :
							Vector3D diEntryPos = readVector3D(file);
						case exitPos :
							Vector3D diExitPos = dsfaga
						}


						Dipole* di = new Dipole(lkdsflksdanlkfdag);
					}
					catch(ReadException& ex){
						e.addReadExceptionMessage("Error building Dipole.");
						throw;
					}

				case fodo :

					try{
						FODO* fodo = new FODO(readsmth);
					}
					catch(ReadException& ex){
						e.addReadExceptionMessage("Error building FODO.");
						throw;
					}

				case particle :

					try{
						Particle* pa = new Particle(readsmth);
					}
					catch(ReadException& ex){
						e.addReadExceptionMessage("Error building Particle.");
						throw;
					}

				case quadrupole :

					try{
					Quadrupole* quad = new Quadrupole(readsmth);
					}
					catch(ReadException& ex){
						e.addReadExceptionMessage("Error building Quadrupole.");
						throw;
					}

				case straightElement :

					try{
						StraightElement* se = new StraightElement(readsmth);
					}
					catch(ReadException& ex){
						e.addReadExceptionMessage("Error building StraightElement.");
						throw;
					}

				// si la variable tmp est vide, on ne fait rien, si elle est non-vide mais ne contient pas de balise,
				// c'est qu'une valeur (celle contenue par la variable donc) n'a pas été récupérée comme il faut.
				default:
					//TODO si l'opérateur ne lit pas les blancs, sinon il fau mettre ça ailleurs
					readClosingTag(file);

					//TODO est-ce que l'opérateur >> lit les blancs?
					//if(tmp != " ") throw ReadException("Values found outside of tag");
					break;


			}
		}

	}
	catch(Exception const& ex){
		std::cout<<ex.getMessage()<<std::endl;
	}
}

}//namespace
