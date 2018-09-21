//
//  snakeConstructor.c

//

#include <stdio.h>              //Standard Libary
#include <stdlib.h>             //For Malloc
#include "snakeConstructor.h"   //Own Header

Node *createHead(int x, int y){
    // allocate the data structure
    Node *node = (Node *)malloc(sizeof(Node));
    
    //Sets Node Coords
    node->xPos = x;
    node->yPos = y;

    //Initialises the old pos coords
    node->oldxPos = 0;
    node->oldyPos = 0;

    //Gives the head the first id
    node->id = 0;
    
    //Defaults direction to North
    node->dir = 'N';
    
    //Gives node child with pointer set to NULL
    node->parent = NULL;
    node->child = NULL;
    
    return node;
}

Node *makeNode( int x, int y, Node *parent)
{
    // allocate the data structure
    Node *node = (Node *)malloc(sizeof(Node));
    
    //Sets Node Coords
    node->xPos = x;
    node->yPos = y;

    //Initialises the old pos coords
    node->oldxPos = 0;
    node->oldyPos = 0;

    //Initialises the Random colours
    node->r = rand() % 256;
    node->g = rand() % 256;
    node->b = rand() % 256;

    //Increments the id counter
    node->id = parent->id + 1;
    
    //Sets Direction
    node->dir = parent->dir;
    
    //Gives node child with pointer set to NULL
    node->parent = parent;
    node->child = NULL;

    //printf("Node[%d] Created.\n", node->id);
    
    return node;
}


//Pass it the head and it will recursively search till its find snakes tail
//makes snake seg behind/infront tail one passed
Node *makeChild(Node *node)
{
    
    if(node->child == NULL){
        
        if(node->dir == 'N')
            node->child = makeNode(node->xPos, node->yPos + 50, node);
        else if(node->dir == 'E')
            node->child = makeNode(node->xPos - 50, node->yPos, node);
        else if(node->dir == 'S')
            node->child = makeNode(node->xPos, node->yPos - 50, node);
        else if(node->dir == 'W')
            node->child = makeNode(node->xPos + 50, node->yPos, node);
       
    }else{
        //Recalls function to get to the end of the linked list
        makeChild(node->child);
    }
    return node;
}


//Pass it head and direction
void updateDirection(Node *node, char direction){
    
    //Sets Direction of current node
    node->dir = direction;

}


void updateHead(Node *node){

    node->oldxPos = node->xPos;
    node->oldyPos = node->yPos;
    
    //Updates sake segs coords
    if(node->dir == 'N'){
        
        //y - 50 North
        node->yPos -= 50;
    }
    else if(node->dir == 'E'){
        
        //x + 50 East
        node->xPos += 50;
    }
    else if(node->dir == 'S'){
        
        //y + 50 South
        node->yPos += 50;
    }
    else if(node->dir == 'W'){
        
        //x - 50 West
        node->xPos -= 50;
        
    }
    
}



// Pass it the first child 
void updateTail(Node *node){


    node->oldxPos = node->xPos;
    node->oldyPos = node->yPos;

    // Sets current node to it's parent position
    node->xPos = node->parent->oldxPos;
    node->yPos = node->parent->oldyPos;

    // Sets current node to it's parents direction
    node->dir = node->parent->dir;

 
    // Recursively call the function to the end of the node list
    if(node->child != NULL ){
        updateTail(node->child);
    }
    
}

void updateSnake(Node *head,char dir){

    //Updates Snake Heads Direction
    updateDirection(head, dir);
    
    //Updates heads coords based on direction, modifies x/y coords accordinly +50||-50
    updateHead(head);

    // Passes first child to assume the position of the head, then for rest of nodes to assume position of parent
    updateTail(head->child);

}



