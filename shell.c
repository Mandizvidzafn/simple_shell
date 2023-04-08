#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *args[] = {NULL}; // array of arguments to pass to execve

    while (1) {
        printf("#cisfun$ "); // display prompt
        read = getline(&line, &len, stdin);
        if (read == -1) { // handle end of file condition
            printf("\n");
            break;
        }
        line[read - 1] = '\0'; // replace newline with null terminator

        pid_t pid = fork();
        if (pid == -1) { // handle fork error
            perror("Error");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) { // child process
            if (execve(line, args, NULL) == -1) { // execute command
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        else { // parent process
            int status;
            waitpid(pid, &status, 0); // wait for child process to finish
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}

