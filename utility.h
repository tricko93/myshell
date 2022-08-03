#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <stdbool.h>

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
int DirInternalCmd(char const *path);
void CdInternalCmd(char* const line);
void ExecuteProgram(char *program_path);
char *append(char const *str1, char const *str2);

#endif // UTILITY_H