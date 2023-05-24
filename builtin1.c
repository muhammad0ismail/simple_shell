#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *command;
  int exit_status = 0;

  while (1) {
    printf("shell> ");
    fflush(stdout);

    command = malloc(1024);
    fgets(command, 1024, stdin);

    // Check for EOF
    if (feof(stdin)) {
      break;
    }

    // Remove the newline character from the end of the command
    command[strlen(command) - 1] = '\0';

    // Check for the exit command
    if (strcmp(command, "exit") == 0) {
      break;
    }

    // Check for the cd command
    if (strcmp(command, "cd") == 0) {
      char *directory;

      // Get the directory name
      printf("Enter directory name: ");
      fflush(stdout);

      directory = malloc(1024);
      fgets(directory, 1024, stdin);

      // Remove the newline character from the end of the directory name
      directory[strlen(directory) - 1] = '\0';

      // Change the directory
      if (chdir(directory) != 0) {
        printf("Error changing directory to %s\n", directory);
      }

      free(directory);
      continue;
    }

    // Check for the help command
    if (strcmp(command, "help") == 0) {
      printf("Available commands:\n");
      printf("  exit\n");
      printf("  cd\n");
      printf("  help\n");
      printf("  history\n");
      printf("  alias\n");
      continue;
    }

    // Check for the history command
    if (strcmp(command, "history") == 0) {
      // Get the history list
      list_t *history = get_history();

      // Print the history list
      for (list_node_t *node = history->head; node != NULL; node = node->next) {
        printf("%d: %s\n", node->data->index, node->data->str);
      }

      // Free the history list
      free_list(history);
      continue;
    }

    // Check for the alias command
    if (strcmp(command, "alias") == 0) {
      // Get the alias list
      list_t *aliases = get_aliases();

      // Print the alias list
      for (list_node_t *node = aliases->head; node != NULL; node = node->next) {
        printf("%s=%s\n", node->data->str, node->data->value);
      }

      // Free the alias list
      free_list(aliases);
      continue;
    }

    // Execute the command
    pid_t pid = fork();

    if (pid == 0) {
      // Child process
      execlp(command, command, NULL);
      printf("Error executing command %s\n", command);
      exit(1);
    } else if (pid < 0) {
      // Error forking
      printf("Error forking\n");
      exit(1);
    }

    // Wait for the child process to finish
    wait(&exit_status);

    // Check the exit status of the child process
    if (WIFEXITED(exit_status)) {
      if (WEXITSTATUS(exit_status) != 0) {
        printf("Command %s exited with status %d\n", command, WEXITSTATUS(exit_status));
      }
    } else if (WIFSIGNALED(exit_status)) {
      printf("Command %s was killed by signal %d\n", command, WTERMSIG(exit_status));
    }
  }

  return 0;
}
