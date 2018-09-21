//
//  snakeConstructor.c
//

#include <stdio.h>              //Standard Libary
#include <stdlib.h>             //For Malloc
#include "snakeConstructor.h"   //Own Header

// Creates the Head Node
Node *createHead(int x, int y){
    // allocate the data structure
    Node *node = (Node *)malloc(sizeof(Node));
    
    // Sets Node Coords
    node->xPos = x;
    node->yPos = y;

    // Sets the old pos coords
    node->oldxPos = x;
    node->oldyPos = y;

    // Gives the head the starting id = 0
    node->id = 0;
    
    // Defaults direction passed 'North'
    node->dir = 'N';
    
    // Gives node child with pointer set to NULL
    node->parent = NULL;
    node->child = NULL;
    
    return node;
}

// Creates a new node given it's parent and X/Y Coords
Node *makeNode( int x, int y, Node *parent)
{
    // allocate the data structure
    Node *node = (Node *)malloc(sizeof(Node));
    
    // Sets Node Coords
    node->xPos = x;
    node->yPos = y;

    // Sets the old pos coords
    node->oldxPos = x;
    node->oldyPos = y;

    // Initialises the Random colour for the node RGB
    node->r = rand() % 256;
    node->g = rand() % 256;
    node->b = rand() % 256;

    // Increments the id counter
    node->id = parent->id + 1;
    
    // Sets Direction
    node->dir = parent->dir;
    
    // Gives node child with pointer set to NULL
    node->parent = parent;
    node->child = NULL;
    
    return node;
}


// Pass it the head and it will recursively search till its find snakes tail
// Creates a new node at the end of the tail
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
        // Recalls function to get to the end of the linked list (Recursive)
        makeChild(node->child);
    }
    return node;
}


// Updates the direction of a given node
void updateDirection(Node *node, char direction){
    
    // Sets Direction of current node
    node->dir = direction;

}


// Given the head will update it's position
void updateHead(Node *node){

    // Store current coords in the old coords field
    node->oldxPos = node->xPos;
    node->oldyPos = node->yPos;
    
    //Update Node Pos based on direction of the node
    if(node->dir == 'N')
        node->yPos -= 50;       //y - 50 North
    else if(node->dir == 'E')
        node->xPos += 50;       //x + 50 East
    else if(node->dir == 'S')
        node->yPos += 50;       //y + 50 South
    else if(node->dir == 'W')
        node->xPos -= 50;       //x - 50 West
    
}


// Pass it the child of the head and it will recursively set a given nodes position 
// based off it's parents oldPos
void updateTail(Node *node){

    // stores current nodes old pos to it's current
    node->oldxPos = node->xPos;
    node->oldyPos = node->yPos;

    // Sets current node pos to it's parent position
    node->xPos = node->parent->oldxPos;
    node->yPos = node->parent->oldyPos;

    // Sets current node to it's parents direction
    node->dir = node->parent->dir;
 
    // Recursively call the function to the end of the node list
    if(node->child != NULL ){
        updateTail(node->child);
    }
    
}


// Called each frame to update snakes position, requires head node and direction of travel
void updateSnake(Node *head,char dir){

    // Updates Snake Heads Direction
    updateDirection(head, dir);
    
    // Updates heads coords based on direction, modifies x/y coords accordinly +50||-50
    updateHead(head);

    // Passes first child to assume the position of the parents node, recursively called through entire tail
    updateTail(head->child);

}



