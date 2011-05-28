/*
 * Parser.h
 *
 *  Created on: 11 mai 2011
 *      Author: christian
 */
#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "Vector3D.h"
#include "Accelerator.h"
#include "Dipole.h"
#include "FODO.h"
#include "Quadrupole.h"
#include "StraightElement.h"
#include "Particle.h"
#include "exceptions.h"

using namespace std;

typedef string tag;

namespace vhc {

/** Classe permettant l'extraction d'un Accelerator depuis un fichier .xml.
 * Cette classe contient une méthode <code>extract()<\code> chargée de créer et renvoyer un pointeur
 * 	sur l'accélérateur contenu dans le .xml. <b>ATTENTION<\b>: cette méthode est une "factory method",
 * 	donc il faut soi-même ajouter les <code>delete<\code> après appel à <code>extract()<\code> !
 * 	Sont à supprimer : les pointeurs sur chaque Particle, Element ou Accelerateur contenu dans le .xml
 */

class Parser {
public:

	/** Constructeur d'un Parseur.
	 * @param file chemin d'accès du fichier à lire */
	inline Parser(std::string file)
	: nameOfFile(file)
	{}

	/**Destructeur virtuel. */
	inline virtual ~Parser() {}

	/** Méthode chargée de lire le fichier .xml (lance une exception si le fichier n'est pas valide),
	 * de créer et renvoyer un accélérateur par appel de fonction privées.
	 * @return Accelerator construit avec les données récoltées dans le fichier .xml */
	Accelerator* extract();

protected:

	/** Contient le chemin d'accès du fichier à lire. */
	string nameOfFile;

private:

//===========================================balises ouvrantes==========================================================================

	/** Balises ouvrantes d'un système.
	 * On ne peut pas y spécifier des constantes, car elle font partie d'un namespace. */
	static tag system;
	static tag accelerator;
	static tag comment;

	/** Balises ouvrantes d'une particule. */
	static tag particle;
	static tag position;
	static tag mass;
	static tag charge;
	static tag energy;
	static tag direction;

	/** Balises ouvrantes d'un Element. */
	static tag entryPos;
	static tag exitPos;
	static tag sectionRadius;

	/** Balises ouvrantes d'un dipole. */
	static tag dipole;
	static tag curvature;
	static tag magneticField;

	/** Balise ouvrantes commune aux quadrupoles et aux fodo. */
	static tag focCoeff;

	/** Balises ouvrantes d'une FODO. */
	static tag fodo;
	static tag straightLength;

	/** Balises ouvrante d'un quadrupole. */
	static tag quadrupole;

	/** Balises ouvrantes d'une straightElement. */
	static tag straightElement;

//===================================================balises fermantes==================================================================

	/** Balises fermantes d'un système. */
	static tag systemCl;
	static tag acceleratorCl;
	static tag commentCl;

	/** Balises fermantes d'une Particle. */
	static tag particleCl;
	static tag positionCl;
	static tag massCl;
	static tag chargeCl;
	static tag energyCl;
	static tag directionCl;

	/** Balises fermantes d'un Element. */
	static tag entryPosCl;
	static tag exitPosCl;
	static tag sectionRadiusCl;

	/** Balises fermantes d'un dipole. */
	static tag dipoleCl;
	static tag curvatureCl;
	static tag magneticFieldCl;

	/** Balise fermantes commune aux quadrupoles et aux fodo. */
	static tag focCoeffCl;

	/** Balises fermantes d'une FODO. */
	static tag fodoCl;
	static tag straightLengthCl;

	/** Balises fermantes d'un quadrupole. */
	static tag quadrupoleCl;

	/** Balises fermantes d'une straightElement. */
	static tag straightElementCl;

//=============================================================méthodes=================================================================

	/** Lit le fichier .xml.
	 * 	@param file fichier à lire
	 *  @param acc référence sur un Accelerator déjà construit */
	void readFile(ifstream& file, Accelerator& acc);

		/** Lit la balise system. Cette méthode appelle readConstants et buildAccelerator.
		 * 	@param file fichier à lire
		 *	@param acc référence sur un Accelerator déjà construit */
		void readSystem(ifstream& file, Accelerator& acc);

			/** Ajoute les différents éléments et particules du fichier dans l'Accelerator passé en argument.
			 * 	@param file fichier à lire
			 *  @param acc référence sur un Accelerator déjà construit */
			void buildAccelerator(ifstream& file, Accelerator const& acc);

				/** Construction d'une nouvelle Particle.
				 * 	@param file fichier à lire
				 * @return Particle créée avec les valeurs récoltées dans le fichier .xml */
				Particle* buildParticle(ifstream& file);

				/** Construction d'une nouvelle FODO.
				 * 	@param file fichier à lire
				 * @return FODO créée avec les valeurs récoltées dans le fichier .xml */
				FODO* buildFODO(ifstream& file);

				/** Construction d'un nouveau Dipole.
				 * 	@param file fichier à lire
				 * @return Dipole créé avec les valeurs récoltées dans le fichier .xml */
				Dipole* buildDipole(ifstream& file);

				/** Construction d'un nouveau quadrupole.
				 * 	@param file fichier à lire
				 * @return Quadrupole créé avec les valeurs récoltées dans le fichier .xml	*/
				Quadrupole* buildQuadrupole(ifstream& file);

				/** Construction d'un nouveau StraightElement.
				 * 	@param file fichier à lire
				 * @return StraightElement créé avec les valeurs récoltées dans le fichier .xml */
				StraightElement* buildStraightElement(ifstream& file);

	/** Lit un double.
	 * 	@param file fichier à lire */
	double readOneDouble(ifstream& file);
	/** Saute une virgule.
	 * 	@param file fichier à lire*/
	void readComma(ifstream& file);

	/** Lit un Vector3D.
	 * 	@param file fichier à lire*/
	Vector3D readVector3D(ifstream& file);
	/** Lit ue balise.
	 * 	@param file fichier à lire*/
	tag readOneTag(ifstream& file);
	/** Cherche et lit une balise fermante contenant à la chaîne de caractère passée en argument.
	 * @param file fichier à lire
	 * @param ta contenu de la balise à trouver */
	void closingTag(ifstream& file, std::string ta);
	/** Cherche et lit une balise fermante d'un commentaire.
	 * 	@param file fichier à lire*/
	void jumpComment(ifstream& file);

};

}

#endif /* PARSER_H_ */
