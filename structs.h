//
//  structs.h
//

#ifndef structs_h
#define structs_h

//Snake Struct
struct node
{
    // Unique node identifier
    int id;

    // Position of node
    int xPos;
    int yPos;

    // Old position of the node
    int oldxPos;
    int oldyPos; 

    // RGB for the node colour
    int r;
    int g;
    int b;
    
    //So newSeg knows where to put it
    char dir;

    char oldDir;
    
    //Pointers to parent and child node
    struct node *parent;
    struct node *child;
    
};
typedef struct node Node;






#endif /* structs_h */
