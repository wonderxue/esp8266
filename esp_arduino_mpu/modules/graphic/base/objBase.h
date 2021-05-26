#ifndef __OBJ_BASE_H__
#define __OBJ_BASE_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float objNodeLoc;
typedef unsigned char objShape;
typedef struct
{
    /* data */
    objShape shape;
    objNode *next;
}objRoot;
typedef struct
{
    /* data */
    objNodeLoc x;
    objNodeLoc y;
    objNodeLoc z;
    objNode *next;
}objNode;


objRoot *objCreate(objNodeLoc *location,objShape objshape);
void objDelete(objRoot *root);


#ifdef __cplusplus
}
#endif

#endif  //__OBJ_BASE_H__