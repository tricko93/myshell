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

// Forward Declarations.
Node *Insert(Node *head, char data[100]);
void ConvertListToVariable(Node *head, char *variable);
void DeleteAll(Node *head);
void RemoveLastElement(Node *head);
char *Split(char *s, char c);
int Position1(char *s1, char *s2);

#endif // UTILITY_H