#include "shell.h"

/**
 * main - Entry point for the shell
 *
 * Return: Always 0
 */
int main(void)
{
        char *input;
        int status;

        do {
                printf("#cisfun$ ");
                input = _getline();
                if (input == NULL)
                {
                        printf("\n");
                        exit(0);
                }
                status = execute(input);
                free(input);
        } while (status);
        return (0);
}
