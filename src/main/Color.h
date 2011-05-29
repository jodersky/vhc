/*
 * Color.h
 *
 *  Created on: 27 mai 2011
 *      Author: christian
 */

#ifndef COLOR_H_
#define COLOR_H_
#include <string>
#include <vector>
#include "exceptions.h"

using namespace std;

namespace vhc {

/** Représente un objet coloré de couleurs suivantes :
 * rouge, vert, bleu, turquoise, violet, jaune, blanc, noir et gris.
 * <b>ATTENTION<\b> : la méthode <code>setColor(string color = "white")<\code> lance une exception si la couleur n'est pas reconnue.
 **/

class Color {
public:
	Color() {}
	virtual ~Color() {}

	/** Retourne (sous forme de vector<double>) la couleur de cet objet. **/
	vector<double> getColor() const;


	/** Affecte la couleur de l'objet selon l'argument de la fonction.(Ici un string) **/
	void setColor(string color = "white");

	/** Affecte la couleur de l'objet selon l'argument de la fonction
	 * (Ici un vector, donc à appeler si on souhaite utiliser d'autres couleurs que celles de la classe Color.) **/
	void setColor(vector<double> const& co);

protected:
	vector<double> color;
private:
	vector<double> convertTabToVector(double tab[]);
	static const double red[4];
	static const double green[4];
	static const double blue[4];
	static const double turquoise[4];
	static const double purple[4];
	static const double yellow[4];
	static const double white[4];
	static const double black[4];
	static const double grey[4];
};

}

#endif /* COLOR_H_ */
