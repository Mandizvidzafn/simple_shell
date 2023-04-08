#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

int main()
{
    char *tokens[MAX_NUM_TOKENS];
    char input[MAX_INPUT_SIZE];
    char *cwd;
    pid_t pid;
    int status;

    while (1) {
        cwd = getcwd(NULL, 0);
        printf("%s$ ", cwd);
        free(cwd);

        if (!fgets(input, MAX_INPUT_SIZE, stdin))
            break;

        int num_tokens = 0;
        char *token = strtok(input, " \n");
        while (token != NULL && num_tokens < MAX_NUM_TOKENS) {
            tokens[num_tokens] = token;
            token = strtok(NULL, " \n");
            num_tokens++;
        }
        tokens[num_tokens] = NULL;

        if (num_tokens == 0)
            continue;

        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            execvp(tokens[0], tokens);
            perror("execvp failed");
            exit(1);
        } else {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

