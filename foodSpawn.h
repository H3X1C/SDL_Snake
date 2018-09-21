//
//  foodSpawn.h

//

#ifndef foodSpawn_h
#define foodSpawn_h

#include "structs.h"

//For collision tracking and spawning
extern int foodX;
extern int foodY;

int roundUp(int num, int numMultiple);
void foodSpawn(Node *head);

#endif /* foodSpawn_h */
