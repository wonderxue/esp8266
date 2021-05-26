#include "objBase.h"

objRoot *objCreate(objNodeLoc *location,objShape objshape)
{
    unsigned char i;
    objRoot *root=(objNode*)malloc(sizeof(objNode));
    objNode *node=(objNode*)malloc(sizeof(objNode));
    root->shape=objshape;
    root->next=node;
    node->x=*location;
    node->y=*(location++);
    node->z=*(location++);
    for(i=1;i<objshape;i++)
    {
        objNode *node1=(objNode*)malloc(sizeof(objNode));
        node->next=node1;
        node1->x=*(location++);
        node1->y=*(location++);
        node1->z=*(location++);
        node=node1;
    }
    node->next=NULL;
    return root;
}
void objDelete(objRoot *root)
{
    objNode *node,*node1;
    node=root->next;
    while(node!=NULL)
    {
        node1=node->next;
        free(node);
        node=node1;
    }
    free(root);
}