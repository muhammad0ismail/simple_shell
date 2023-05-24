#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
View other drafts





1
Sure, I can help you with that. Here is the rewritten code:

C
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
      printf("  env\n");
      printf("  setenv\n");
      printf("  unsetenv\n");
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

    // Check for the env command
    if (strcmp(command, "env") == 0) {
      // Print the current environment
      print_list_str(get_env());
      continue;
    }

    // Check for the setenv command
    if (strcmp(command, "setenv") == 0) {
      if (info->argc != 3) {
        _eputs("Incorrect number of arguements\n");
        return (1);
      }
      if (_setenv(info, info->argv[1], info->argv[2])) {
        return (0);
      }
      return (1);
    }

    // Check for the unsetenv command
    if (strcmp(command, "unsetenv") == 0) {
      if (info->argc == 1) {
        _eputs("Too few arguements.\n");
        return (1);
      }
      for (int i = 1; i <= info->argc; i++) {
        _unsetenv(info, info->argv[i]);
      }

      return (0);
    }
