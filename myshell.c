#include "myshell.h"

void EchoInternalCmd(char *line)
{
  char *m = Split(line, ' ');
  printf("%s\n", ++m);
}

void RunProgram(char const *line, char const *path)
{
  char **programs = ListExeFilesFromDir();

  int ind = -1;
  for (int i = 0; programs[i] != '\0'; i++)
    if (strstr(programs[i], line))
    {
      ind = i;
    }

  if (ind == -1)
  {
    char *full_program_path = append(path, line);
    if(ExecuteProgram(full_program_path)){
      printf("Specified program or an internal command is not found.\n");
    }
    free(full_program_path);
  }
  else
    ExecuteProgram(programs[ind]);

  // Deallocate used memory
  for (int i = 0; programs[i] != '\0'; i++)
    free(programs[i]);
}

void HelpInternalCommand(char* const line)
{
  int line_sz = strlen(line);
  if(line_sz == 4)
  {
    printf("cd <directory>  - Changes current default directory to <directory>.\n");
    printf("clr             - Clears the screen.\n");
    printf("dir <directory> - Prints the contents of the directory <directory>.\n");
    printf("environ         - Prints all environment variables.\n");
    printf("echo <comment>  - Prints <comment> on the screen.\n");
    printf("help            - Help information for MyShell commands.\n");
    printf("pause           - Pauses screen.\n");
    printf("quit            - Quits the program.\n");
  }
  else
  {
    char *arg = Split(line, ' ');
    ++arg;
    if (strcmpi(arg, "cd") == 0)
      printf("cd <directory>  - Changes current default directory to <directory>.\n");
    else if (strcmpi(arg, "clr") == 0)
      printf("clr             - Clears the screen.\n");
    else if (strcmpi(arg, "dir") == 0)
      printf("dir             - Clears the screen.\n");
    else if (strcmpi(arg, "environ") == 0)
      printf("environ         - Prints all environment variables.\n");
    else if (strcmpi(arg, "echo") == 0)
      printf("echo <comment>  - Prints <comment> on the screen.\n");
    else if (strcmpi(arg, "help") == 0)
      printf("help            - Help information for MyShell commands.\n");
    else if (strcmpi(arg, "pause") == 0)
      printf("pause           - Pauses screen.\n");
    else if (strcmpi(arg, "quit") == 0)
      printf("quit            - Quits the program.\n");
  }
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
    printf("%s>", getcwd(path, 100));

    fgets(line, MAX_SIZE, input);
    strtok(line, "\n");

    if (Position1(line, "cd") == 0)
    {
      CdInternalCmd(line);
    }
    else if (Position1(line, "clr") == 0)
      system("cls");
    else if (Position1(line, "dir") == 0)
    {
      char s[100];
      DirInternalCmd(getcwd(s, 100));
    }
    else if (Position1(line, "environ") == 0)
    {
      for (int i = 0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
    }
    else if (Position1(line, "echo") == 0)
    {
      EchoInternalCmd(line);
    }
    else if (Position1(line, "help") == 0)
    {
      HelpInternalCommand(line);
    }
    else if (Position1(line, "pause") == 0)
    {
      printf("More...");
      getchar();
    }
    else if (Position1(line, "quit") == 0)
      exit(0);
    else
      RunProgram(line, path);
  }

  if (input != stdin)
    fclose(input);

  return 0;
}
