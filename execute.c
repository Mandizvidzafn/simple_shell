#include "shell.h"

/**
 * execute - Execute a command
 * @input: The command to execute
 *
 * Return: 1 if the shell should continue, 0 if it should exit
 */
int execute(char *input)
{
        pid_t pid;
        int status;

        if (input == NULL || *input == '\0')
                return (1);

        pid = fork();

        if (pid == -1)
        {
                perror("fork");
                return (1);
        }
        else if (pid == 0)
        {
                /* Child process */
                if (execve(input, NULL, NULL) == -1)
                {
                        perror("execve");
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                /* Parent process */
                do {
                        if (waitpid(pid, &status, WUNTRACED) == -1)
                        {
                                perror("waitpid");
                                return (1);
                        }
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }

        return (1);
}
