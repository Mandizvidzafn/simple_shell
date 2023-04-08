#include "shell.h"

/**
 * _getline - Read an entire line from stdin
 *
 * Return: The line read from stdin
 */
char *_getline(void)
{
        char *buffer = NULL;
        size_t bufsize = 0;
        ssize_t chars_read;

        chars_read = getline(&buffer, &bufsize, stdin);

        if (chars_read == -1)
                return (NULL);

        if (buffer[chars_read - 1] == '\n')
                buffer[chars_read - 1] = '\0';

        return (buffer);
}
