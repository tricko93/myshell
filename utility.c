#include "utility.h"

//
// Insert new node at the head of the list and copy data.
//
Node *insert(Node *head, char data[100])
{
  Node *temp, *p;
  temp = (Node *)malloc(sizeof(Node));
  strncpy(temp->data, data, 100);
  temp->next = NULL;
  if (head == NULL)
  {
    head = temp;
  }
  else
  {
    for (p = head; p->next != NULL; p = p->next)
      ;
    p->next = temp;
  }
  return temp;
}

//
// Remove last element from the list.
// Note: Useful when going back one level of directory.
//
void removeLastElement(Node *head)
{
  Node *temp;
  if (head)
  {
    for (temp = head; temp->next->next != NULL; temp = temp->next)
      ;
    free(temp->next);
    temp->next = NULL;
  }
}

//
// Function traverses through the list and makes one string
// from all the nodes.
// Note: Created string will be returned through the 2nd parameter.
//
void convertListToVariable(Node *head, char *variable)
{
  int offset = 0, sum = 0;
  Node *temp = head;
  while (temp != NULL)
  {
    offset = strlen(temp->data);
    strncpy(variable + sum, temp->data, offset);
    temp = temp->next;
    sum += offset;
  }
  variable[sum] = '\0';
}

//
// Remove all elements from the linked list.
//
void deleteAll(Node *head)
{
  if (head)
  {
    deleteAll(head->next);
    free(head);
  }
}

//
// Returns pointer to the delimeter specified as a 2nd parameter.
//
char *split(char *s, char c)
{
  char *pok = s;
  while (*pok)
    if (*pok++ == c)
      return --pok;
  return NULL;
}

//
// Looks for the substring in 1st parameter, if found it will return the size
// of s1, if not found negative value.
//
int position1(char *s1, char *s2)
{
  if (strstr(s1, s1) == NULL)
  {
    return -1;
  }
  else
  {
    return strstr(s1, s2) - s1;
  }
}