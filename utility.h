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
char *Split(char *s, char c);
int Position1(char *s1, char *s2);
int DirInternalCmd(char const *path);
void CdInternalCmd(char* const line);
int ExecuteProgram(char *program_path);
char *append(char const *str1, char const *str2);
char ** ListExeFilesFromDir();

#endif // UTILITY_H
