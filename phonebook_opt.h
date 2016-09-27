#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT      1
#define DEGREE   64


typedef struct __ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __NODE *pNext;
} bTreeEntry;

typedef struct __NODE {
    int degree;
    bTreeEntry children[DEGREE];
} bTreeNode;





char *findName(char lastname[], bTreeNode *node, int ht);
bTreeNode *append(char lastName[], bTreeNode *node, int *ht);


#endif
