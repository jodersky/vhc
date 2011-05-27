/*
 * Parser.h
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */
#include <iostream>
#include <string>
#include <fstream>
#include "Vector3D.h"
#include "Accelerator.h"
#include "Dipole.h"
#include "FODO.h"
#include "Quadrupole.h"
#include "StraightElement.h"
#include "Particle.h"
#include "exceptions.h"

#ifndef PARSER_H_
#define PARSER_H_

typedef tag string;
typedef tagStat static tag;

namespace vhc {

/** Cette classe contient une méthode <code>extract<\code> chargée de créer et renvoyer un pointeur
 * 	sur l'accélérateur contenu dans le .xml. <b>ATTENTION : cette méthode est une "factory method",
 * 	donc il faut soi-même ajouter le <code>delete<\code> après appel à <code>extract<\code> !<\b>
 * 	Sont à supprimer : les pointeurs sur chaque particule, element ou accelerateur contenu dans le .xml
 **/

class Parser {
public:
	Parser();

	/** Constructeur d'un Parseur. Prend en argument le chemin d'accès du fichier à lire. **/
	Parser(std::string file);

	/**Destructeur virtuel. **/
	virtual ~Parser();

	/** Méthode chargée de lire le fichier .xml et de renvoyer un pointeur sur l'accélérateur ainsi construit. **/
	Accelerator* extract();
private:

	/** Attribut contenant le chemin d'accès du fichier. **/
	string nameOfFile;

//===========================================constantes=================================================================================

	const double CP;
	const double EP;
	const double PROTON_MASSP;
	const double ELECTRON_MASSP;
	const double GeVP = 1E9 * EP;

//===========================================balises ouvrantes==========================================================================

	/** Balises ouvrantes d'un système. **/
	tagStat system;
	tagStat accelerator;
	tagStat comment;

	/** Balises ouvrantes des constantes. **/
	tagStat constants;
	tagStat dt;
	tagStat C;
	tagStat E;
	tagStat PROTON_MASS;
	tagStat ELECTRON_MASS;

	/** Balises ouvrantes d'une particule. **/
	tagStat particle;
	tagStat position;
	tagStat mass;
	tagStat charge;
	tagStat energy;
	tagStat direction;

	/** Balises ouvrantes d'un Element. **/
	tagStat entryPos;
	tagStat exitPos;
	tagStat sectionRadius;

	/** Balises ouvrantes d'un dipole. **/
	tagStat dipole;
	tagStat curvature;
	tagStat magneticField;

	/** Balise ouvrantes commune aux quadrupoles et aux fodo. **/
	tagStat focCoeff;

	/** Balises ouvrantes d'une FODO. **/
	tagStat fodo;
	tagStat straightLength;

	/** Balises ouvrante d'un quadrupole. **/
	tagStat quadrupole;

	/** Balises ouvrantes d'une straightElement. **/
	tagStat straightElement;

//===================================================balises fermantes==================================================================

	/** Balises fermantes d'un système. **/
	tagStat systemCl;
	tagStat acceleratorCl;
	tagStat commentCl;

	/** Balises fermantes des constantes. **/
	tagStat constantsCl;
	tagStat dtCl;
	tagStat CCl;
	tagStat ECl;
	tagStat PROTON_MASSCl;
	tagStat ELECTRON_MASSCl;

	/** Balises fermantes d'une particule. **/
	tagStat particleCl;
	tagStat positionCl;
	tagStat massCl;
	tagStat chargeCl;
	tagStat energyCl;
	tagStat directionCl;

	/** Balises fermantes d'un Element. **/
	tagStat entryPosCl;
	tagStat exitPosCl;
	tagStat sectionRadiusCl;

	/** Balises fermantes d'un dipole. **/
	tagStat dipoleCl;
	tagStat curvatureCl;
	tagStat magneticFieldCl;

	/** Balise fermantes commune aux quadrupoles et aux fodo. **/
	tagStat focCoeffCl;

	/** Balises fermantes d'une FODO. **/
	tagStat fodoCl;
	tagStat straightLengthCl;

	/** Balises fermantes d'un quadrupole. **/
	tagStat quadrupoleCl;

	/** Balises fermantes d'une straightElement. **/
	tagStat straightElementCl;

//=============================================================méthodes=================================================================

	/** Crée et renvoie un accélérateur par appel de la fonction readFile. **/
	Accelerator* extract();

	/** Lit le fichier .xml. **/
	void readFile(ifstream& file, Accelerator& acc);

		/** Lit la balise system. Cette méthode appelle readConstants et buildAccelerator. **/
		void readSystem(ifstream& file, Accelerator& acc);

			/** Affecte les attributs statiques contenant les constantes physiques. **/
			void readConstants(ifstream& file);

				/** Affecte l'attribut dt. **/
				void readdt(ifstream& file);

				/** Affecte l'attribut C. **/
				void readC(ifstream& file);

				/** Affecte l'attribut E. **/
				void readE(ifstream& file);

				/** Affecte l'attribut PROTON_MASS. **/
				void readPROTON_MASS(ifstream& file);

				/** Affecte l'attribut ELECTRON_MASS. **/
				void readELECTRON_MASS(ifstream& file);

			/** Ajoute les différents éléments et particules du fichier dans l'Accelerator passé en argument. **/
			void buildAccelerator(ifstream& file, Accelerator const& acc);

				/** Construction d'une nouvelle Particle. **/
				Particle* buildParticle(ifstream& file);

				/** Construction d'une nouvelle FODO. **/
				FODO* buildFODO(ifstream& file);

				/** Construction d'un nouveau Dipole. **/
				Dipole* buildDipole(ifstream& file);

				/** Construction d'un nouveau quadrupole.	**/
				Quadrupole* buildQuadrupole(ifstream& file);

				/** Construction d'un nouveau StraightElement. **/
				StraightElement* buildStraightElement(ifstream& file);

	/** Lit un char. **/
	char readOneChar(ifstream& file);
	/** Lit un int. **/
	int readOneInt(ifstream& file);
	/** Lit un double. **/
	double readOneDouble(ifstream& file);
	/** Saute une virgule. **/
	void readComma(ifstream& file);

	/** Lit un Vector3D. **/
	Vector3D readVector3D(ifstream& file);
	/** Lit ue balise. **/
	tag readOneTag(ifstream& file);
	/** Cherche et lit une balise fermante. **/
	void closingTag(ifstream& file);
	/** Saute un commentaire. **/
	void jumpComment(ifstream& file);

};

}
#endif /* PARSER_H_ */
