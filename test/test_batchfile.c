#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
        int i, redirection;
        
        printf("%d\n", argc);

        for(i=0;i<=argc;i++)
        {
                printf("%s\n", argv[i]);
                if(strcmpi(argv[i], "<")){
                        redirection = i;
                }
        }

        // char file_name[100];
        // strncpy(file_name, argv[redirection+1], strlen(argv[redirection+1]));

        // printf("%s\n", file_name);
        return 0;
}
