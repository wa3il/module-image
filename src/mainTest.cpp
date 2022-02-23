#include "Image.h"

int main() {
   Image * monImage = new Image(3,2);
   Image * test = new Image();
   monImage->getPix(2,1);
   monImage->testRegression();
   monImage->sauver("./data/monImage.ppm");
   test->ouvrir("./data/imgmodif.ppm");
   monImage->afficherConsole();
   test->afficherConsole();

   delete monImage; 
   delete test;
   
   return 0;
}