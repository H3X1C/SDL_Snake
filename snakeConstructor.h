//
//  snakeConstructor.h

//

#ifndef snakeConstructor_h
#define snakeConstructor_h


#include "structs.h"

Node *createHead(int x, int y);
Node *makeNode( int x, int y, Node *parent);
Node *makeChild(Node *node);
void updateHead(Node *node);
void updateTail(Node *node);
void updateDirection(Node *node, char direction);
void updateTailDirection(Node *node);
void updateSnake(Node *head,char dir);

#endif /* snakeConstructor_h */
