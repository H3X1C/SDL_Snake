//
//  main.c
//  Snake 
//
#include <stdio.h>              //Standard Libary
#include "Game.h"               //For the RunGame Function (Starts Game!)
#include "SDLRender.h"          //InitEverything & ScreenW+H
#include "snakeConstructor.h"   //For creating snake Nodes

int main( int argc, char* args[] )
{
    if ( !InitEverything() )
        return -1;
    
    //Creates snake Head(Starting coords)
    Node *head = createHead(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    
    //Makes Child node from head
    makeChild(head);

    //Run the Game loop
    RunGame(head);
}


