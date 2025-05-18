#ifdef USE_SDL
#include <SDL2/SDL.h>
#endif

#include "ppmg.h"

#define WIDTH 800
#define HEIGHT 600

int pixels[WIDTH*HEIGHT];

int main(void) 
{
    ppmg_fill_pixels(pixels, WIDTH, HEIGHT, BACKGROUND);
    {
        // Fill here the canvas.
	}

    const char *filename = "image.ppm";
    Errno err = ppmg_save_to_ppm_file(pixels, WIDTH, HEIGHT, filename);
    if (err) {
        fprintf(stderr, "Error while saving the file '%s'.\n", filename);
    }

#ifdef USE_SDL
	SDL_Window *window = NULL;
	SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

	window = SDL_CreateWindow(
        "Image",          
        SDL_WINDOWPOS_UNDEFINED,       
        SDL_WINDOWPOS_UNDEFINED,       
        WIDTH,                         
        HEIGHT,                        
        SDL_WINDOW_SHOWN               
    );

	if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

	texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,      
        SDL_TEXTUREACCESS_STREAMING,   
        WIDTH,                         
        HEIGHT                 
    );

	if (texture == NULL) {
        fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

	int quit = 0;
	SDL_Event e;

	while (!quit) 
	{
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        
        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(Uint32));
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif // USE_SDL

    return 0;
}
