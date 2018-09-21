//
//  SDLRender.h
//

#ifndef SDLRender_h
#define SDLRender_h

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// Starting speed
extern int speed;

// Intilise SDL Items
extern SDL_Texture* loadTexture( char *path );
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;

bool InitEverything();

bool InitSDL();

bool loadMedia();

bool loadSound();

void playSound();

bool CreateWindow();

bool CreateRenderer();

void SetupRenderer();

void Render();

void closeAll();            // Frees media and shuts down SDL

#endif /* SDLRender_h */
