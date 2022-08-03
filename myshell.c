#include "myshell.h"

void EchoInternalCmd(char *line)
{
  char *m = Split(line, ' ');
  printf("%s\n", ++m);
}

void RunProgram(char * const prog)
{
  char s[100];
  getcwd(s, 100);
  int s_sz = strlen(s);
  s[s_sz]='\\';
  strncpy(s+s_sz+1, prog, strlen(prog));
  s[s_sz+1+strlen(prog)]='\0';
  ExecuteProgram(s);
}

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
    char p[100];
    printf("%s>", getcwd(p,100));

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
      RunProgram(line);
  }

  if(input != stdin)
    fclose(input);

  return 0;
}