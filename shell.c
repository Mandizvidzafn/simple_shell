#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROMPT "$ "

/**
 * main - simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char *input = NULL, *command = NULL, *path = NULL;
    char *env = getenv("PATH"), *token = NULL, **args = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int i = 0, status = 0, count = 0;

    while (1)
    {
        printf("%s", PROMPT);
        read = getline(&input, &len, stdin);

        if (read == -1)
            break;

        if (input[read - 1] == '\n')
            input[read - 1] = '\0';

        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "env") == 0)
        {
            while (environ[i])
            {
                printf("%s\n", environ[i++]);
            }
            i = 0;
            continue;
        }

        command = strtok(input, " ");
        if (command == NULL)
            continue;

        args = malloc(sizeof(char *) * 32);
        if (args == NULL)
        {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        args[count++] = command;

        while ((token = strtok(NULL, " ")) != NULL)
        {
            args[count++] = token;
        }

        args[count] = NULL;

        path = strtok(env, ":");
        while (path != NULL)
        {
            char *command_path = malloc(sizeof(char) * (strlen(command) + strlen(path) + 2));
            if (command_path == NULL)
            {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }

            sprintf(command_path, "%s/%s", path, command);

            if (access(command_path, X_OK) == 0)
            {
                pid_t pid = fork();

                if (pid == -1)
                {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0)
                {
                    execve(command_path, args, environ);
                    perror("execve failed");
                    exit(EXIT_FAILURE);
                }

                wait(&status);

                break;
            }

            free(command_path);
            path = strtok(NULL, ":");
        }

        free(args);
    }

    free(input);

    return (EXIT_SUCCESS);
}

