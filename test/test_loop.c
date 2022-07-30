#include "../utility.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <windows.h>
#include <stdbool.h>

#define MAX_SIZE 250

void CdInternalCmd(Node *head, char *line, char *path)
{
        int command_sz = strlen(line);
        if (command_sz == 2) // This means only cd is typed on the input.
        {
                printf("%s\n", path);
        }
        else if (command_sz > 3) // This means cd has parameter given on the input.
        {
                char *r = split(line, ' ');
                r++;
                if (position1(r, "..") == 0)
                {
                        removeLastElement(head);
                        convertListToVariable(head, path);
                }
                else
                {
                        Node *p; // Is the last element in the list.
                        for (p = head; p->next != NULL; p = p->next)
                                ;
                        int sz = strlen(p->data);

                        if (p->data[sz - 1] == '\\')
                        {
                                insert(head, r);
                        }
                        else if (head->data[sz - 1] != '\\' && r[0] != '\\')
                        {
                                char str[sz + 2];
                                str[0] = '\\';
                                strncpy(str + 1, r, strlen(r) + 1);
                                insert(head, str);
                        }
                        else
                                insert(head, r);

                        convertListToVariable(head, path);
                }
        }
}

void EchoInternalCmd(char *line)
{
        char *m = split(line, ' ');
        printf("%s\n", ++m);
}

int Dir(char const *path)
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

int Parse(char *s, char **locations)
{
        int i = 0;
        char *p = strtok(s, ";");
        while (p != NULL)
        {
                strncpy(locations[i++], p, MAX_SIZE);
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
                        if (strstr(dir->d_name, ".exe") || strstr(dir->d_name, ".EXE"))
                        {
                                char str[MAX_SIZE];
                                int path_sz = strlen(path);

                                strncpy(str, path, path_sz);

                                if (path[path_sz - 1] != '\\')
                                {
                                        str[path_sz] = '\\';
                                        strncpy(str + path_sz + 1, dir->d_name, strlen(dir->d_name));
                                }
                                else
                                {
                                        strncpy(str + path_sz, dir->d_name, strlen(dir->d_name));
                                }

                                strncpy(exe_files[i++], str, strlen(str));
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
                arr[i] = (char *)malloc(sizeof(char *) * MAX_SIZE);
        }
        return arr;
}

//
// Search in the exe_files for the program we want to execute and return index
// for that program we're looking for.
//
int SearchMultidimensionalArray(char const **exe_files, char *program)
{
        int i;
        for (i = 0; i < 1000; i++)
        {
                if (strstr(exe_files[i], program))
                {
                        break;
                }
        }
        return i;
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

        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
}

int main(int argc, char const *argv[], char const *envp[])
{

        /* Case#.
         * 1. Command given on the keyboard.
         * 2. myshell batchfile - to execute commands from the batch file.
         */

        Node *head = NULL;
        char line[MAX_SIZE];
        char path[MAX_SIZE];
        head = insert(head, "C:\\");
        convertListToVariable(head, path);

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
        int d = ListExeFilesFromDir(array_of_strings[0], exe_files);
                
        for(int i=0; i<c; i++)
        {
                // d = ListExeFilesFromDir(array_of_strings[i], exe_files+=d);
                printf("%s\n", array_of_strings[i]);
        }

        while (1)
        {
                fgets(line, MAX_SIZE, stdin);
                strtok(line, "\n");
                if (position1(line, "cd") == 0)
                {
                        CdInternalCmd(head, line, path);
                }
                else if (position1(line, "clr") == 0)
                {
                        system("cls");
                }
                else if (position1(line, "dir") == 0)
                {
                        Dir(path);
                }
                else if (position1(line, "environ") == 0)
                {
                        int i;
                        for (i = 0; envp[i] != NULL; i++)
                                printf("%s\n", envp[i]);
                }
                else if (position1(line, "echo") == 0)
                {
                        EchoInternalCmd(line);
                }
                else if (position1(line, "quit") == 0)
                {
                        exit(0);
                }
                else if (isalpha(line[0]) && line[1] == ':')
                {
                        deleteAll(head); // clean all data from the list
                        head = NULL;

                        int line_sz = strlen(line);
                        if (line[line_sz - 1] != '\\')
                        {
                                line[line_sz] = '\\';
                                line[line_sz + 1] = '\0';
                        }

                        head = insert(head, line);         // insert new drive
                        convertListToVariable(head, path); // convert to string
                }
                else if (strstr(line, ".exe"))
                {
                        int ind = SearchMultidimensionalArray(exe_files, line);
                        if (ind != 1000) // Not found.
                        {
                                char *program_full_path = exe_files[SearchMultidimensionalArray(exe_files, line)];
                                ExecuteProgram(program_full_path);
                        }


                        /*
                        else
                        {
                                convertListToVariable(head, path);
                                int path_sz = strlen(path);

                                if (path[path_sz]=='\\')
                                {
                                        strncpy(path+path_sz, line, strlen(line));
                                }
                                else
                                {
                                        strncpy(path+path_sz, '\\', 1);
                                        strncpy(path+path_sz+1, line, strlne(line));
                                }
                        }
                        */

                }
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
