#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int Parse(char *s, char **locations)
{
  int i = 0;
  char *p = strtok(s, ";");
  while (p != NULL)
  {
    strncpy(locations[i++], p, 100);
    p = strtok(NULL, ";");
  }
  return i;
}

//
// Creates the array with full program names (including full path).
//
int ListExeFilesFromDir(char *path, char **exe_files)
{
  DIR *d;
  struct dirent *dir;
  int i = 0;
  d = opendir(path);
  if (d)
  {

    while ((dir = readdir(d)) != NULL)
    {
      if (strstr(dir->d_name, ".exe"))
      {
        char str[100];
        int path_sz = strlen(path);

        strncpy(str, path, 100);

        if (path[path_sz - 1] != '\\')
        {
          str[path_sz] = '\\';
          strncpy(str + path_sz + 1, dir->d_name, 100);
        }
        else
        {
          strncpy(str + path_sz, dir->d_name, 100);
        }

        strncpy(exe_files[i++], str, 100);

        // printf("%s\n", str);
      }
    }

    closedir(d);
  }

  return (i);
}

void CopyEnvpIntoVar(char const *envp[], char *path_env)
{
  // Copy Path string from the envp in the char array "path_env".
  for (int i = 0; envp[i] != NULL; i++)
  {
    char const path[] = "Path";
    if (strncmp(envp[i], path, strlen(path) - 1) == 0)
    {
      strncpy(path_env, envp[i] + 5, strlen(envp[i]));
    }
  }
}

//
// Allocate memory for 2d array.
//
char **AllocMem(int n)
{
  char **arr = (char **)malloc(sizeof(char *) * n);
  for (int i = 0; i < n; i++)
  {
    arr[i] = (char *)malloc(sizeof(char *) * 100);
  }
  return arr;
}

int main(int argc, char const *argv[], char const *envp[])
{
  // path_env is the copy of the envp.
  char *path_env = (char *)malloc(sizeof(char) * 1000);

  CopyEnvpIntoVar(envp, path_env);

  // Declare and allocate 30 strings in the array of strings.
  char **array_of_strings = AllocMem(30);

  // Declare and allocate 1000 strings for the all exe files
  // found in the locations from the path variable.
  char **exe_files = AllocMem(1000);

  // It will separate the paths from the path string
  // into array of strings.
  int c = Parse(path_env, array_of_strings);

  // Make list of exe files only for first path which is
  // C:\\Windows\\System32
  // for(int i=0; i<c; i++)
  ListExeFilesFromDir(array_of_strings[0], exe_files);

  // Print every path from the path env variable.
  for (int i = 0; i < c; i++)
  {
    // printf("%d. %s\n", i+1, array_of_strings[i]);
    printf("%s\n", exe_files[i]);
  }

  // Free up allocated memory.
  for (int i = 0; i < 30; i++)
  {
    free(array_of_strings[i]);
  }
  free(array_of_strings);

  for (int i = 0; i < 1000; i++)
  {
    free(exe_files[i]);
  }
  free(exe_files);

  free(path_env);
  return 0;
}