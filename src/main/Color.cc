/*
 * Color.cc
 *
 *  Created on: 27 mai 2011
 *      Author: christian
 */

#include "Color.h"

using namespace std;

namespace vhc {

//TODO comment importer le tableau statique depuis le header?
const double Color::red[] = {1,0,0,1};
const double Color::green[] = {0,1,0,1};
const double Color::blue[] = {0,0,1,1};
const double Color::turquoise[] = {0,1,1,1};
const double Color::purple[] = {1,0,1,1};
const double Color::yellow[] = {1,1,0,1};
const double Color::white[] = {1,1,1,1};
const double Color::black[] = {0,0,0,1};
const double Color::grey[] = {0.6,0.6,0.6,1};

vector<double> Color::convertTabToVector(const double tab[]) {
	vector <double> tmp;
	for (unsigned int i(0); i < 4; ++i) {
		tmp.push_back(tab[i]);
	}
	return tmp;
}

void Color::setColor(vector<double> const& co){
	color = co;
}

void Color::setColor(string co) {

	switch(co){
	case "red" :
		color = convertTabToVector(red);
		break;
	case "green" :
		color = convertTabToVector(green);
		break;
	case "blue" :
		color = convertTabToVector(blue);
		break;
	case "turquoise" :
		color = convertTabToVector(turquoise);
		break;
	case "purple" :
		color = convertTabToVector(purple);
		break;
	case "yellow" :
		color = convertTabToVector(yellow);
		break;
	case "white" :
		color = convertTabToVector(white);
		break;
	case "black" :
		color = convertTabToVector(black);
		break;
	case "grey" :
		color = convertTabToVector(grey);
		break;
	default:
		throw IllegalArgumentException("Color is not defined.");
	}
}

vector<double> Color::getColor() const {
	return color;
}

}
