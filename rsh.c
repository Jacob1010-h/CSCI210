#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp",   "touch", "mkdir", "ls", "pwd",  "cat",
                    "grep", "chmod", "diff",  "cd", "exit", "help"};

int isAllowed(const char *cmd) {
  for (int i = 0; i < N; i++) {
    if (strcmp(cmd, allowed[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

int main() {

  // TODO
  // Add variables as needed

  char line[256];

  while (1) {

    fprintf(stderr, "rsh>");

    if (fgets(line, 256, stdin) == NULL)
      continue;

    if (strcmp(line, "\n") == 0)
      continue;

    line[strlen(line) - 1] = '\0';
    // TODO
    // Add code to spawn processes for the first 9 commands
    // And add code to execute cd, exit, help commands
    // Use the example provided in myspawn.c

	char *argv[21];
	int argc = 0;

	char *token = strtok(line, " ");

	while (token != NULL && argc < 20) {
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;

	if (argc == 0)
		continue;

	if (!isAllowed(argv[0])) {
		printf("NOT ALLOWED!\n");
		continue;
	}

	if (strcmp(argv[0], "exit") == 0 ) {
		return 0;
	}

	if ( strcmp(argv[0], "help") == 0) {
		printf("The allowed commands are:\n");
		for (int i = 0; i < N; i++) {
			printf("%d: %s\n", i+1, allowed[i]);
		}

		continue;
	}

	if (strcmp(argv[0], "cd") == 0	) {
		if (argc > 2 ) {
			printf("-rsh: cd: too many arguments\n");
		} else if (argc == 2) {
			chdir(argv[1]);
		}
		continue;
	}

	pid_t pid;
	int status;
	posix_spawnattr_t attr;

	posix_spawnattr_init(&attr);

	if (posix_spawnp(&pid, argv[0], NULL, &attr, argv, environ) != 0 ) {
		printf("NOT ALLOWED!\n");
		posix_spawnattr_destroy(&attr);
		continue;
	}

	waitpid(pid, &status, 0);
	posix_spawnattr_destroy(&attr);
  }

  return 0;
}
