#include <iostream>
#include <cassert>

using namespace std;

#include "Pixel.h"

//constructeur
Pixel :: Pixel():r(0),g(0),b(0){}
Pixel :: Pixel(unsigned char nr,unsigned char ng,unsigned char nb):r(nr),g(ng),b(nb){}

//destructeur
//Pixel :: ~Pixel(){}

//accesseur rouge, vert, bleu
unsigned char Pixel :: getRouge()const{
    return r;
}

unsigned char Pixel :: getVert()const{
    return g;
}

unsigned char Pixel :: getBleu()const{
    return b;
}

//mutateurs rouge, vert, bleu
void Pixel :: setRouge(unsigned char nr){
    r = nr;
}

void Pixel :: setVert(unsigned char nv){
    g = nv;
}

void Pixel :: setBleu(unsigned char nb){
    b = nb;
}