#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <string.h>

// Declaration for the node.
typedef struct node
{
        char data[100];
        struct node *prev;
        struct node *next;
} Node;

// Forward definitions for functions.
Node *insert(Node *head, char data[100]);
void convertToVariable(Node *head, char *variable);

#endif // UTILITY_H