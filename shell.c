#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        // Read in the command from the user
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // Handle the end of file condition (Ctrl+D)
            printf("\n");
            exit(0);
        }

        // Remove the trailing newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Fork a new process to execute the command
        pid_t pid = fork();

        if (pid < 0) {
            // Handle the fork error
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            if (execlp(command, command, (char *) NULL) < 0) {
                // Handle the error if the command doesn't exist
                printf("%s: command not found\n", command);
                exit(1);
            }
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}

