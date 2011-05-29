/*
 * simulationTest.cc
 *
 *  Created on: 28 mai 2011
 *      Author: christian
 */
#include <iostream>
#include "Parser.h"
#include "Accelerator.h"
#include "exceptions.h"

using namespace std;
using namespace vhc;

/* Ne marche pas. L'ouverture du fichier est impossible.
 * Pourtant j'ai essayé en exercice le même bout de code
 * [ que dans la méthode extract() ] pour ouvrir un fichier, et ça marchait....
 * Je suspecte un problème avec la makefile.*/

int main(){
	try{
		Parser pars("./accelerator.xml");

		Accelerator* a = pars.extract();

		cout<< *a <<endl;

		a->clear();

		delete a;
	}
	catch(Exception const& ex){
		cout<<ex.getExceptionType()<<endl
			<<ex.getMessage()<<endl;
	}
	return 0;
}
