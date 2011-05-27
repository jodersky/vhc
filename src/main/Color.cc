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
double Color::red[4] = {1,0,0,1};
double Color::green[4] = {0,1,0,1};
double Color::blue[4] = {0,0,1,1};
double Color::turquoise[4] = {0,1,1,1};
double Color::purple[4] = {1,0,1,1};
double Color::yellow[4] = {1,1,0,1};
double Color::white[4] = {1,1,1,1};
double Color::black[4] = {0,0,0,1};
double Color::grey[4] = {0.6,0.6,0.6,1};

vector<double> Color::convertTabToVector(double const& tab[4]) {
	vector <double> tmp;
	for (unsigned int i(0); i < 4; ++i) {
		tmp.push_back(tab[i]);
	}
	return tmp;
}

void Color::setColor(vector<double> const& co){
	color = co;
}

void Color::setColor(string co) const {

	switch(co){
	case "red" :
		color = convertTabToVector(red[4]);
		break;
	case "green" :
		color = convertTabToVector(green[4]);
		break;
	case "blue" :
		color = convertTabToVector(blue[4]);
		break;
	case "turquoise" :
		color = convertTabToVector(turquoise[4]);
		break;
	case "purple" :
		color = convertTabToVector(purple[4]);
		break;
	case "yellow" :
		color = convertTabToVector(yellow[4]);
		break;
	case "white" :
		color = convertTabToVector(white[4]);
		break;
	case "black" :
		color = convertTabToVector(black[4]);
		break;
	case "grey" :
		color = convertTabToVector(grey[4]);
		break;
	default:
		throw IllegalArgumentException("Color is not defined.");
	}
}

vector<double> Color::getColor() const {
	return color;
}

string Color::getStringColor() const {

	string tmp;

	switch(color){
	case convertTabToVector(red) :
		tmp="red";
		break;
	case convertTabToVector(green) :
		tmp="green";
		break;
	case convertTabToVector(blue) :
		tmp="blue";
		break;
	case convertTabToVector(turquoise) :
		break;
		tmp="turquoise";
	case convertTabToVector(purple) :
		tmp="purple";
		break;
	case convertTabToVector(yellow) :
		tmp="yellow";
		break;
	case convertTabToVector(white) :
		tmp="white";
		break;
	case convertTabToVector(black) :
		tmp="black";
		break;
	case convertTabToVector(grey) :
		tmp="grey";
		break;
	default :
		tmp="No valid color.";
		break;
	}

	return tmp;
}

}
