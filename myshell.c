#include "myshell.h"

void EchoInternalCmd(char *line)
{
  char *m = Split(line, ' ');
  printf("%s\n", ++m);
}

int main(int argc, char const *argv[], char const *envp[])
{
  // Declare variables
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
    printf("%s>", getcwd(path,100));

    fgets(line, MAX_SIZE, input);
    strtok(line, "\n");

    if (Position1(line, "cd")==0)
    {
      CdInternalCmd(line);
    }
    else if(Position1(line, "clr")==0)
      system("cls");
    else if(Position1(line, "dir")==0)
    {
      char s[100];
      DirInternalCmd(getcwd(s, 100));
    }
    else if(Position1(line, "environ")==0)
    {
      for (int i = 0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
    }
    else if(Position1(line, "echo")==0)
    {
      EchoInternalCmd(line);
    }
    else if(Position1(line, "pause")==0)
    {
      printf("More...");
      getchar();
    }
    else if(Position1(line, "quit")==0)
      exit(0);
    else
    {
      char * full_program_path = append(path, line);
      ExecuteProgram(full_program_path);
      free(full_program_path);
    }
  }

  if(input != stdin)
    fclose(input);

  return 0;
}
