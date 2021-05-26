#ifndef __OBJ_TRANSFER_H__
#define __OBJ_TRANSFER_H__

#include "../base/objBase.h"
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif
#define PI 3.1415926535898
typedef int RotateAngle;
typedef struct
{
    /* data */
    objNodeLoc x;
    objNodeLoc y;
    objNodeLoc z;
}transNode,transVector;

typedef struct 
{
    /* data */
    transNode node;
    transVector vector;
    RotateAngle angle;
}rotateVector;


void objTranslate(objRoot *root,transVector *vector);
void objRotate(objRoot *root,rotateVector *vector);

#ifdef __cplusplus
}
#endif

#endif //__OBJ_TRANSFER_H__