/*
 * util.h
 *
 *  Created on: Apr 3, 2011
 *      Author: jakob
 */

#ifndef UTIL_H_
#define UTIL_H_

namespace vhc {

/** Contient des fonctions utilitaires. */
namespace util {

/** Dessine un tore autour de l'origine, sur le plan xy.
 *  @param R rayon du tore
 *  @param r rayon du "cylindre" du tore
 *  @param fraction fraction du tore a dessiner (1 = un tour)
 *  @param slices nombre de cotes du "cylindre" du tore
 *  @param stacks nombre de cotes du tore */
void torus(double R, double r, double fraction, int slices = 12, int stacks = 20);


/** Dessine un cylindre partant de l'origine, direction de l'axe z.
 *  @param base rayon de la base du cylindre
 *  @param top rayon du haut du cylindre
 *  @param height hauteur du cylindre
 *  @param slices cotes laterales du cylindre
 *  @param stacks divisions en hauteur du cylindre */
void cylinder(double base, double top, double height, int slices = 12, int stacks = 20);


/** Dessine une sphere centree a l'origine.
 *  @param radius rayon de la sphere
 *  @param slices cotes laterales de la sphere
 *  @param stacks divisions en hauteur de la sphere */
void sphere(double radius, int slices = 12, int stacks = 20);

/** Dessine les axes unitaires d'un repere cartesien.
 * 	Les axes Ox, Oy et Oz ont les couleurs respectifs suivantes rouge, vert et bleu. */
void axes();

/** Dessine une grille sur le plan xy entre les coordonnees -1 et 1 des deux axes.
 *  Cette grille comporte <code>divisions</code> divisions.*/
void grid(int divisions);

/** Dessine une croix de visee au milieu du viewport. */
void crosshair();

}
}

#endif /* UTIL_H_ */
