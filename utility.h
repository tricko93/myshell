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

// Forward declarations for utility functions.
Node *insert(Node *head, char data[100]);
void convertToVariable(Node *head, char *variable);
void deleteAll(Node *head);
void removeLastElement(Node *head);
char *split(char *s, char c);
int position1(char *s1, char *s2);

#endif // UTILITY_H