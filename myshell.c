#include "myshell.h"
 
int main(int argc, char const *argv[], char const *envp[])
{
  // Declare variables
  Node *head = Insert(NULL, "C:\\");
  char line[MAX_SIZE], path[MAX_SIZE];
  FILE *input = stdin;

  if (argc == 2) // Batch file is given
  {
    input = fopen(argv[1], "r");
    if (input == NULL)
    {
      fprintf(stdout, "Input file was not found.\n");
      exit(1);
    }
  }

  while (1)
  {
    fgets(line, MAX_SIZE, input);
    strtok(line, "\n");

    if (Position1(line, "cd")==0)
    {
      int line_sz = strlen(line);
      if(line_sz == 2)
      {
        char s[100];
        printf("%s\n", getcwd(s, 100));
      }
      else
      {
        char *r = Split(line, ' ');
        ++r;
        chdir(r);
      }
    }
    else if(Position1(line, "clr")==0)
      system("cls");
    else if(Position1(line, "dir")==0)
    {
      char s[100];
      DirInternalCmd(getcwd(s, 100));
    }
    else if(Position1(line, "quit")==0)
      exit(0);
  }

  if(input != stdin)
    fclose(input);

  return 0;
}
