#include "utility.h"

//
// Insert new node at the head of the list and copy data.
//
Node *Insert(Node *head, char data[100])
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
void RemoveLastElement(Node *head)
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
void ConvertListToVariable(Node *head, char *variable)
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
void DeleteAll(Node *head)
{
  if (head)
  {
    DeleteAll(head->next);
    free(head);
  }
}

//
// Returns pointer to the delimeter specified as a 2nd parameter.
//
char *Split(char *s, char c)
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
int Position1(char *s1, char *s2)
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

int DirInternalCmd(char const *path)
{
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("%s\n", dir->d_name);
    }

    closedir(d);
  }

  return (0);
}

void CdInternalCmd(char* const line)
{
  int line_sz = strlen(line);
  if(line_sz == 2)
  {
    char s[100];
    printf("%s\n\n", getcwd(s, 100));
  }
  else
  {
    char *r = Split(line, ' ');
    ++r;
    if (chdir(r))
    {
      fprintf(stdout, "Specified path cannot be found.\n");
    }
  }
}

//
// Execute given program given full path as the parameter.
//
void ExecuteProgram(char *program_path)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Start the child process.
  if (!CreateProcess(NULL,         // No module name (use command line)
                     program_path, // Command line
                     NULL,         // Process handle not inheritable
                     NULL,         // Thread handle not inheritable
                     FALSE,        // Set handle inheritance to FALSE
                     0,            // No creation flags
                     NULL,         // Use parent's environment block
                     NULL,         // Use parent's starting directory
                     &si,          // Pointer to STARTUPINFO structure
                     &pi)          // Pointer to PROCESS_INFORMATION structure
  )
  {
    printf("CreateProcess failed (%d).\n", GetLastError());
    return;
  }
}

// Append creates new string with back slash added.
// Note: Don't forget to free returned variable.
// Return allocated string of size of both strings.
char *append(char const *str1, char const *str2)
{
  char *s = (char *)malloc(300);
  int ind = strlen(str1) + 1;
  strncpy(s, str1, ind);

  if (s[ind - 2] == '\\') // Backslash included
    ind -= 1;
  else // Backslash not included
    s[ind - 1] = '\\';

  strncpy(s + ind, str2, strlen(str2));
  s[ind+strlen(str2)]='\0';
  return s;
}
