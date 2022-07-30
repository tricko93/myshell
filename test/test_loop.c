#include "../utility.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <windows.h>
#include <stdbool.h>
void cd_internal_cmd(Node *head, char *line, char *path)
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
                        for (p = head; p->next != NULL; p = p->next);
                        int sz = strlen(p->data);

                        if (p->data[sz-1]=='\\')
                        {
                                insert(head, r);
                        }
                        else if (head->data[sz-1]!='\\' && r[0]!='\\')
                        {
                                char str[sz+2];
                                str[0]='\\';
                                strncpy(str+1, r, strlen(r)+1);
                                insert(head, str);
                        }
                        else
                                insert(head, r);
                
                        convertListToVariable(head, path);
                }
        }
}

void echo_internal_cmd(char *line)
{
        char *m = split(line, ' ');
        printf("%s\n", ++m);
}

int dir(char const *path)
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

void run_program(Node *head, char *line, char *path)
{
        char str[100];

        int sz = strlen(head->data);
        int sz_path = strlen(path);
        int sz_line = strlen(line);

        strncpy(str, path, sz_path);

        Node *p; // Is the last element in the list.
        for (p = head; p->next != NULL; p = p->next);


        if (p->data[sz - 1] == '\\')
        {
                strncpy(str + sz_path, line, sz_line);
                str[sz_line + sz_path] = '\0';
        }
        else
        {
                str[sz_path] = '\\';
                strncpy(str + sz_path + 1, line, sz_line);
                str[sz_path + sz_line + 1] = '\0';
        }

        printf("%s %s %s\n", str, path, line);
}

int main(int argc, char const *argv[], char const *envp[])
{

        /* Case#. 
         * 1. Command given on the keyboard.
         * 2. myshell batchfile - to execute commands from the batch file.
         */


        Node *head = NULL;
        char line[100];
        char path[100];
        head = insert(head, "C:\\");
        convertListToVariable(head, path);

        while (1)
        {
                fgets(line, 100, stdin);
                strtok(line, "\n");
                if (position1(line, "cd") == 0)
                {
                        cd_internal_cmd(head, line, path);
                }
                else if (position1(line, "clr") == 0)
                {
                        system("cls");
                }
                else if (position1(line, "dir") == 0)
                {
                        dir(path);
                }
                else if (position1(line, "environ") == 0)
                {
                        int i;
                        for (i = 0; envp[i] != NULL; i++)
                                printf("%s\n", envp[i]);
                }
                else if(position1(line, "echo") == 0)
                {
                        echo_internal_cmd(line);
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
                        if(line[line_sz-1]!='\\')
                        {
                                line[line_sz]='\\';
                                line[line_sz+1]='\0';
                        }

                        head = insert(head, line);     // insert new drive
                        convertListToVariable(head, path); // convert to string
                }
                else if (strstr(line, ".exe"))
                {
                        char path[100];
                        convertListToVariable(head, path);

                        int path_sz = strlen(path), line_sz = strlen(line);
                        if(path[path_sz] != '\\' && line[0]!='\\')
                        {
                                path[path_sz]='\\';       
                        }

                        strncpy(path+path_sz+1, line, line_sz);
                        path[path_sz+line_sz+1]='\0';

                        // TODO: Use search for the full program path.

                        printf("%s\n", path);

                        STARTUPINFOA startup_info = {0};
			LPSTARTUPINFOA p_startup_info = &startup_info;
			PROCESS_INFORMATION proc_info = {0};
			LPPROCESS_INFORMATION p_proc_info = &proc_info;

			bool process_created = CreateProcess(
			    NULL,
			    path,
			    NULL,
			    NULL,
			    FALSE,
			    DETACHED_PROCESS,
			    NULL,
			    NULL,
			    p_startup_info,
			    p_proc_info);

                        // system(path);
                        // run_program(head, line, path);
                }
        }
        return 0;
}
