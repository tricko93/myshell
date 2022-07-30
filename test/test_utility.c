#include "../utility.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
  Node *head = NULL;
  char *var = (char *)malloc(sizeof(char) * 100);

  head = insert(head, "C:\\");
  insert(head, "Users");
  insert(head, "\\Marko");
  insert(head, "\\OneDrive");
  insert(head, "\\Desktop");
  insert(head, "\\Programming");

  convertListToVariable(head, var);
  printf("%s\n", var);

  removeLastElement(head);
  removeLastElement(head);
  convertListToVariable(head, var);
  printf("%s\n", var);

  deleteAll(head);

  return 0;
}
