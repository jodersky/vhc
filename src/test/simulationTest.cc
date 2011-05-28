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

int main(){
	try{
		Parser pars("./simulation.xml");

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
