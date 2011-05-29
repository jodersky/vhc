/*
 * Parser.cc
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
#include "exceptions.h"

using namespace std;

namespace vhc {

//===========================================balises ouvrantes==========================================================================

//balises ouvrantes d'un système
tag Parser::system = "<System>";
tag Parser::accelerator ="<Accelerator>";
tag Parser::comment = "<!--";

//balises ouvrantes d'une particule
tag Parser::particle ="<Particle>";
tag Parser::position = "<Position>";
tag Parser::mass = "<Mass>";
tag Parser::charge = "<Charge>";
tag Parser::energy = "<Energy>";
tag Parser::direction = "<Direction>";

//balises ouvrantes d'un Element
tag Parser::entryPos = "<EntryPosition>";
tag Parser::exitPos = "<ExitPosition>";
tag Parser::sectionRadius = "<SectionRadius>";

//balises ouvrantes d'un Dipole
tag Parser::dipole ="<Dipole>";
tag Parser::curvature = "<Curvature>";
tag Parser::magneticField = "<MagneticField>";

//balise ouvrante commune aux quadrupoles et aux fodo
tag Parser::focCoeff = "<FocalizingCoefficient>";

//balises ouvrantes d'une FODO
tag Parser::fodo ="<FODO>";
tag Parser::straightLength = "<StraightLenght>";

//balises ouvrantes d'un Quadrupole
tag Parser::quadrupole ="<Quadrupole>";

//balises ouvrantes d'un StraightElement
tag Parser::straightElement ="<StraightElement>";

//===================================================balises fermantes==================================================================

//balises fermantes d'un système
tag Parser::systemCl = "<\System>";
tag Parser::acceleratorCl ="<\Accelerator>";
tag Parser::commentCl = "-->";

//balises fermantes d'une particule
tag Parser::particleCl ="<\Particle>";
tag Parser::positionCl = "<\Position>";
tag Parser::massCl = "<\Mass>";
tag Parser::chargeCl = "<\Charge>";
tag Parser::energyCl = "<\Energy>";
tag Parser::directionCl = "<\Direction>";

//balises fermantes d'un Element
tag Parser::entryPosCl = "<\EntryPosition>";
tag Parser::exitPosCl = "<\ExitPosition>";
tag Parser::sectionRadiusCl = "<\SectionRadius>";

//balises fermantes d'un Dipole
tag Parser::dipoleCl ="<\Dipole>";
tag Parser::curvatureCl = "<\Curvature>";
tag Parser::magneticFieldCl = "<\MagneticField";

//balise fermantes commune aux quadrupoles et aux fodo
tag Parser::focCoeffCl = "<\FocalizingCoefficient>";

//balises fermantes d'une FODO
tag Parser::fodoCl ="<\FODO>";
tag Parser::straightLengthCl = "<\StraightLenght>";

//balises fermantes d'un Quadrupole
tag Parser::quadrupoleCl ="<\Quadrupole>";

//balises fermantes d'un StraightElement
tag Parser::straightElementCl ="<\StraightElement>";

//===========================================================création et renvoi d'un accélérateur=======================================
Accelerator* Parser::extract() {

	Accelerator* acc = new Accelerator;

	//on déclare une flot d'entrée
	ifstream entry;

	//associe le flot d'entrée au fichier donné par l'utilisateur
	entry.open(nameOfFile.c_str());

	//teste si l'association a bien pu se faire
	if(! entry.fail()){

		//Tant qu'on n'est pas arrivé à la fin du fichier, on continue à le lire
		while(! entry.eof()){

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
void Parser::readFile(ifstream& file, Accelerator& acc){
	try {
		tag tmp1;
		// on lit la balise qu'on doit traiter
		tmp1=readOneTag(file);

		/*on teste si tmp1 correspond à une des balises suivantes :
		 * 	- 	soit system
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		if(tmp1 == system){

				readSystem(file, acc);
				closingTag(file, systemCl);

		}else if(tmp1 == comment){

				jumpComment(file);
		}
			/* si la variable tmp1 ne contient pas les balises voulues, c'est qu'une valeur
			 * (celle contenue par la variable tmp1 donc)
			 * n'a pas été récupérée comme il faut.
			*/
		else{
				throw ReadException("Values found outside of following tags : "+system+
									"\n Value is : "+tmp1);
		}
	}

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//==============================================================lecture de la balise system=============================================
void Parser::readSystem(ifstream& file, Accelerator& acc){

	try {

		// on lit la balise qu'on doit traiter
		tag tmp2 = readOneTag(file);

		/*on teste si tmp2 correspond à une des balises suivantes :
		 * 	-	soit accelerator
		 * 	- 	soit un commentaire
		 * 	-	sinon il y a un problème car on ne s'attend pas à autre chose à ce niveau-là
		 */
		if(tmp2==accelerator){

				buildAccelerator(file, acc);

		}else if(tmp2==comment){

				jumpComment(file);
		}
			/* si la variable tmp2 ne contient pas les balises voulues, c'est qu'une valeur
			 * (celle contenue par la variable tmp2 donc)
			 * n'a pas été récupérée comme il faut.
			*/
		else{
				throw ReadException("Values found outside of following tags : "+accelerator+
									"\n Value is : "+tmp2);
		}
	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//==========================================================fabrication de l'accélérateur===============================================
void Parser::buildAccelerator(ifstream& file, Accelerator& acc){

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
		if(tmp3==dipole){

					acc.add(*buildDipole(file));
					closingTag(file, dipoleCl);
					tmp3 = readOneTag(file);
					//if(tmp3 == acceleratorCl){}

		}else if(tmp3==fodo){

					acc.add(*buildFODO(file));
					closingTag(file, fodoCl);
					tmp3 = readOneTag(file);
					//if(tmp3 == acceleratorCl)

		}else if(tmp3==particle){

					acc.add(*buildParticle(file));
					closingTag(file, particleCl);
					tmp3 = readOneTag(file);
					//if(tmp3 == acceleratorCl)

		}else if(tmp3==quadrupole){

					acc.add(*buildQuadrupole(file));
					closingTag(file, quadrupoleCl);
					tmp3 = readOneTag(file);
					//if(tmp3 == acceleratorCl)

		}else if(tmp3==straightElement){

					acc.add(*buildStraightElement(file));
					closingTag(file, straightElementCl);
					tmp3 = readOneTag(file);
					//if(tmp3 == acceleratorCl)

		}else if(tmp3==comment){

					jumpComment(file);
		}
				/* si la variable tmp3 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp3 donc)
				 * n'a pas été récupérée comme il faut.
				*/
		else{

					throw ReadException("Values found outside of following tags : "+dipole+fodo+particle+quadrupole+straightElement+
										"\n Value is : "+tmp3);
		}
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
		if(tmp41==position){

					po = readVector3D(file);
					closingTag(file, positionCl);

		}else if(tmp41==mass){

					ma = readOneDouble(file);
					closingTag(file, massCl);

		}else if(tmp41==charge){

					ch = readOneDouble(file);
					closingTag(file, chargeCl);

		}else if(tmp41==energy){

					en = readOneDouble(file);
					closingTag(file, energyCl);

		}else if(tmp41==direction){

					dir = readVector3D(file);
					closingTag(file, directionCl);

		}else if(tmp41==comment){

					jumpComment(file);
		}
				/* si la variable tmp41 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp41 donc)
				 * n'a pas été récupérée comme il faut.
				*/
		else{
					throw ReadException("Values found outside of following tags : "+position+mass+charge+energy+direction+
										"\n Value is : "+tmp41);
		}

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
Dipole* Parser::buildDipole(ifstream& file){
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
		if(tmp42==entryPos){

					enp = readVector3D(file);
					closingTag(file, entryPosCl);

		}else if(tmp42==exitPos){

					exp = readVector3D(file);
					closingTag(file, exitPosCl);

		}else if(tmp42==sectionRadius){

					sr = readOneDouble(file);
					closingTag(file, sectionRadiusCl);

		}else if(tmp42==curvature){

					cu = readOneDouble(file);
					closingTag(file, curvatureCl);

		}else if(tmp42==magneticField){

					mf = readVector3D(file);
					closingTag(file, magneticFieldCl);

		}else if(tmp42==comment){

					jumpComment(file);
		}
				/* si la variable tmp42 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp42 donc)
				 * n'a pas été récupérée comme il faut.
				*/
		else{

					throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+curvature+magneticField+
										"\n Value is : "+tmp42);
		}

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
		if(tmp43==entryPos){

				enp = readVector3D(file);
				closingTag(file, entryPosCl);

		}else if(tmp43==exitPos){

				exp = readVector3D(file);
				closingTag(file, exitPosCl);

		}else if(tmp43==sectionRadius){

				sr = readOneDouble(file);
				closingTag(file, sectionRadiusCl);

		}else if(tmp43==straightLength){

				sl = readOneDouble(file);
				closingTag(file, straightLengthCl);

		}else if(tmp43==focCoeff){

				fc = readOneDouble(file);
				closingTag(file, focCoeffCl);

		}else if(tmp43==comment){

				jumpComment(file);
		}
				/* si la variable tmp43 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp43 donc)
				 * n'a pas été récupérée comme il faut.
				*/
		else{

				throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+straightLength+focCoeff+
									"\n Value is : "+tmp43);
		}

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
		if(tmp44==entryPos){

				enp = readVector3D(file);
				closingTag(file, entryPosCl);

		}else if(tmp44==exitPos){

				exp = readVector3D(file);
				closingTag(file, exitPosCl);

		}else if(tmp44==sectionRadius){

				sr = readOneDouble(file);
				closingTag(file, sectionRadiusCl);

		}else if(tmp44==focCoeff){

				fc = readOneDouble(file);
				closingTag(file, focCoeffCl);

		}else if(tmp44==comment){

				jumpComment(file);
		}
				/* si la variable tmp44 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp44 donc)
				 * n'a pas été récupérée comme il faut.
				*/
		else{

				throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+focCoeff+
									"\n Value is : "+tmp44);
		}

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
		if(tmp45==entryPos){

				enp = readVector3D(file);
				closingTag(file, entryPosCl);

		}else if(tmp45==exitPos){

				exp = readVector3D(file);
				closingTag(file, exitPosCl);

		}else if(tmp45==sectionRadius){

				sr = readOneDouble(file);
				closingTag(file, sectionRadiusCl);

		}else if(tmp45==comment){

				jumpComment(file);
		}				/* si la variable tmp45 ne contient pas les balises voulues, c'est qu'une valeur
				 * (celle contenue par la variable tmp45 donc)
				 * n'a pas été récupérée comme il faut.
				*/
		else{

					throw ReadException("Values found outside of following tags : "+entryPos+exitPos+sectionRadius+
										"\n Value is : "+tmp45);
		}
		//Construction d'un StraightElement avec les variables récoltées.
		StraightElement* se = new StraightElement(enp, exp, sr);

		return se;

	}//try

	catch(Exception const& ex){
		cout<<ex.getMessage()<<endl;
	}
}

//=======================================================lecture atomique===============================================================

/** Cf. header. */
double Parser::readOneDouble(ifstream& file){

	double tmp;
	char ex('x');
	string str;
	file>>ws;

	do{
		file.get(ex);
		str=str+ex;

	}while(ex != '<' && ',');

	istringstream is(str);
	is>>tmp;
	return tmp;
}

//===========================================================lecture moléculaire========================================================
/** Cf. header. */
Vector3D Parser::readVector3D(ifstream& file){

	double x = readOneDouble(file);
	double y = readOneDouble(file);
	double z = readOneDouble(file);

	return Vector3D(x,y,z);
}

/** Cf. header. */
tag Parser::readOneTag(ifstream& file){

	tag tmp("<");
	char ex('x');

	/* Lecture caractère par caractère du flot, et remplissage au fur et à mesure de la string,
	*  jusqu'à la fin de la balise. */
	do{
		file>>ws;
		file.get(ex);
		tmp=tmp+ex;

	}while(ex != '>');

	return tmp;
}

/** Cf. header. */
void Parser::closingTag(ifstream& file, std::string ta){

	tag tmp("<");
	char ex('x');
	size_t found;

	/* Lecture caractère par caractère du flot, et remplissage au fur et à mesure de la string,
	*  jusqu'à la fin de la balise. */
	do{
		file>>ws;
		file.get(ex);
		tmp=tmp+ex;

	}while(ex != '>');

	//si on a pas de balise fermante (ici il devrait il y en avoir normalement une) alors on lance une exception
	found=tmp.find(ta);
	if(found == string::npos)
		throw ReadException("No closing tag "+ta+" found.");
}
//===========================================================lecture commentaire========================================================
/**Cf. header. */
void Parser::jumpComment(ifstream& file){

	tag tmp;
	size_t found;

	do{
		file>>ws;
		getline(file,tmp);
		found=tmp.find("-->");
	}
	while(found == string::npos);

	if(file.eof())
		throw ReadException("No closing tag for comment found.");

}

}//namespace
