/*
 * Parser.cc
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */
#include <isotream>
#include <string>
#include "Parser.h"

using namespace std;

namespace vhc {

//===========================================balises ouvrantes==========================================================================

//balises ouvrantes d'un système
static tag Parser::system = "<System>";
static tag Parser::accelerator ="<Accelerator>";
static tag Parser::comment = "<!--";

//balises ouvrantes d'une particule
static tag Parser::particle ="<Particle>";
static tag Parser::position = "<Position>";
static tag Parser::mass = "<Mass>";
static tag Parser::charge = "<Charge>";
static tag Parser::energy = "<Energy>";
static tag Parser::direction = "<Direction>";

//balises ouvrantes d'un Element
static tag Parser::entryPos = "<EntryPosition>";
static tag Parser::exitPos = "<ExitPosition>";
static tag Parser::sectionRadius = "<SectionRadius>";

//balises ouvrantes d'un Dipole
static tag Parser::dipole ="<Dipole>";
static tag Parser::curvature = "<Curvature>";
static tag Parser::magneticField = "<MagneticField>";

//balise ouvrante commune aux quadrupoles et aux fodo
static tag Parser::focCoeff = "<FocalizingCoefficient>";

//balises ouvrantes d'une FODO
static tag Parser::fodo ="<FODO>";
static tag Parser::straightLength = "<StraightLenght>";

//balises ouvrantes d'un Quadrupole
static tag Parser::quadrupole ="<Quadrupole>";

//balises ouvrantes d'un StraightElement
static tag Parser::straightElement ="<StraightElement>";

//===================================================balises fermantes==================================================================

//balises fermantes d'un système
static tag Parser::systemCl = "<\System>";
static tag Parser::acceleratorCl ="<\Accelerator>";
static tag Parser::commentCl = "-->";

//balises fermantes d'une particule
static tag Parser::particleCl ="<\Particle>";
static tag Parser::positionCl = "<\Position>";
static tag Parser::massCl = "<\Mass>";
static tag Parser::chargeCl = "<\Charge>";
static tag Parser::energyCl = "<\Energy>";
static tag Parser::directionCl = "<\Direction>";

//balises fermantes d'un Element
static tag Parser::entryPosCl = "<\EntryPosition>";
static tag Parser::exitPosCl = "<\ExitPosition>";
static tag Parser::sectionRadiusCl = "<\SectionRadius>";

//balises fermantes d'un Dipole
static tag Parser::dipoleCl ="<\Dipole>";
static tag Parser::curvatureCl = "<\Curvature>";
static tag Parser::magneticFieldCl = "<\MagneticField";

//balise fermantes commune aux quadrupoles et aux fodo
static tag Parser::focCoeffCl = "<\FocalizingCoefficient>";

//balises fermantes d'une FODO
static tag Parser::fodoCl ="<\FODO>";
static tag Parser::straightLengthCl = "<\StraightLenght>";

//balises fermantes d'un Quadrupole
static tag Parser::quadrupoleCl ="<\Quadrupole>";

//balises fermantes d'un StraightElement
static tag Parser::straightElementCl ="<\StraightElement>";

//===========================================================création et renvoi d'un accélérateur=======================================
Parser::extract() {

	Accelerator* acc = new Accelerator;

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

	acc->close();
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
				closingTag(file, systemCl);
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
		cout<<ex.getMessage()<<endl;
	}
}

//==============================================================lecture de la balise system=============================================
Parser::readSystem(ifstream& file, Accelerator& acc){

	try {

		// on lit la balise qu'on doit traiter
		tag tmp2 = readOneTag(file);

		/*on teste si tmp2 correspond à une des balises suivantes :
		 * 	-	soit accelerator
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp2){

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

				throw ReadException("Values found outside of following tags : "+accelerator+
									"\n Value is : "+tmp2);
				break;
		}
	}

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//==========================================================fabrication de l'accélérateur===============================================
Parser::buildAccelerator(ifstream& file, Accelerator& acc){

	try {

		// on lit la balise qu'on doit traiter
		tag tmp3 = readOneTag(file);

		/*on teste si tmp3 correspond à une des balises suivantes :
		 * 	- 	soit dipole
		 * 	-	soit fodo
		 * 	-	soit particle
		 * 	-	soit quadrupole
		 * 	-	soit straightElement
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp3){

				case dipole :

					acc.add(*buildDipole(file));
					readClosingTag(file, dipoleCl);
					tmp3 = readOneTag(file);
					if(tmp3 == acceleratorCl)
						break;
					else
						continue;

				case fodo :

					acc.add(*buildFODO(file));
					readClosingTag(file, fodoCl);
					tmp3 = readOneTag(file);
					if(tmp3 == acceleratorCl)
						break;
					else
						continue;

				case particle :

					acc.add(*buildParticle(file));
					readClosingTag(file, particleCl);
					tmp3 = readOneTag(file);
					if(tmp3 == acceleratorCl)
						break;
					else
						continue;;

				case quadrupole :

					acc.add(*buildQuadrupole(file));
					readClosingTag(file, quadrupoleCl);
					tmp3 = readOneTag(file);
					if(tmp3 == acceleratorCl)
						break;
					else
						continue;

				case straightElement :

					acc.add(*buildStraightElement(file));
					readClosingTag(file, straightElementCl);
					tmp3 = readOneTag(file);
					if(tmp3 == acceleratorCl)
						break;
					else
						continue;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp3 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp3 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+dipole+fodo+particle+quadrupole+straightElement+
										"\n Value is : "+tmp3);
					break;
		}//switch
	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//===========================================================création d'une particule===================================================
Particle* Parser::buildParticle(ifstream& file){
	try {

		//Initialisation des variables nécessaires à la construction d'une particule.
		Vector3D po(0,0,0); double ma(0); double ch(0); double en(0); Vector3D dir(0,0,0);

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

					po = readVector3D(file);
					closingTag(file, positionCl);
					break;

				case mass :

					ma = readOneDouble(file);
					closingTag(file, massCl);
					break;

				case charge :

					ch = readOneDouble(file);
					closingTag(file, chargeCl);
					break;

				case energy :

					en = readOneDouble(file);
					closingTag(file, energyCl);
					break;

				case direction :

					dir = readVector3D(file);
					closingTag(file, directionCl);
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp41 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp41 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+position+mass+charge+energy+direction+
										"\n Value is : "+tmp41);
					break;
		}//switch

		//Construction d'une particule avec les varables récoltées.
		Particle* p = new Particle(po,
								   ma * constants::PROTON_MASS,
								   ch * constants::E,
								   en * constants::GeV,
								   dir);

		return p;

	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//===========================================================création d'un Dipole=======================================================
/** Cf. header. */
Diple* Parser::buildDipole(ifstream& file){
	try {

		//Initialsation des variables nécessaires à la construction d'un Dipole.
		Vector3D enp(0,0,0); Vector3D exp(0,0,0); double sr(0); double cu(0); Vector3D mf(0,0,0);

		// on lit la balise qu'on doit traiter
		tag tmp42 = readOneTag(file);

		/*on teste si tmp42 correspond à une des balises suivantes :
		 * 	- 	soit entryPos
		 * 	-	soit exitPos
		 * 	-	soit sectionRadius
		 * 	-	soit curvature
		 * 	-	soit magneticField
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp42){

				case entryPos :

					enp = readVector3D(file);
					closingTag(file, entryPosCl);
					break;

				case exitPos :

					exp = readVector3D(file);
					closingTag(file, exitPosCl);
					break;

				case sectionRadius :

					sr = readOneDouble(file);
					closingTag(file, sectionRadiusCl);
					break;

				case curvature :

					cu = readOneDouble(file);
					closingTag(file, curvatureCl);
					break;

				case magneticField :

					mf = readVector3D(file);
					closingTag(file, magneticFieldCl);
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp42 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp42 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+curvature+magneticField+
										"\n Value is : "+tmp42);
					break;
		}//switch

		//Construction d'un dipole avec les variables récoltées.
		Dipole* di = new Dipole(enp, exp, sr, cu, mf);

		return di;

	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//===========================================================modification d'une FODO====================================================
/** Cf. header. */
FODO* Parser::buildFODO(ifstream& file){
	try {

		//Initialsation des variables nécessaires à la construction d'une FODO.
		Vector3D enp(0,0,0); Vector3D exp(0,0,0); double sr(0); double sl(0); double fc(0);

		// on lit la balise qu'on doit traiter
		tag tmp43 = readOneTag(file);

		/*on teste si tmp43 correspond à une des balises suivantes :
		 * 	- 	soit entryPos
		 * 	-	soit exitPos
		 * 	-	soit sectionRadius
		 * 	-	soit straightLength
		 * 	-	soit focCoeff
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp43){

				case entryPos :

					enp = readVector3D(file);
					closingTag(file, entryPosCl);
					break;

				case exitPos :

					exp = readVector3D(file);
					closingTag(file, exitPosCl);
					break;

				case sectionRadius :

					sr = readOneDouble(file);
					closingTag(file, sectionRadiusCl);
					break;

				case straightLength :

					sl = readOneDouble(file);
					closingTag(file, straightLengthCl);
					break;

				case focCoeff :

					fc = readOneDouble(file);
					closingTag(file, focCoeffCl);
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp43 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp43 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+straightLength+focCoeff+
										"\n Value is : "+tmp43);
					break;
		}//switch

		//Construction d'une FODO avec les variables récoltées.
		FODO* fo = new FODO(enp, exp, sr, sl, fc);

		return fo;

	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}


//============================================================création d'un quadrupole==================================================
/** Cf. header. */
Quadrupole* Parser::buildQuadrupole(ifstream& file){
	try {

		//Initialsation des variables nécessaires à la construction d'un Quadrupole.
		Vector3D enp(0,0,0); Vector3D exp(0,0,0); double sr(0); double fc(0);

		// on lit la balise qu'on doit traiter
		tag tmp44 = readOneTag(file);

		/*on teste si tmp44 correspond à une des balises suivantes :
		 * 	- 	soit entryPos
		 * 	-	soit exitPos
		 * 	-	soit sectionRadius
		 * 	-	soit focCoeff
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp44){

				case entryPos :

					enp = readVector3D(file);
					closingTag(file, entryPosCl);
					break;

				case exitPos :

					exp = readVector3D(file);
					closingTag(file, exitPosCl);
					break;

				case sectionRadius :

					sr = readOneDouble(file);
					closingTag(file, sectionRadiusCl);
					break;

				case focCoeff :

					fc = readOneDouble(file);
					closingTag(file, focCoeffCl);
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp44 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp44 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+focCoeff+
										"\n Value is : "+tmp44);
					break;
		}//switch

		//Construction d'un Quadrupole avec les variables récoltées.
		Quadrupole* qu = new Quadrupole(enp, exp, sr, fc);

		return qu;

	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//============================================================création d'un StraightElement=============================================
/** Cf. header. */
StraightElement* Parser::buildStraightElement(ifstream& file){
	try {

		//Initialsation des variables nécessaires à la construction d'un StraightElement.
		Vector3D enp(0,0,0); Vector3D exp(0,0,0); double sr(0);

		// on lit la balise qu'on doit traiter
		tag tmp45 = readOneTag(file);

		/*on teste si tmp45 correspond à une des balises suivantes :
		 * 	- 	soit entryPos
		 * 	-	soit exitPos
		 * 	-	soit sectionRadius
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		switch(tmp45){

				case entryPos :

					enp = readVector3D(file);
					closingTag(file, entryPosCl);
					break;

				case exitPos :

					exp = readVector3D(file);
					closingTag(file, exitPosCl);
					break;

				case sectionRadius :

					sr = readOneDouble(file);
					closingTag(file, sectionRadiusCl);
					break;

				case comment :

					jumpComment(file);
					break;

				/* si la variable tmp45 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp45 donc)
				 * n'a pas été récupérée comme il faut.
				*/
				default:

					throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+
										"\n Value is : "+tmp45);
					break;
		}//switch

		//Construction d'un StraightElement avec les variables récoltées.
		StraightElement* se = new StraightElement(enp, exp, sr);

		return se;

	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}

//=======================================================lecture atomique===============================================================

/** Cf. header. */
double Parser::readOneDouble(ifstream& file){
	file>>ws;
	double tmp;
	file>>tmp;
	return tmp;
}

/** Cf. header. */
void Parser::readComma(ifstream& file){
	char trash;
	file>>ws;
	file>>trash;
}

//===========================================================lecture moléculaire========================================================
/** Cf. header. */
Vector3D Parser::readVector3D(ifstream& file){

	double x = readOneDouble(file);
	readComma(file);
	double y = readOneDouble(file);
	readComma(file);
	double z = readOneDouble(file);
	file>>ws;

	return Vector3D(x,y,z);
}

/** Cf. header. */
tag Parser::readOneTag(ifstream& file){
	tag tmp;
	file>>ws;
	file>>tag;
	return tmp;
}

/** Cf. header. */
void Parser::closingTag(ifstream& file, std::string ta){
	tag tmp;
	file>>ws;
	file>>tmp;
	//si on a pas de balise fermante (ici il devrait il y en avoir normalement une) alors on lance une exception
	found=tmp.find(ta);
	if(found() == string::npos)
		throw ReadExceptionMessage("No closing tag "+ta+" found.");
}
//===========================================================lecture commentaire========================================================
/**Cf. header. */
void Parser::jumpComment(ifstream& file){
	tag tmp;

	do{
		file>>ws;
		file>>tmp;
		found=tmp.find("-->");
	}
	while(found() == string::npos);

	if(file.eof())
		throw ReadExceptionMessage("No closing tag for comment found.");

}

}//namespace
