#include "objTransfer.h"
objNode *RotateX(objNode *node, RotateAngle angle)
{
    objNodeLoc y1 = node->y;
    objNodeLoc z1 = node->z;
    node->y = y1 * cos(angle) - z1 * sin(angle);
    node->z = y1 * sin(angle) + z1 * cos(angle);
    return node;
}
objNode *RotateY(objNode *node, RotateAngle angle)
{
    objNodeLoc x1 = node->x;
    objNodeLoc z1 = node->z;
    node->x = x1 * cos(angle) + z1 * sin(angle);
    node->z = -x1 * sin(angle) + z1 * cos(angle);
    return node;
}
objNode *RotateZ(objNode *node, RotateAngle angle)
{
    objNodeLoc x1 = node->x;
    objNodeLoc y1 = node->y;
    node->x = x1 * cos(angle) - y1 * sin(angle);
    node->y = x1 * sin(angle) + y1 * cos(angle);
    return node;
}

void objTranslate(objRoot *root, transVector *vector)
{
    objNode *node = root->next;
    do
    {
        /* code */
        node->x += vector->x;
        node->y += vector->y;
        node->z += vector->z;
        node = node->next;
    } while (node != NULL);
}

// objNode* RotateLine(objNode *node,rotateVector *vector)
// {
//     RotateY(node,)
// }
void objRotate(objRoot *root, rotateVector *vector)
{
    transNode transNode = vector->node;
    transVector transVector = vector->vector;
    objNode *node = root->next;
    transNode.x = -transNode.x;
    transNode.y = -transNode.y;
    transNode.z = -transNode.z;
    //移到原点
    objTranslate(root, &transNode);
    if (transVector.x != 0)
    {
        do
        {
            /* code */
            RotateX(node, vector->angle);
            node = node->next;
        } while (node != NULL);
    }
    if (transVector.y != 0)
    {
        do
        {
            /* code */
            RotateY(node, vector->angle);
            node = node->next;
        } while (node != NULL);
    }
    if (transVector.z != 0)
    {
        do
        {
            /* code */
            RotateZ(node, vector->angle);
            node = node->next;
        } while (node != NULL);
    }
}