#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;

    while (1)
    {
        printf("#cisfun$ ");
        if (getline(&buffer, &bufsize, stdin) == -1)
        {
            printf("\n");
            break;
        }

        char *command = strtok(buffer, " \n");
        if (command == NULL)
            continue;

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Error");

