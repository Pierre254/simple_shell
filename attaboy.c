#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "simple_shell> "
#define MAX_LINE 128

int main() {
  char line[MAX_LINE];
  while (1) {
    // Display prompt
    printf(PROMPT);
    fflush(stdout);

    // Read user input
    if (fgets(line, MAX_LINE, stdin) == NULL) {
      // Handle EOF (Ctrl+D)
      printf("\n");
      break;
    }

    // Remove newline character
    line[strcspn(line, "\n")] = '\0';

    // Check for empty command
    if (strlen(line) == 0) {
      continue;
    }

    // Try to execute command
    if (fork() == 0) {
      // Child process
      execve(line, NULL, environ);
      // If execve fails, print error and exit
      perror("Error executing command");
      exit(1);
    } else {
      // Parent process waits for child
      wait(NULL);
    }
  }

  return 0;
}
