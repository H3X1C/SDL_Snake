//
//  SDLRender.c
//

#include <stdio.h>              // Standard Libary
#include "SDLRender.h"          // Own Header
#include "foodSpawn.h"          // For rendering food
#include "Game.h"               // For Update All


// Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

// Starting speed
int speed = 170;

SDL_Texture* loadTexture( char *path );
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture = NULL;

// Audio vars
SDL_AudioSpec wavSpec;
SDL_AudioDeviceID deviceId;
Uint32 wavLength;
Uint8 *wavBuffer;


void Render(Node *head)
{
    // Clear screen
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
    
    // Render texture to screen
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    
    // Call recursive draw function
    updateAll( head );
    
    foodSpawn( head );
    
    // Render the changes above
    SDL_RenderPresent( renderer );
    
}

bool InitEverything()
{
    if ( !InitSDL() )
        return false;
    
    if ( !CreateWindow() )
        return false;
    
    if ( !CreateRenderer() )
        return false;
    
    SetupRenderer();
    
    return true;
}

bool InitSDL()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    
    return true;
}
bool CreateWindow()
{
    
    // Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }
    
    
    window = SDL_CreateWindow( "SNAKE | SCORE: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if ( window == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    
    return true;
}
bool CreateRenderer()
{
    renderer = SDL_CreateRenderer( window, -1, 0 );
    
    if ( renderer == NULL )
    {
        printf( "Failed to create render! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    
    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    
    return true;
}
void SetupRenderer()
{
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // Set color of renderer to green
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
    
}


bool loadMedia()
{
    // Loading success flag
    bool success = true;
    
    // Load PNG texture
    texture = loadTexture( "texture.png" );
    if( texture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}

bool loadSound()
{

    // Loading success flag
    bool success = true;

    if( SDL_LoadWAV("foodPickup.wav", &wavSpec, &wavBuffer, &wavLength) == NULL ){
        printf( "Failed to load sound file!\n" );
        success = false;
    }

    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    // Unpauses the audio
    SDL_PauseAudioDevice(deviceId, 0);

    return success;
}

void playSound()
{
    int status = SDL_QueueAudio(deviceId, wavBuffer, wavLength); 
    if(status)
        printf("Error creating queue!\n");
}

SDL_Texture* loadTexture( char *path )
{
    // The final texture
    SDL_Texture* newTexture = NULL;
    
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! \nSDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        
        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}


// Exit operations
void closeAll()
{
    // Free loaded image
    SDL_DestroyTexture( texture );
    texture = NULL;
    
    // Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    // Close Audio and free buffer for audio
    SDL_CloseAudio();
	SDL_FreeWAV(wavBuffer);
    
    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    printf("CLEANUP DONE\n");
}




