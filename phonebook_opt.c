#include <stdlib.h>
#include <string.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
/*entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if(strcasecmp(lastname, pHead->lastNameList[pHead->numElements-1]) <= 0) {
            unsigned int i;
            for(i = 0; i < pHead->numElements; i++) {
                if (strcasecmp(lastname, pHead->lastNameList[i]) == 0) {
                    strcpy(pHead->lastName, lastname);
                    return pHead;
                }
            }
        }
        pHead = pHead->pNext;
    }
    return NULL;
}*/

char *findName(char lastname[], bTreeNode *node, int ht)
{
    bTreeEntry *children = node->children;
    int j;
    if(ht == 0){
        for(j = 0; j < node->degree; j++){
            if(strcmp(lastname, children[j].lastName) == 0){
                return lastname;
            }
        }
    }
    else{
        for(j = 0; j < node->degree; j++){
            if(j+1 == node->degree || strcmp(lastname, children[j+1].lastName) < 0)
                return findName(lastname, children[j].pNext, ht-1);
        }
     }
    return NULL;
}

/*entry *append(char lastName[], entry *e)
{
    if(e->numElements < MAX_NUM_OF_NAME) {
        strcpy(e->lastNameList[e->numElements], lastName);
    } else {
        // printf("%s\r\n", e->lastNameList[e->numElements-1]);
        e->pNext = (entry *) malloc(sizeof(entry));
        e = e->pNext;
        e->numElements = 0;
        strcpy(e->lastNameList[e->numElements], lastName);
        e->pNext = NULL;
    }
    e->numElements++;
    return e;
}*/

bTreeNode *split(bTreeNode *node)
{
    int j;
    bTreeNode *e = (bTreeNode *)malloc(sizeof(bTreeNode));
    e->degree = DEGREE >> 1;
    node->degree = DEGREE >> 1;
    for(j = 0; j < DEGREE >> 1; j++){
        e->children[j] = node->children[(DEGREE>>1) + j];
    }
    return e;
}

bTreeNode *appendHelp(char lastName[], bTreeNode *node, int ht)
{
    int i, j;
    bTreeEntry *e = (bTreeEntry *)malloc(sizeof(bTreeEntry));
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    if(ht == 0) {
        for(j = 0; j < node->degree; j++) {
            if(strcmp(lastName, node->children[j].lastName) < 0)
                break;
        }    
    }

    else {
        for(j = 0; j < node->degree; j++) {
            if((j+1 == node->degree) || strcmp(lastName, node->children[j+1].lastName) < 0) {
               bTreeNode *u = appendHelp(lastName, node->children[j++].pNext, ht-1);
               if(u == NULL)
                   return NULL;
               strcpy(e->lastName, u->children[0].lastName);
               e->pNext = u;
               break; 
            }
        }
    }
    
    for(i = node->degree; i > j; i--) {
        node->children[i] = node->children[i-1];
    }
    node->children[j] = *e;
    node->degree++;
    if(node->degree < DEGREE){
        return NULL;
    }
    else{
        return split(node);
    }
}

bTreeNode *append(char lastName[], bTreeNode *root, int *ht)
{
    bTreeNode *e = appendHelp(lastName, root, *ht);
    if(e == NULL)
        return root;
    bTreeNode *u = (bTreeNode *)malloc(sizeof(bTreeNode));
    u->degree = 2;
    strcpy(u->children[0].lastName, root->children[0].lastName);
    u->children[0].pNext = root;
    strcpy(u->children[1].lastName, e->children[0].lastName);
    u->children[1].pNext = e;
    root = u;
    *ht = *ht + 1;
    return root;      
}








