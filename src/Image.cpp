#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;

#include "Image.h"
#include "Pixel.h"

float temps (){
    return float(SDL_GetTicks())/ CLOCKS_PER_SEC;///conversion des ms en secondes en divisant par 1000
}

//constructeur d'une image de dimension x et y
Image :: Image() : dimx(0),dimy(0){ tab = nullptr;}
Image::Image(unsigned int x, unsigned int y) : dimx(x), dimy(y) {  ///Défintion du constructeur de la classe

    assert(x >= 0);
    assert(y >= 0);
    tab= new Pixel[dimx * dimy];

    }

Image::~Image() {  /// définition du destructeur

    dimx=0;
    dimy=0;
    delete [] tab;

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

void Image :: effacer(const Pixel couleur){
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
   pix.setRouge(10);
   pix.setVert(150);
   pix.setBleu(176);

   assert((pix.getRouge() == 10)&&(pix.getVert() == 150) && (pix.getBleu() == 176));

   //test getPix et setPix
   im.setPix(2,2,pix);

   assert(im.getPix(2,2).getRouge() == 10);
   assert(im.getPix(2,2).getVert() == 150);
   assert(im.getPix(2,2).getBleu() == 176);

   //test dessinerectangle
   im.dessinerRectangle(0,0,3,3,pix);
   
   for(unsigned int i = 0;i < 3;i++){
      for(unsigned int j = 0;j < 3;j++){
         assert(im.getPix(i,j).getRouge() == 10 );
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


void Image::sauver(const string & filename) const {
    ofstream fichier (filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            Pixel& pix = getPix(x,y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}



void Image::ouvrir(const string & filename) {
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
    unsigned int r,g,b;
    string mot;
    dimx = dimy = 0;
    fichier >> mot >> dimx >> dimy >> mot;
    assert(dimx > 0 && dimy > 0);
    if (tab != NULL) delete [] tab;
    tab = new Pixel [dimx*dimy];
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            fichier >> r >> g >> b;
            getPix(x,y).setRouge(r);
            getPix(x,y).setVert(g);
            getPix(x,y).setBleu(b);
        }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}


void Image::afficherConsole(){
    std::cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy; y++) {
        for(unsigned int x=0; x<dimx; x++) {
            Pixel& pix = getPix(x,y);
            cout << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
        cout << endl;
    }
}

void Image::afficherInit(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout<<"erreur lors de l'initialisation de la SDL:"<<SDL_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }
    if (TTF_Init() != 0){
        cout<<"erreur lors de l'initialisation de la SDL:"<<SDL_GetError()<<endl;
        SDL_Quit();
        exit(1);
         }
    
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags)& imgFlags)){
        cout<<"erreur lors de l'initialisation de la SDL:"<<SDL_GetError()<<endl;
        SDL_Quit();
        exit(1); 
    }

    /**creation de la fenetre*/
    window = SDL_CreateWindow( "Module image",
        SDL_WINDOWPOS_CENTERED, //x coin haut/gauche
        SDL_WINDOWPOS_CENTERED,
        200,200,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL){
        cout << "erreur lors de la creation de la fenetre:"<<SDL_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }
    

    sauver("./data/ImageSDL.ppm");
    surface = IMG_Load("./data/ImageSDL.ppm");

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.h = 200;
    r.w = 200;

    SDL_RenderCopy(renderer,texture,NULL,&r);
    SDL_RenderPresent(renderer);

}



void Image::afficherBoucle(){
    SDL_Event events;
    SDL_Rect r;
    bool quit = false;

    ///Uint32 t = SDL_GetTicks(),nt;

    while (!quit){
            SDL_WaitEvent(&events);
            if (events.type == SDL_QUIT) {quit = true;}
            switch (events.key.keysym.scancode){
                case SDL_SCANCODE_ESCAPE:                        
                    quit = true;
                    break;
                case SDL_SCANCODE_G :
                    SDL_RenderClear(renderer);
                        r.x += 10;
                        r.y += 10;
                        r.h -= 20;
                        r.w -= 20;
                    SDL_RenderCopy(renderer,texture,NULL,&r);
                    break;
                case SDL_SCANCODE_T :
                    SDL_RenderClear(renderer);
                        r.x -= 10;
                        r.y -= 10;
                        r.h += 20;
                        r.w += 20;
                    SDL_RenderCopy(renderer,texture,NULL,&r);
                    break;
                default : break;
                    
                }
            
        SDL_RenderPresent(renderer);
    }

}
    

void Image :: afficherDetruit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Image::afficher(){
    afficherInit();
    afficherBoucle();
    afficherDetruit();
}
