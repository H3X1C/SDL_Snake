//
//  foodSpawn.c

//

#include <stdio.h>      //Standard Libary
#include "foodSpawn.h"  //Own Header
#include "SDLRender.h"  //For SDL items

//Coords for food
//3 instead of 0 as the round function could return 0,0 preventing food respawn
int foodX = 1;
int foodY = 1;

int roundUp(int num, int numMultiple)
{
    if(numMultiple == 0){
        return num;
    }
    
    int remainder = num % numMultiple;
    
    if (remainder == 0){
        return numMultiple;
    }
    
    return num + numMultiple - remainder;
}

void foodSpawn(Node *head){
    
    SDL_Rect rect;
    rect.h = 50;
    rect.w = 50;
    
    
    while(foodY == 1 && foodX == 1){
        
        //Feeds screen width and height into a round up to multiple function
        //To ensure foods always on a multiple of 50 to stay on grid
        //-50 to keep off edges
        foodX = roundUp( rand() % SCREEN_WIDTH - 50, 50 );
        foodY = roundUp( rand() % SCREEN_HEIGHT - 50, 50 );
    }
    
    
    //Sets rect coords based of struct
    rect.x = foodX;
    rect.y = foodY;
    
    
    //Render red filled quad
    //RGB + Alpha
    SDL_SetRenderDrawColor( renderer, 255, 10, 10, 0x00 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderFillRect( renderer, &rect );
    
}
