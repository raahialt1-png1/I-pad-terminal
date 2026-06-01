#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main() {
    char input[MAX_LINE];
    char *args[MAX_LINE / 2 + 1]; 

    while (1) {
        printf("mini-term> ");
        fflush(stdout);

        // Read input from user
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        // Built-in exit command
        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;

        // Parse input into arguments
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // Inside Child Process
            if (execvp(args[0], args) < 0) {
                printf("Command not found or execution failed.\n");
            }
            exit(1);
        } else if (pid > 0) {
            // Inside Parent Process: Wait for child to finish
            wait(NULL);
        } else {
            perror("Fork failed");
        }
    }
    return 0;
}
