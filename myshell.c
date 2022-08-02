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

    if(Position1(line, "quit")==0)
      exit(0);
  }

  if(input != stdin)
    fclose(input);

  return 0;
}
