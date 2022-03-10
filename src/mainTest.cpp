#include "Image.h"

int main() {
   Image * monImage = new Image(3,2);
   monImage->getPix(2,1);
   monImage->testRegression();
   monImage->sauver("./data/monImage.ppm");
   monImage->ouvrir("./data/monImage.ppm");
   monImage->afficherConsole();

   delete monImage; 
   
   return 0;
}