/*
 * Parser.cc
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */
#include "Parser.h"

//TODO balises fermantes et header et constantes et commentaires????????

namespace vhc {

/** Cf. header.**/
Parser::Parser(): nameOfFile("") {};

Parser::Parser(std::string file): nameOfFile(file) {};

Parser::~Parser() {};

//===========================================balises ouvrantes==========================================================================

//balises ouvrantes d'un système
tagStat Parser::system = "<System>";
tagStat Parser::accelerator ="<Accelerator>";
tagStat Parser::comment = "<--";

//balises ouvrantes des constantes
tagStat Parser::constants = "<constants>";
tagStat Parser::dt = "<dt>";
tagStat Parser::C = "<C>";
tagStat Parser::E = "<E>";
tagStat Parser::PROTON_MASS = "<PROTON_MASS>";
tagStat Parser::ELECTRON_MASS = "<ELECTRON_MASS>";

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

//balises fermantes des constantes
tagStat Parser::constantsCl = "<\constants>";
tagStat Parser::dtCl = "<\dt>";
tagStat Parser::CCl = "<\C>";
tagStat Parser::ECl = "<\E>";
tagStat Parser::PROTON_MASSCl = "<\PROTON_MASS>";
tagStat Parser::ELECTRON_MASSCl = "<\ELECTRON_MASS>";

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

//===========================================================création et renvoi d'un accélérateur=======================================
Parser::extract() {

	Accelerator* acc;

	//on déclare une flot d'entrée
	ifstream entry;

	//associe le flot d'entrée au fichier donné par l'utilisateur
	entry.open(nameOfFile.c_str());

	//teste si l'association a bien pu se faire
	if(not entry.fail()){

		//Tant qu'on n'est pas arrivé à la fin du fichier, on continue à le lire
		while(not file.eof()){

			//tout se fait depuis ici
			readFile(entry, *acc);
		}

		//A la fin de la lecture, on ferme le flot
		entry.close();
	}else{
		//si l'association du flot d'entrée avec le fichier n'a pas pu se faire, on lance une exception
		throw IOException("Cannot open file. "+nameOfFile+" not found.");
	}

	return acc;
}

//===========================================================lecture du fichier .xml====================================================
Parser::readFile(ifstream& file, Accelerator& acc){
	try {

		// on lit la balise qu'on doit traiter
		tag tmp1 = readOneTag(file);

		/*on teste si tmp1 correspond à une des balises suivantes :
		 * 	- 	soit system
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp1){

			case system :

				readSystem(file, acc);
				break;

			case comment :

				jumpComment(file);
				break;

			/* si la variable tmp1 ne contient pas les balises voulues, c'est qu'une valeur
			 * (celle contenue par la variable tmp1 donc)
			 * n'a pas été récupérée comme il faut.
			*/
			default:

				throw ReadException("Values found outside of following tags : "+system+
									"\n Value is : "+tmp1);
				break;
		}
	}

	catch(Exception const& ex){
		std::cout<<ex.getMessage()<<std::endl;
	}
}

//==============================================================lecture de la balise system=============================================
Parser::readSystem(ifstream& file, Accelerator& acc){

	try {

		// on lit la balise qu'on doit traiter
		tag tmp2 = readOneTag(file);

		/*on teste si tmp2 correspond à une des balises suivantes :
		 * 	- 	soit constants
		 * 	-	soit accelerator
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp2){

			case constants :

				readConstants(file);
				break;

			case accelerator :

				buildAccelerator(file, acc);
				break;

			case comment :

				jumpComment(file);
				break;

			/* si la variable tmp2 ne contient pas les balises voulues, c'est qu'une valeur
			 * (celle contenue par la variable tmp2 donc)
			 * n'a pas été récupérée comme il faut.
			*/
			default:

				throw ReadException("Values found outside of following tags : "+constants+accelerator+
									"\n Value is : "+tmp2);
				break;
		}
	}

	catch(Exception const& ex){
		std::cout<<ex.getMessage()<<std::endl;
	}
}

//====================================================================lecture de constantes=============================================
Parser::readConstants(ifstream& file){
	try {

		// on lit la balise qu'on doit traiter
		tag tmp31 = readOneTag(file);

		/*on teste si tmp31 correspond à une des balises suivantes :
		 * 	- 	soit C
		 * 	- 	soit E
		 * 	-	soit PROTON_MASS
		 * 	-	soit ELECTRON_MASS
		 * 	-	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp31){

			case C :

				readC(file);
				break;

			case E :

				readE(file);
				break;

			case PROTON_MASS :

				readPROTON_MASS(file);
				break;

			case ELECTRON_MASS :

				readELECTRON_MASS(file);
				break;

			case comment :

				jumpComment(file);
				break;

			/* si la variable tmp31 ne contient pas les balises voulues, c'est qu'une valeur
			 * (celle contenue par la variable tmp31 donc)
			 * n'a pas été récupérée comme il faut.
			*/
			default:

				throw ReadException("Values found outside of following tags : "+dt+C+E+PROTON_MASS+ELECTRON_MASS+
									"\n Value is : "+tmp31);
				break;
		}
	}

	catch(Exception const& ex){
		std::cout<<ex.getMessage()<<std::endl;
	}
}

Parser::readC(ifstream& file){
	Parser::CP = readOneDouble(file);
	closingTag(file);
}

Parser::readE(ifstream& file){
	Parser::EP = readOneDouble(file);
	closingTag(file);
}

Parser::readPROTON_MASS(ifstream& file){
	Parser::PROTON_MASSP = readOneDouble(file);
	closingTag(file);
}

Parser::readELECTRON_MASS(ifstream& file){
	Parser::ELECTRON_MASSP = readOneDouble(file);
	closingTag(file);
}

//==========================================================fabrication de l'accélérateur===============================================
Parser::buildAccelerator(ifstream& file, Accelerator const& acc){

	try {

		// on lit la balise qu'on doit traiter
		tag tmp32 = readOneTag(file);

		/*on teste si tmp32 correspond à une des balises suivantes :
		 * 	- 	soit dipole
		 * 	-	soit fodo
		 * 	-	soit particle
		 * 	-	soit quadrupole
		 * 	-	soit straightElement
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp32){

				case dipole :

					acc.add(buildDipole(file));
					break;

				case fodo :

					acc.add(buildFODO(file));
					break;

				case particle :

					Particle* p = new Particle;
					acc.add(buildParticle(file,*pa));
					break;

				case quadrupole :

					acc.add(buildQuadrupole(file));
					break;

				case straightElement :

					acc.add(buildStraightElement(file));
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp32 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp32 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+dipole+fodo+particle+quadrupole+straightElement+
										"\n Value is : "+tmp32);
					break;
		}//switch
	}//try

	catch(Exception const& ex){
		std::cout<<ex.getMessage()<<std::endl;
	}
}

//===========================================================construction d'une nouvelle particule======================================
Parser::buildParticle(ifstream& file, Particle const& p){
	try {

		// on lit la balise qu'on doit traiter
		tag tmp41 = readOneTag(file);

		/*on teste si tmp41 correspond à une des balises suivantes :
		 * 	- 	soit position
		 * 	-	soit mass
		 * 	-	soit charge
		 * 	-	soit energy
		 * 	-	soit direction
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp41){

				case position :

					p.setPosition(readPosition(file));
					break;

				case mass :

					p.setMass(readMass(file));
					break;

				case charge :

					p.setCharge(readCharge(file));
					break;

				case energy :

					p.setEnergy(readEnergy(file));//TODO faire un set Energy!!!!!
					break;

				case direction :

					acc.add(buildStraightElement(file));
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp41 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp41 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+dipole+fodo+particle+quadrupole+straightElement+
										"\n Value is : "+tmp41);
					break;
		}//switch
	}//try

	catch(Exception const& ex){
		std::cout<<ex.getMessage()<<std::endl;
	}
}

Parser::readPosition(ifstream& file){

}

Parser::readMass(ifstream& file){

}

Parser::readCharge(ifstream& file){

}

Parser::readEnergy(ifstream& file){

}

Parser::readDirection(ifstream& file){

}

//===========================================================construction d'une nouvelle FODO===========================================
Parser::buildFODO(ifstream& file){

}

//===========================================================construction d'un nouveau Dipole===========================================
Parser::buildDipole(ifstream& file){

}

//============================================================construction d'un nouveau quadrupole======================================
Parser::buildQuadrupole(ifstream& file){

}

//============================================================construction d'un nouveau straight Element================================
Parser::buildStraightElement(ifstream& file){

}

//=======================================================lecture atomique===============================================================
Parser::readOneChar(ifstream& file){
	file>>ws;
	char tmp;
	file>>tmp;
	return tmp;
}
Parser::readOneInt(ifstream& file){
	file>>ws;
	int tmp;
	file>>tmp;
	return tmp;
}
Parser::readOneDouble(ifstream& file){
	file>>ws;
	double tmp;
	file>>tmp;
	return tmp;
}
Parser::readComma(ifstream& file){
	char trash;
	file>>ws;
	file>>trash;
}
//===========================================================lecture moléculaire========================================================
Parser::readVector3D(ifstream& file){

	double x = readOneDouble(file);
	readComma(file);
	double y = readOneDouble(file);
	readComma(file);
	double z = readOneDouble(file);
	file>>ws;

	return Vector3D(x,y,z);
}
Parser::readOneTag(ifstream& file){
	tag tmp;
	file>>tag;
	return tmp;
}
Parser::closingTag(ifstream& file){
	tag tmp;
	file>>ws;
	file>>tmp;
	//si on a pas de balise fermante (ici il devrait il y en avoir normalement une) alors on lance une exception
	found=tmp.find("<");
	if(found() == string::npos)
		throw ReadExceptionMessage("No closing tag found.");
}
//===========================================================lecture commentaire========================================================
Parser::jumpComment(ifstream& file){
	tag tmp;
	file>>ws;
	//TODO getLine(file,tmp);
	//si on a pas de balise fermante (ici il devrait il y en avoir normalement une) alors on lance une exception
	found=tmp.find("-->");
	if(found() == string::npos)
		throw ReadExceptionMessage("No closing tag for comment found.");

}

}//namespace
