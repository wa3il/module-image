#ifndef _Image_H_
#define _Image_H_

#include "Pixel.h"
#include <fstream>
#include <string>

class Image{

    private :
        Pixel* tab;     // le tableau 1D de pixel
        unsigned int dimx, dimy;        // les dimensions de l'image

    public :

        // Constructeur par défaut de la classe: initialise dimx et dimy à 0
        // ce constructeur n'alloue pas de pixel
        Image();

        // Constructeur de la classe: initialise dimx et dimy (après vérification)
        // puis alloue le tableau de pixel dans le tas (image noire)
        Image(unsigned int dimx,unsigned int dimy);

        // Destructeur de la classe: déallocation de la mémoire du tableau de pixels
        // et mise à jour des champs dimx et dimy à 0
        ~Image();

        // Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
        // la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
        Pixel& getPix(const unsigned int x,const unsigned int y)const;

        // Mutateur : modifie le pixel de coordonnées (x,y)
        void setPix (const unsigned int x,const unsigned int y,const Pixel& couleur);

        // Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
        void dessinerRectangle(const unsigned int Xmin,const unsigned int Ymin,const unsigned int Xmax,const unsigned int Ymax,const Pixel& couleur);

        // Efface l'image en la remplissant de la couleur en paramètre
        // (en appelant dessinerRectangle avec le bon rectangle)
        void effacer (const Pixel& couleur);

        // Effectue une série de tests vérifiant que le module fonctionne et
        // que les données membres de l'objet sont conformes
        void testRegression ()const;

        //fonctions d'entrée sortie:
        //sauver une image dans un fichier
        void sauver(const std::string & filename) const;

        //ouvrir une image depuis un fichier
        void ouvrir(const std::string & filename);

        //afficher sur la console une image
        void afficherConsole();

};

#endif