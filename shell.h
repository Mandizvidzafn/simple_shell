#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *_getline(void);
int execute(char *input);

#endif /* SHELL_H */
