/*
 * util.h
 *
 *  Created on: Apr 3, 2011
 *      Author: jakob
 */

#ifndef UTIL_H_
#define UTIL_H_

namespace vhc {
namespace util {

/** Dessine un tore autour de l'origine
 *  @param R rayon du tore
 *  @param r rayon du "cylindre" du tore
 *  @param fraction fraction de tore a dessiner (1 = un tour)
 *  @param slices nombre de cotes du "cylindre" du tore
 *  @param stacks nombre de cotes du tore */
void torus(double R, double r, double fraction, int slices = 12, int stacks = 20);


void cylinder(double base, double top, double height, int slices = 12, int stacks = 20);

/** Dessine les axes unitaires d'un repere cartesien.
 * 	Les axes ont les couleurs suivantes: x -> rouge, y -> vert, z -> bleu */
void axes();

/** Dessine une grille sur le plan XY entre les coordonnees -1 et 1 des deux axes.
 *  Cette grille comporte <code>divisions</code> divisions.*/
void grid(int divisions);

}
}

#endif /* UTIL_H_ */
