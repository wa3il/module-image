#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;

#include "Image.h"
#include "Pixel.h"

//constructeur d'une image de dimension x et y
Image :: Image() : dimx(0),dimy(0){}
Image :: Image(unsigned int x,unsigned int y){
   assert((x>=0) && (y>=0));
   dimx = x;
   dimy = y;
   const unsigned int t_img = dimx * dimy;

   tab = new Pixel[t_img]; //allocation dynamique d'un tableau de dimension h * l

   //for(unsigned int i=0; i<t_img ; i++ ){
      //cout<<tab[i].getRouge()<<","<<tab[i].getVert()<<","<<tab[i].getBleu();
   //}
}

Image :: ~Image(){
   if((dimx!= 0)||(dimy != 0)){
      dimx = 0;
      dimy = 0;
      delete[] tab;
      tab = NULL;
   }
}

Pixel& Image :: getPix(const unsigned int x,const unsigned int y)const{
   assert(x<dimx);
   assert(y<dimy);
   return tab[y*dimx+x];
}

void Image :: setPix (const unsigned int x,const unsigned int y,const Pixel& couleur){
   assert(x<dimx);
   assert(y<dimy);
   
   tab[y*dimx+x].setRouge(couleur.getRouge());
   tab[y*dimx+x].setVert(couleur.getVert());
   tab[y*dimx+x].setBleu(couleur.getBleu());
}

void Image :: dessinerRectangle(const unsigned int Xmin,const unsigned int Ymin,const unsigned int Xmax,const unsigned int Ymax,const Pixel& couleur){
   assert(Xmin<=Xmax);
   assert(Ymin<=Ymax);
   assert(Xmin<=dimx);
   assert(Ymin<=dimx);
   assert(Xmax<=dimx);
   assert(Ymax<=dimx);
   
   for(unsigned int i=Xmin;i<Xmax;i++){
      for(unsigned int j=Ymin;j<Ymax;j++){
         setPix(i,j,couleur);
      }
   }
}

void Image :: effacer(const Pixel& couleur){
   dessinerRectangle(0,0,dimx,dimy,couleur);
}

void Image :: testRegression()const{
   Image im(6,3);
   Pixel pix(20,50,76);

   //test constructeur image
   assert((im.dimx == 6) && (im.dimy == 3));

   //test accesseur get pixel
   assert((pix.getRouge() == 20)&&(pix.getVert() == 50) && (pix.getBleu() == 76));

   //test mutateur set pixel
   pix.setRouge(120);
   pix.setVert(150);
   pix.setBleu(176);

   assert((pix.getRouge() == 120)&&(pix.getVert() == 150) && (pix.getBleu() == 176));

   //test getPix et setPix
   im.setPix(2,2,pix);

   assert(im.getPix(2,2).getRouge() == 120);
   assert(im.getPix(2,2).getVert() == 150);
   assert(im.getPix(2,2).getBleu() == 176);

   //test dessinerectangle
   im.dessinerRectangle(0,0,3,3,pix);
   
   for(unsigned int i = 0;i < 3;i++){
      for(unsigned int j = 0;j < 3;j++){
         assert(im.getPix(i,j).getRouge() == 120 );
         assert(im.getPix(i,j).getVert() == 150 );
         assert(im.getPix(i,j).getBleu() == 176 );
   }
   }

   //test effacer
   Pixel pixefface(255,255,255);
   im.effacer(pixefface);

    for(unsigned int i = 0;i < 3;i++){
      for(unsigned int j = 0;j < 3;j++){
         assert(im.getPix(i,j).getRouge() == 255 );
         assert(im.getPix(i,j).getVert() == 255 );
         assert(im.getPix(i,j).getBleu() == 255 );
   }
   }

} 


void Image::sauver(const std::string & filename) const {
    ofstream fichier(filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; y++)
        for(unsigned int x=0; x<dimx; x++) {
            Pixel& pix = getPix(x,y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}

void Image::ouvrir(const std::string & filename) {
   ifstream fichier (filename.c_str());
   assert(fichier.is_open());
	unsigned int r,g,b;
	string mot;
	dimx = dimy = 0;
	fichier >> mot >> dimx >> dimy >> mot;
	assert(dimx > 0 && dimy > 0);
	if (tab != NULL) delete [] tab;
	tab = new Pixel [dimx*dimy];
   for(unsigned int y=0; y<dimy; y++)
     for(unsigned int x=0; x<dimx; x++) {
         fichier >> r >> g >> b;
         getPix(x,y).setRouge(r);
         getPix(x,y).setVert(g);
         getPix(x,y).setBleu(b);
     }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole(){
    cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy;y++) {
        for(unsigned int x=0; x<dimx;x++) {
            Pixel& pix = getPix(x,y);
            cout << "["<<+pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << "]";
        }
        cout << endl;
    }
}

