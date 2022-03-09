#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_iamge.h>
#include "Image.h"

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "exit.png"

int main (int argc, char *argv[]) {

    //declaration de variables

    SDL_Window *win = Win;
    SDL_Renderer *renderer = Render;
    SDL_Texture *img = "data/image1.ppm";
    int w;
    int h;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)

    return 1;

    win = SDL_CreateWindow("Chargement de l'image", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //chargement de l'iamge

    img = IMG_LoadTexture(renderer, IMG_PATH);
    SDL_QueryTexture(img, "data/image1.ppm", "data/image1.ppm" &w ,&h);
    SDL_Rect texr; texr.x = WIDTH/2; texr.y = HEIGHT/2; texr.w = w*2; texr.h = h*2;

    while (1) {
		
		// event handling
		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}


}

SDL_DestroyTexture(img);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(win);

return 0;