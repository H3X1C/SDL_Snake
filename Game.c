//
//  Game.c
//

#include <stdio.h>              // Standard Libary
#include "Game.h"               // Own Header
#include "structs.h"            // For Node Structure
#include "SDLRender.h"          // For SDL Items
#include "snakeConstructor.h"   // For updating Snake Segment Nodes
#include "foodSpawn.h"          // For food Collisions

// Direction Indicators
bool north = false; // UP
bool east = false;  // RIGHT
bool south = false; // DOWN
bool west = false;  // LEFT

int score;
char titleText[255];

void checker(Node *theNode, Node *origNode){

    if(theNode->id != origNode->id && theNode->xPos == origNode->xPos && theNode->yPos == origNode->yPos  ){
        printf("GAME OVER - SCORE: %d\n", score);
        printf("Node[%d] collided with Node[%d]\n", origNode->id, theNode->id);
        closeAll();
        exit(0);
    }

    // Recursive
    if(theNode->child != NULL ){
        checker(theNode->child, origNode);
    }
}

void updateAll(Node *node){
    
    SDL_Rect rect;
    rect.h = 50;
    rect.w = 50;


     // Snake Self colision (Only call if Head node)
    if(node->parent == NULL)
        checker(node,node);
    
    // Screen edge detection
    if(node->xPos > SCREEN_WIDTH || node->xPos < 0 || node->yPos > SCREEN_HEIGHT || node->yPos < 0){
        // Out of bounds
        printf("GAME OVER - SCORE: %d\n", score);
        closeAll();
        exit(0);
    }

    // Food detection
    if(node->xPos == foodX && node->yPos == foodY ){
        score ++;                                           // Incrment score counter 
        sprintf(titleText, "SNAKE | SCORE: %d", score);     // Format title string
        SDL_SetWindowTitle(window, titleText);              // Set title string
        playSound();                                        // Play pickup sound effect
        makeChild(node);                                    // Grow snake with a new node
        foodX = 1;                                          // Reset food            
        foodY = 1;                                          // ^
        speed -= 5;                                         // Increase game speed
    }
    
    // Sets rect coords based of struct
    rect.x = node->xPos;
    rect.y = node->yPos;
    
    // Render red filled quad
    // RGB + Alpha
    SDL_SetRenderDrawColor( renderer, node->r, node->g, node->b, 0xFF );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderFillRect( renderer, &rect );
    
    // Recursive
    if(node->child != NULL ){
        updateAll(node->child);
    }

}


void RunGame(Node *head)
{
    bool loop = true;
    
    // Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        closeAll();
        exit(0);
    }

    if( !loadSound() )
    {
        printf( "Failed to load sound!\n" );
        closeAll();
        exit(0);
    }
    
    while ( loop )
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            
            if ( event.type == SDL_QUIT ){
                loop = false;
                closeAll();
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_RIGHT:
                        
                        north = false;
                        east = true;
                        south = false;
                        west = false;
                        
                        
                        break;
                    case SDLK_LEFT:
                        
                        north = false;
                        east = false;
                        south = false;
                        west = true;
                        
                        break;
                    case SDLK_DOWN:
                        
                        north = false;
                        east = false;
                        south = true;
                        west = false;
                        
                        break;
                    case SDLK_UP:
                        
                        north = true;
                        east = false;
                        south = false;
                        west = false;
                        
                        break;
                    case SDLK_SPACE:
                        // Create segment
                        break;
                    default :
                        break;
                }
            }
        }
        
        
        // Movement - Calls functions to adjust x,y of Snake segments
        if(north == true){
            updateSnake(head, 'N');
        }else if(east == true){
            updateSnake(head, 'E');
        }else if(south == true){
            updateSnake(head, 'S');
        }else if(west == true){
            updateSnake(head, 'W');
        }
        
        // Calls Render function to render, snake & food
        Render(head);
        
        // Refresh rate (Frame Rate)
        SDL_Delay( speed );
    }
}


